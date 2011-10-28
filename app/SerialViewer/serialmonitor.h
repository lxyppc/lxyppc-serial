#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QtGui>
#include "ui_BasicView.h"
#include "qextserialport.h"

class SerialMonitor : public QFrame, public Ui::BasicView
{
Q_OBJECT
public:
    explicit SerialMonitor(const QString& portName, QWidget *parent = 0);

    static void addSettingMenuCallback(const QString& name, const QString& setting, bool isGroup, void* context);
    void addSettingMenu(const QString& name, const QString& setting, bool isGroup);

protected:
    void closeEvent(QCloseEvent *event);
    bool canbeClose();
signals:

public slots:

    void updateUI();
    void openDevice();
    void wirteData();
    void onReadyRead();
    void updateSetting(QString setting);

private:
    QString             mPortName;
    QextSerialPort*     serialPort;
    QSignalMapper*      settingMapper;
    QMenu*              settingMenu;
};

#endif // SERIALMONITOR_H
