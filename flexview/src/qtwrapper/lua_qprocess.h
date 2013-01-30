#ifndef LUA_QPROCESS_H
#define LUA_QPROCESS_H
#include "lua_qt_wrapper.hpp"

typedef class_<QProcessEnvironment>  LQProcessEnvironment;
typedef class_<QProcess,QObject>  LQProcess;
typedef class_<QApplication,QObject>  LQApplication;
typedef class_<QDesktopWidget, QWidget> LQDesktopWidget;
typedef class_<QClipboard, QObject> LQClipboard;
typedef class_<QSound, QObject> LQSound;
typedef class_<QFileSystemWatcher, QObject> LQFileSystemWatcher;
typedef class_<QThread, QObject> LQThread;
typedef class_<QSysInfo>  LQSysInfo;

LQProcessEnvironment lqprocessenvironment();
LQProcess lqprocess();
LQApplication lqapplication();

LQDesktopWidget lqdesktopwidget();
LQClipboard lqclipboard();
LQSound lqsound();
LQFileSystemWatcher lqfilesystemwatcher();
LQThread lqthread();
LQSysInfo lqsysinfo();

#endif // LUA_QPROCESS_H
