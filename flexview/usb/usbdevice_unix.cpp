#include "usbdevice.h"
#include <QMap>
#include <QDebug>
#include <QLibrary>
#include <QTextCodec>
#include "libusb.h"

typedef libusb_device usb_device;
typedef libusb_device_handle usb_dev_handle;
typedef QMap<QString, usb_device*> DeviceMap_t;
libusb_device **device_list;


static DeviceMap_t deviceMap;

UsbDevice::UsbDevice()
    :handle(0)
    ,errorCode(0)
    ,epForRead(0)
{
    Init();
    devPath = "unknown path";
    devName = "unknown name";
}

static void showBytes(const void* p, int len, const char* desc);

static QString getDevicePath(usb_device* dev)
{
    QString str("//bus%1/dev%2");
    return str.arg(libusb_get_bus_number(dev)).arg(libusb_get_device_address(dev));
}

static QString translateUSBString(const char* str, int len)
{
    if(len < 4) return QString("<null>");
    return QString((QChar*)(str+2), (len - 2)/2);
}

static void showBytes(const void* p, int len, const char* desc)
{
    qDebug()<<desc<<":"<<len;
    const unsigned char* data = (const unsigned char*)p;
    QString s;
    for(int i=0;i<len;i++){
        s+=QString("%1,").arg(data[i],2,16, QChar('0'));
        if( (i&15) == 15){
            qDebug()<<s;
            s = "";
        }
    }
    if(s.length())qDebug()<<s;
}

bool UsbDevice::openBySN(const QString& devSN, int epForRead)
{
    if(deviceMap.find(devSN) != deviceMap.end()){
        usb_device* dev = deviceMap.value(devSN);
        return open(dev, epForRead);
    }
    return false;
}

bool UsbDevice::openByPath(const QString& path, int epForRead)
{
    foreach(usb_device* dev, deviceMap.values()){
        if(path.compare(getDevicePath(dev), Qt::CaseInsensitive) == 0){
            return open(dev, epForRead);
        }
    }
    return false;
}

bool UsbDevice::open(void* devive, int epForRead)
{
    usb_device* dev = (usb_device*)devive;
    usb_dev_handle* handle = 0;
    close();
    errorCode = libusb_open(dev, &handle);
    if(errorCode < 0 ){
        handle = 0;
    }
    if(handle != 0){
        devPath = getDevicePath(dev);

        errorCode = libusb_claim_interface(handle, 0);
        if(errorCode >= 0){
            char sn[256] = {0};
            int res = 0;
            this->handle = handle;
            res = libusb_get_string_descriptor(handle,3,0,(uint8_t*)sn,256);
            if(res > 0){
                devName = translateUSBString(sn,res);
            }
            if(epForRead){
                this->epForRead = epForRead;
                this->start();
            }
            return true;
        }
        libusb_close(handle);
    }
    return false;
}

QString UsbDevice::devicePath()const
{
    //if(!handle) return LoadString(cs::unknownDevPath);
    return devPath;
}

QString UsbDevice::deviceName()const
{
    //if(!handle) return LoadString(cs::unknownDevName);
    return devName;
}

bool UsbDevice::writeControlData(const void* data, size_t len, uint8_t request, uint16_t value, uint16_t index)
{
    if(handle == 0) return false;
    usb_dev_handle* h = (usb_dev_handle*)handle;
    int res = libusb_control_transfer(
            h,
            LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE,
            request,
            value,
            index,
            (uint8_t*)data,
            (uint16_t)len,
            1000);
    return res == (int)len;
}

int UsbDevice::readControlData(void* data, size_t len, uint8_t request, uint16_t value, uint16_t index)
{
    if(handle == 0) return false;
    usb_dev_handle* h = (usb_dev_handle*)handle;
    int res = libusb_control_transfer(
            h,
            LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_DEVICE,
            request,
            value,
            index,
            (uint8_t*)data,
            (uint16_t)len,
            1000);
    return res;
}


bool UsbDevice::close()
{
    if(handle == 0) return true;
    usb_dev_handle* h = (usb_dev_handle*)handle;
    errorCode = libusb_release_interface(h, 0);
    libusb_close(h);
    handle = 0;
    bool res = this->wait(500);
    qDebug()<<"Usb device close "<<res;
    if(!isFinished()){
        terminate();
    }
    return errorCode == 0;
}

int UsbDevice::lastError() const
{
    return errorCode;
}

QString formatError(int err)
{
    switch(err){
    case LIBUSB_SUCCESS: return "Success";

        /** Input/output error */
    case LIBUSB_ERROR_IO: return "Input/output error";

        /** Invalid parameter */
    case LIBUSB_ERROR_INVALID_PARAM: return "Invalid parameter";

        /** Access denied (insufficient permissions) */
    case LIBUSB_ERROR_ACCESS: return "Access denied (insufficient permissions)";// = -3,

        /** No such device (it may have been disconnected) */
    case LIBUSB_ERROR_NO_DEVICE: return "No such device (it may have been disconnected)";// = -4,

        /** Entity not found */
    case LIBUSB_ERROR_NOT_FOUND: return "Entity not found";// = -5,

        /** Resource busy */
    case LIBUSB_ERROR_BUSY: return "Resource busy";// = -6,

        /** Operation timed out */
    case LIBUSB_ERROR_TIMEOUT: return "Operation timed out";// = -7,

        /** Overflow */
    case LIBUSB_ERROR_OVERFLOW: return "Overflow";// = -8,

        /** Pipe error */
    case LIBUSB_ERROR_PIPE: return "Pipe error";// = -9,

        /** System call interrupted (perhaps due to signal) */
    case LIBUSB_ERROR_INTERRUPTED: return "System call interrupted (perhaps due to signal)";// = -10,

        /** Insufficient memory */
    case LIBUSB_ERROR_NO_MEM: return "Insufficient memory";// = -11,

        /** Operation not supported or unimplemented on this platform */
    case LIBUSB_ERROR_NOT_SUPPORTED: return "Operation not supported or unimplemented on this platform";// = -12,

        /** Other error */
    case LIBUSB_ERROR_OTHER:
    default:
        return "Other error";// = -99
    }
    return "Other error";// = -99
}

QString UsbDevice::lastErrorString() const
{
    return QString("(%1) \"%2\"").arg(errorCode).arg(formatError(errorCode));
}

bool UsbDevice::writeData(const void* data, size_t len, int epNum, int timeout)
{
    if(!handle) return false;
    epNum &= 0x0f;
    int actLen = 0;
    int errorCode = libusb_bulk_transfer((usb_dev_handle*)handle, epNum, (unsigned char*)data, len, &actLen, timeout);
    if(errorCode < 0) return false;
    showBytes(data,actLen,"write");
    return actLen == (int)len;
}

int UsbDevice::readData(void* data, size_t len, int epNum, int timeout)
{
    if(!handle) return false;
    epNum |= 0x80;
    int actLen = 0;
    int errorCode = libusb_bulk_transfer((usb_dev_handle*)handle, epNum, (unsigned char*)data, len, &actLen, timeout);
    if(errorCode < 0) return 0;
    return actLen;
}

void UsbDevice::OnData(const void* data, size_t len)
{
    (void)data;
    (void)len;
}

struct CB_Data
{
    UsbDevice* device;
    unsigned char* buffer;
    struct libusb_transfer* transfer;
    bool   bRun;
};

void request_exit(CB_Data* p)
{
    p->bRun = false;
}

static void cb_data(struct libusb_transfer *transfer)
{
    CB_Data * p = (CB_Data*) transfer->user_data;
        if (transfer->status != LIBUSB_TRANSFER_COMPLETED) {
                qDebug()<<"img transfer status "<<transfer->status<<"?";
                libusb_free_transfer(transfer);
                p->transfer = 0;
                request_exit(p);
                return;
        }

        p->device->OnData(transfer->buffer, transfer->actual_length);
        showBytes(transfer->buffer, transfer->actual_length, "read");

        if (libusb_submit_transfer(p->transfer) < 0)
                request_exit(p);
}

void UsbDevice::run()
{
    if(epForRead == 0 || handle == 0) return;

    unsigned char buffer[4096];

    CB_Data data = {this, buffer, 0, true};

    data.transfer = libusb_alloc_transfer(0);

    libusb_fill_bulk_transfer(data.transfer, (usb_dev_handle*)handle, epForRead, buffer,
                    4096, cb_data, &data, 0);

    while(data.bRun){
        struct timeval tv = { 1, 0 };
        libusb_handle_events_timeout(0, &tv);
    }
    if(data.transfer){
        libusb_cancel_transfer(data.transfer);
    }

    while (data.transfer)
        if (libusb_handle_events(NULL) < 0)
            break;

    libusb_free_transfer(data.transfer);
}

QStringList UsbDevice::enumDevice(uint16_t vid, uint16_t pid, bool SN)
{

    QStringList list;
    deviceMap.clear();

    if(device_list){
        libusb_free_device_list(device_list,1);
    }
    //vid = 0; pid = 0;
    ssize_t cnt = libusb_get_device_list(NULL, &device_list);
    if(cnt < 0) return list;
    for (int i = 0; device_list[i]; i++)
    {
        libusb_device*  dev = device_list[i];
        struct libusb_device_descriptor desc;
        libusb_get_device_descriptor(dev, &desc);
        if( (desc.idVendor == vid || 0 == vid) && (desc.idProduct == pid || 0 == pid)){
            char sn[256] = {0};
            usb_dev_handle * handle = 0;
            QString str = getDevicePath(dev);
            int res = 0;
            res = libusb_open(dev, &handle);
            if(res < 0) handle = 0;
            if(SN && res >= 0 && desc.iSerialNumber != 0){
                res = libusb_get_string_descriptor(handle,desc.iSerialNumber,0,(uint8_t*)sn,256);
            }
            if(handle){
                libusb_close(handle);
            }
            if(res > 0 && SN){
                str = translateUSBString(sn,res);
                list.append(str);
            }else{
                list.append(str);
            }
            deviceMap.insert(str, dev);
        }
    }
    //libusb_free_device_list(devs,1);
    return list;
}

bool UsbDevice::Init(void)
{
    if(libusb_init(0) < 0)
        return false;
    return true;
}
