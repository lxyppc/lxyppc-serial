#ifndef LUA_QPROCESS_H
#define LUA_QPROCESS_H
#include "lua_qt_wrapper.hpp"

typedef class_<QProcessEnvironment>  LQProcessEnvironment;
typedef class_<QProcess,QObject>  LQProcess;
typedef class_<QApplication,QObject>  LQApplication;

LQProcessEnvironment lqprocessenvironment();
LQProcess lqprocess();
LQApplication lqapplication();

#endif // LUA_QPROCESS_H
