#include "mainwindow.h"
#include "hexeditor/qhexedit.h"
void run_script_init(MainWindow* mainwindow);
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

    run_script_init(this);

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
    this->setWindowTitle(QString::fromLocal8Bit("X Toolbox"));
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
    QMessageBox::about(this,
        "X Toolbox",
        QString::fromLocal8Bit("<p><b>X Toolbox</b></p><p>by lxyppc</p><a href=\"mailto:lxyppc@163.com\">lxyppc@163.com</a>"));
}
