#include "mainwindow.h"
#include "qusbhidenumerator.h"

QUsbHidEnumerator* hidenum = 0;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":res/123.png"));
    mdi = new QMdiArea(this);
    this->setCentralWidget(mdi);
    QDockWidget* dock = new QDockWidget(tr("Script log"),this);
    dock->setObjectName(tr("ScriptLogDock"));
    logText = new QTextEdit(dock);
    logText->setReadOnly(true);
    logText->setLineWrapMode(QTextEdit::NoWrap);
    dock->setWidget(logText);
    this->addDockWidget(Qt::BottomDockWidgetArea, dock);
    if(hidenum == 0){
        hidenum = new QUsbHidEnumerator();
    }
    connect(hidenum, SIGNAL(deviceDiscovered(QUsbHidInfo)), this, SLOT(devconnect(QUsbHidInfo)));
    connect(hidenum, SIGNAL(deviceRemoved(QUsbHidInfo)), this, SLOT(devdisconnect(QUsbHidInfo)));
    hidenum->setUpNotifications(0x051A,0x511B);

    QMenu* menu = 0;
    QList<QAction*> list = menuBar()->actions();
    foreach(QAction* act, list){
        if( act->text().contains(tr("help"),Qt::CaseInsensitive) ){
            menu = act->menu();
        }
    }

    if(menu == 0){
        menu = menuBar()->addMenu(tr("&Help"));
    }
    menu->addAction(dock->toggleViewAction());
    menu->addSeparator();
    QAction* act = menu->addAction(tr("&About..."));
    connect(act,SIGNAL(triggered()),this,SLOT(my_about()));
    this->setWindowTitle(QString::fromLocal8Bit("Tool Box"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::addLog(const QString& log)
{
    logText->append(log);
}

void MainWindow::my_about()
{
    QMessageBox::about(this, "Toolbox", QString::fromLocal8Bit("<p><b>Toolbox</b></p><p>by lxyppc</p>lxyppc@163.com"));
}

void MainWindow::devconnect(const QUsbHidInfo& info)
{
    qDebug()<<"devconnect";
    qDebug()<<info.enumName;
    qDebug()<<info.friendName;
    qDebug()<<info.physName;
    qDebug()<<info.path;
    qDebug()<<info.productID;
    qDebug()<<info.vendorID;
}

void MainWindow::devdisconnect(const QUsbHidInfo& info)
{
    qDebug()<<"devdisconnect";
    qDebug()<<info.enumName;
    qDebug()<<info.friendName;
    qDebug()<<info.physName;
    qDebug()<<info.path;
    qDebug()<<info.productID;
    qDebug()<<info.vendorID;
}














