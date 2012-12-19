#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <QList>
#include <QStringList>
#include <stdint.h>
#include <QThread>

class UsbDevice : public QThread
{
public:
    UsbDevice();

    bool openBySN(const QString& devSN, int epForRead = 0);

    bool openByPath(const QString& path, int epForRead = 0);

    bool close();

    int lastError()const;

    QString lastErrorString()const;

    bool writeData(const void* data, size_t len, int epNum, int timeout);

    int readData(void* data, size_t len, int epNum, int timeout);

    bool writeControlData(const void* data, size_t len, uint8_t request, uint16_t value, uint16_t index);

    int readControlData(void* data, size_t len, uint8_t request, uint16_t value, uint16_t index);

    QString devicePath()const;

    QString deviceName()const;

    // static methods
    static QStringList enumDevice(uint16_t vid, uint16_t pid, bool SN = false);

    static bool Init(void);

    virtual void OnData(const void* data, size_t len);

protected:
    virtual void run();

private:
    void*  handle;
    int errorCode;
    int epForRead;
    bool open(void* dev, int epForRead);
    QString devName;
    QString devPath;
};

#endif // USBDEVICE_H
