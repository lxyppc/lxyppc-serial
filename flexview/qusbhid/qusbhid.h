#ifndef QUSBHID_H
#define QUSBHID_H

#include <QIODevice>
#include <QMutex>
#include <QMutexLocker>
#include <QReadWriteLock>

#ifdef Q_OS_WIN
    #include <windows.h>
    #include <setupapi.h>
    #include <dbt.h>
    #include "qwineventnotifier_p.h"
#endif /*Q_OS_WIN*/

class QUsbHid : public QIODevice
{
    Q_OBJECT
public:
    enum QueryMode {
        Polling,
        EventDriven
    };

    QUsbHid(QObject* parent = 0, QueryMode mode = EventDriven);
    QUsbHid(const QString& path, QObject* parent = 0, QueryMode mode = EventDriven);
    ~QUsbHid();

    void setPath(const QString& path){ m_path = path; }
    QString path()const { return m_path; }

    void setQueryMode(int mode) {m_queryMode = QueryMode(mode); }
    int queryMode() const { return m_queryMode; }

    void setTimeout(int timeout){ m_timeout = timeout; }
    int timeout()const { return m_timeout; }

    bool open(OpenMode mode);
    bool isSequential() const {return true; }
    void close();
    void flush();

    QString errorString()const;

signals:

public slots:
#ifdef Q_OS_WIN
    private slots:
        void onWinEvent(HANDLE h);
#endif
protected:
    void initial();
    void deinitial();

    QueryMode m_queryMode;
    QString m_path;
    int m_timeout;
    QMutex* mutex;

#if (defined Q_OS_WIN)
        HANDLE Win_Handle;
        OVERLAPPED overlap;
        QWinEventNotifier *winEventNotifier;
        DWORD eventMask;
        QList<OVERLAPPED*> pendingWrites;
        QReadWriteLock* bytesToWriteLock;
        qint64 _bytesToWrite;
#endif
};

#endif // QUSBHID_H
