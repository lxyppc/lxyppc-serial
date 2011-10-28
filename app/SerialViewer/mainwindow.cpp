#include "mainwindow.h"
#include "qextserialenumerator.h"
#include "qwineventnotifier_p.h"
#include <QList.h>
OVERLAPPED overlap;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    // Initialize the UI component
    QMdiArea* mdiArea = new QMdiArea;
    mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(mdiArea);

    deviceView = new QTreeView(this);
    deviceView->setHeaderHidden(true);
    deviceView->setEditTriggers(0);
    deviceViewModel = new QStandardItemModel;
    deviceView->setModel(deviceViewModel);

    dockDevList = new QDockWidget(tr("Device List"), this);
    dockDevList->setAllowedAreas(Qt::AllDockWidgetAreas);
    dockDevList->setWidget(deviceView);
    dockDevList->setObjectName(tr("FindResult"));
    this->addDockWidget(Qt::LeftDockWidgetArea,dockDevList);

    //connect(deviceList, SIGNAL(clicked(QModelIndex)), this, SLOT(onComboCLick()));

    refreshDeviceList();
}

MainWindow::~MainWindow()
{
}

void MainWindow::onComboCLick()
{
}

void MainWindow::refreshDeviceList()
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    deviceViewModel->clear();
    for (int i = 0; i < ports.size(); i++) {
        const QextPortInfo& info = ports.at(i);
        QStandardItem *item = new QStandardItem(info.portName);
        {
            item->appendRow(new QStandardItem(QString("Name:") + info.friendName));
            item->appendRow(new QStandardItem(QString("Path:") + info.physName));
            QString str =
            QString("VID 0x%0, PID 0x%1").arg(info.vendorID,4,16,QChar('0')).arg(info.productID,4,16,QChar('0'));
            item->appendRow(new QStandardItem(str));
        }
        deviceViewModel->setItem(i, 0, item);
    }
}
