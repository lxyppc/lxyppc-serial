#include "mainwindow.h"
#include "hexeditor/qhexedit.h"
void run_script_init(QMainWindow* mainwindow);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //mdi = new QMdiArea(this);
    //this->setCentralWidget(new QHexEdit(this));
    this->menuBar()->addMenu("&Help")->addAction("&About...");
    run_script_init(this);
}

MainWindow::~MainWindow()
{

}
