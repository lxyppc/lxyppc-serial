#ifndef LUA_QDIALOG_H
#define LUA_QDIALOG_H

#include "lua_qt_wrapper.hpp"

typedef class_<QDialog, QWidget> LQDialog;
typedef class_<QFrame, QWidget> LQFrame;

LQDialog  lqdialog();
LQFrame lqframe();
#endif // LUA_QDIALOG_H
