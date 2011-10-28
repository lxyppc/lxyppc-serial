#include "mainwindow.h"
#include "qextserialenumerator.h"
#include "QList"
#include "serialmonitor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Initialize the UI component
    mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    deviceViewModel = new QStandardItemModel;

    deviceList = new QListView(this);
    deviceList->setModel(deviceViewModel);
    deviceList->setEditTriggers(0);

    deviceListSplitter = new QSplitter(this);
    deviceListSplitter->addWidget(deviceList);
    deviceInfoText = new QTextEdit();
    deviceInfoText->setReadOnly(true);
    deviceInfoText->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    deviceInfoText->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    deviceInfoText->setWordWrapMode(QTextOption::NoWrap);

    deviceListSplitter->addWidget(deviceInfoText);
    deviceListSplitter->setOrientation(Qt::Vertical);

    // Initialize the dock widget
    dockDevList = new QDockWidget(tr("Device List"), this);
    dockDevList->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockDevList->setWidget(deviceListSplitter);
    dockDevList->setObjectName(tr("Device List"));
    this->addDockWidget(Qt::LeftDockWidgetArea,dockDevList);

    connect(deviceList, SIGNAL(clicked(QModelIndex)), this, SLOT(deviceViewClicked(QModelIndex)));

    connect(deviceList, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(deviceSelected(QModelIndex)));

    connect(dockDevList, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)), this, SLOT(deviceDockChanged(Qt::DockWidgetArea)));

    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(setActiveSubWindow(QWidget*)));

    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
            this, SLOT(updateWindowSubMenus()));

    createActions();

    addMenus();

    updateWindowMenu();

    connect(windowMenu, SIGNAL(aboutToShow()), this, SLOT(updateWindowMenu()));

    updateWindowSubMenus();

    refreshDeviceList();
}

MainWindow::~MainWindow()
{
}

void MainWindow::refreshDeviceList()
{
    deviceInfoList = QextSerialEnumerator::getPorts();
    deviceViewModel->clear();
    for (int i = 0; i < deviceInfoList.size(); i++) {
        const QextPortInfo& info = deviceInfoList.at(i);
        QStandardItem *item = new QStandardItem(info.portName);
        deviceViewModel->setItem(i, 0, item);
    }
}

void MainWindow::deviceViewClicked(QModelIndex index)
{
    if(index.row() >= deviceInfoList.count())return;
    const QextPortInfo& info = deviceInfoList.at(index.row());
    QString str = QString("Device information:\r\n");
    str += QString("VID 0x%0, PID 0x%1\r\n")
           .arg(info.vendorID,4,16,QChar('0'))
           .arg(info.productID,4,16,QChar('0'));
    str += QString("Name:  %0\r\n").arg(info.friendName);
    str += QString("Path:  %0\r\n").arg(info.physName);
    str += QString("Enum name:  %0\r\n").arg(info.enumName);
    deviceInfoText->setText(str);
}

void MainWindow::deviceDockChanged(Qt::DockWidgetArea dockArea)
{
    if(dockArea & (Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea)){
        deviceListSplitter->setOrientation(Qt::Vertical);
    }else{
        deviceListSplitter->setOrientation(Qt::Horizontal);
    }
}

void MainWindow::deviceSelected(QModelIndex index)
{
    if(index.row() >= deviceInfoList.count())return;
    const QextPortInfo& info = deviceInfoList.at(index.row());
    QString devName = info.portName;
    if(info.portName.startsWith("tty")){
        devName = info.physName;
    }

    foreach(QMdiSubWindow* window, mdiArea->subWindowList()){
        if(window->widget()->windowTitle().contains(devName)){
            mdiArea->setActiveSubWindow(window);
            return;
        }
    }

    SerialMonitor* monitor = new SerialMonitor(devName);
    mdiArea->addSubWindow(monitor);
    monitor->show();
}

SerialMonitor *MainWindow::activeMdiChild()
{
    if (QMdiSubWindow *activeSubWindow = mdiArea->activeSubWindow())
        return qobject_cast<SerialMonitor *>(activeSubWindow->widget());
    return 0;
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    mdiArea->closeAllSubWindows();
    if (mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        //writeSettings();
        event->accept();
    }
}

void MainWindow::updateWindowSubMenus()
{
    bool hasMdiChild = (activeMdiChild() != 0);
    closeAct->setEnabled(hasMdiChild);
    closeAllAct->setEnabled(hasMdiChild);
    tileAct->setEnabled(hasMdiChild);
    cascadeAct->setEnabled(hasMdiChild);
    nextAct->setEnabled(hasMdiChild);
    previousAct->setEnabled(hasMdiChild);
    separatorAct->setVisible(hasMdiChild);
}

void MainWindow::addMenus()
{
    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(dockDevList->toggleViewAction());
    windowMenu = menuBar()->addMenu(tr("&Window"));
}

void MainWindow::updateWindowMenu()
{
    windowMenu->clear();
    windowMenu->addAction(closeAct);
    windowMenu->addAction(closeAllAct);
    windowMenu->addSeparator();
    windowMenu->addAction(tileAct);
    windowMenu->addAction(cascadeAct);
    windowMenu->addSeparator();
    windowMenu->addAction(nextAct);
    windowMenu->addAction(previousAct);
    windowMenu->addAction(separatorAct);

    QList<QMdiSubWindow *> windows = mdiArea->subWindowList();
    separatorAct->setVisible(!windows.isEmpty());

    for (int i = 0; i < windows.size(); ++i) {
        SerialMonitor *child = qobject_cast<SerialMonitor *>(windows.at(i)->widget());

        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->windowTitle());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->windowTitle());
        }
        QAction *action  = windowMenu->addAction(text);
        action->setCheckable(true);
        action ->setChecked(child == activeMdiChild());
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, windows.at(i));
    }
}

void MainWindow::createActions()
{
    closeAct = new QAction(tr("Cl&ose"), this);
    closeAct->setStatusTip(tr("Close the active window"));
    connect(closeAct, SIGNAL(triggered()),
            mdiArea, SLOT(closeActiveSubWindow()));

    closeAllAct = new QAction(tr("Close &All"), this);
    closeAllAct->setStatusTip(tr("Close all the windows"));
    connect(closeAllAct, SIGNAL(triggered()),
            mdiArea, SLOT(closeAllSubWindows()));

    tileAct = new QAction(tr("&Tile"), this);
    tileAct->setStatusTip(tr("Tile the windows"));
    connect(tileAct, SIGNAL(triggered()), mdiArea, SLOT(tileSubWindows()));

    cascadeAct = new QAction(tr("&Cascade"), this);
    cascadeAct->setStatusTip(tr("Cascade the windows"));
    connect(cascadeAct, SIGNAL(triggered()), mdiArea, SLOT(cascadeSubWindows()));

    nextAct = new QAction(tr("Ne&xt"), this);
    nextAct->setShortcuts(QKeySequence::NextChild);
    nextAct->setStatusTip(tr("Move the focus to the next window"));
    connect(nextAct, SIGNAL(triggered()),
            mdiArea, SLOT(activateNextSubWindow()));

    previousAct = new QAction(tr("Pre&vious"), this);
    previousAct->setShortcuts(QKeySequence::PreviousChild);
    previousAct->setStatusTip(tr("Move the focus to the previous "
                                 "window"));
    connect(previousAct, SIGNAL(triggered()),
            mdiArea, SLOT(activatePreviousSubWindow()));

    separatorAct = new QAction(this);
    separatorAct->setSeparator(true);
}
