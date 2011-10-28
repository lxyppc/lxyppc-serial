#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "qextserialenumerator.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:

signals:

public slots:
    void refreshDeviceList();

#ifdef Q_OS_WIN
    private slots:
        void onComboCLick();
#endif
private:
    QDockWidget*            dockDevList;
    QListWidget*            deviceList;
    QTreeView*              deviceView;
    QStandardItemModel*     deviceViewModel;
    QListWidget*            viewerList;
};

#endif // MAINWINDOW_H
