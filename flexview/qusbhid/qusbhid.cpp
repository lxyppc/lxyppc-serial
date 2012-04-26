#include "qusbhid.h"

QUsbHid::QUsbHid(QObject *parent,QueryMode mode) :
    QIODevice(parent),
    m_queryMode(mode)
{
    initial();
}

QUsbHid::QUsbHid(const QString& path, QObject *parent,QueryMode mode) :
    QIODevice(parent),
     m_queryMode(mode),
    m_path(path)
{
    initial();
}

QUsbHid::~QUsbHid()
{
    deinitial();
}

void QUsbHid::initial()
{
    mutex = new QMutex(QMutex::Recursive);

    Win_Handle=INVALID_HANDLE_VALUE;
    ZeroMemory(&overlap, sizeof(OVERLAPPED));
    overlap.hEvent = CreateEvent(NULL, true, false, NULL);
    winEventNotifier = 0;
    bytesToWriteLock = new QReadWriteLock;
    _bytesToWrite = 0;
}

void QUsbHid::deinitial()
{
    CloseHandle(overlap.hEvent);
    delete bytesToWriteLock;
    if (isOpen()) {
        close();
    }
    delete mutex;
}

bool QUsbHid::open(OpenMode mode)
{
    DWORD dwFlagsAndAttributes = 0;
    if (queryMode() == QUsbHid::EventDriven)
        dwFlagsAndAttributes += FILE_FLAG_OVERLAPPED;
    QMutexLocker lock(mutex);
    if (mode == QIODevice::NotOpen)
        return isOpen();
    Win_Handle=CreateFileA(m_path.toAscii(), GENERIC_READ|GENERIC_WRITE,
                          0, NULL, OPEN_EXISTING, dwFlagsAndAttributes, NULL);

    if (Win_Handle!=INVALID_HANDLE_VALUE) {
        QIODevice::open(mode);

        //init event driven approach
        if (queryMode() == QUsbHid::EventDriven) {
            winEventNotifier = new QWinEventNotifier(overlap.hEvent, this);
            connect(winEventNotifier, SIGNAL(activated(HANDLE)), this, SLOT(onWinEvent(HANDLE)));
            ::ReadFile(Win_Handle, );
        }

    }else{
        return false;
    }
    return isOpen();
}

void QUsbHid::close()
{
}

void QUsbHid::flush()
{
    QMutexLocker lock(mutex);
    if (isOpen()) {
        FlushFileBuffers(Win_Handle);
    }
}

void QUsbHid::onWinEvent(HANDLE h)
{
    QMutexLocker lock(mutex);
    if(h == overlap.hEvent) {
    }
}

QString QUsbHid::errorString()const
{
    QString res;
#ifdef Q_OS_WIN
    LPTSTR lpMsgBuf = 0;
    DWORD ret = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS,
                  0,
                  ::GetLastError(),
                  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                  (LPTSTR) &lpMsgBuf, 0, 0);
#ifdef UNICODE
    res = QString::fromWCharArray( (LPTSTR)lpMsgBuf);
#else
    res =  QString::fromLocal8Bit((LPTSTR) lpMsgBuf);
#endif
    res.remove(QChar('\n'));
    LocalFree(lpMsgBuf);
    (void)ret;
#endif
    return res;
}

