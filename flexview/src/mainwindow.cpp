#include "mainwindow.h"
#include "hexeditor/qhexedit.h"
void run_script_init(QMainWindow* mainwindow);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    run_script_init(this);
    menuBar()->addMenu(tr("&Help"))->addAction(tr("&About..."));
    QFrame* f = new QFrame(this);
    QVBoxLayout* l = new QVBoxLayout(f);
    l->addWidget(new QHexEdit(this));
    l->addWidget(new QHexEdit(this));
    f->setLayout(l);
    this->setCentralWidget(f);
}

MainWindow::~MainWindow()
{

}
