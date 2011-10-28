#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "qextserialenumerator.h"
class SerialMonitor;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void addMenus();

    void closeEvent(QCloseEvent *event);

private:
    void createActions();
    SerialMonitor *activeMdiChild();
signals:

public slots:
    void refreshDeviceList();

    void deviceViewClicked(QModelIndex index);

    void deviceDockChanged(Qt::DockWidgetArea dockArea);

    void deviceSelected(QModelIndex index);

private slots:
    void updateWindowMenu();
    void setActiveSubWindow(QWidget *window);
    void updateWindowSubMenus();

private:
    QMenu*                  viewMenu;
    QMenu*                  windowMenu;
    QDockWidget*            dockDevList;
    QListView*              deviceList;
    QStandardItemModel*     deviceViewModel;
    QSplitter*              deviceListSplitter;
    QTextEdit*              deviceInfoText;
    QList<QextPortInfo>     deviceInfoList;
    QMdiArea*               mdiArea;

    QSignalMapper*          windowMapper;

    // Actions
    QAction *closeAct;
    QAction *closeAllAct;
    QAction *tileAct;
    QAction *cascadeAct;
    QAction *nextAct;
    QAction *previousAct;
    QAction *separatorAct;
};

#endif // MAINWINDOW_H
