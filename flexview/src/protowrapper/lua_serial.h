#ifndef LUA_SERIAL_H
#define LUA_SERIAL_H
#include "../../qextserialport/qextserialport.h"
#include "../../qextserialport/qextserialenumerator.h"
#include "../qtwrapper/lua_qt_wrapper.hpp"
#include "serialhelper.h"


class QSerialPort : public QextSerialPort
{
    Q_OBJECT
public:
    QSerialPort(int mode = EventDriven):QextSerialPort(QueryMode(mode)){initial();}
    QSerialPort(const QString & name, int mode = EventDriven):QextSerialPort(name,QueryMode(mode)){initial();}
    QSerialPort(const QString & name, const PortSettings& s, int mode = EventDriven):QextSerialPort(name,s,QueryMode(mode)){initial();}

    QString portName() const{ return QextSerialPort::portName(); }
    void setPortName(const QString& name){ QextSerialPort::setPortName(name); }

    int queryMode() const { return QextSerialPort::queryMode(); }
    void setQueryMode(int mode){ QextSerialPort::setQueryMode(QueryMode(mode));}

    void setBaudRate(int baud){ QextSerialPort::setBaudRate(BaudRateType(baud)); emit settingChange(settingString());}
    int baudRate() const { return QextSerialPort::baudRate(); }

    void setDataBits(int bits){ QextSerialPort::setDataBits(DataBitsType(bits)); emit settingChange(settingString());}
    int dataBits() const{ return QextSerialPort::dataBits(); }

    void setParity(int parity){ QextSerialPort::setParity(ParityType(parity)); emit settingChange(settingString());}
    int parity() const{ return QextSerialPort::parity(); }

    void setStopBits(int stop){ QextSerialPort::setStopBits(StopBitsType(stop)); emit settingChange(settingString());}
    int stopBits() const { return QextSerialPort::stopBits(); }

    void setFlowControl(int flow){ QextSerialPort::setFlowControl(FlowType(flow)); emit settingChange(settingString());}
    int flowControl() const{ return QextSerialPort::flowControl(); }

    QString settingString() const { return PortSettingString(Settings);}

protected:
    void initial();
signals:
    void connected(const QextPortInfo&);
    void disconnected(const QextPortInfo&);
    void settingChange(const QString& setting);
protected:
    static QextSerialEnumerator* enumerator;
};

typedef class_<PortSettings>    LQPortSetting;
typedef class_<QSerialPort>  LQextSerialPort;
typedef class_<QextPortInfo>  LQextPortInfo;

LQextSerialPort lqextserialport();
LQextPortInfo lqextportinfo();
LQPortSetting lqportsetting();
#endif // LUA_SERIAL_H
