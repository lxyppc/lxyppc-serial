#ifndef SERIALMONITOR_H
#define SERIALMONITOR_H

#include <QtGui>
#include "ui_BasicView.h"
#include "qextserialport.h"
#include "qhexedit.h"

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
    void updateTextMode();
signals:

public slots:

    void updateUI();
    void openDevice();
    void wirteData();
    void sendFile();
    void onReadyRead();
    void updateSetting(QString setting);
    void switchRecvTextMode();
    void switchSendTextMode();

private:
    QString             mPortName;
    QextSerialPort*     serialPort;
    QSignalMapper*      settingMapper;
    QMenu*              settingMenu;
    bool                recvTextModeHex;
    bool                sendTextModeHex;
    QHexEdit*           sendHexEdit;
    QHexEdit*           recvHexEdit;
};

#endif // SERIALMONITOR_H
