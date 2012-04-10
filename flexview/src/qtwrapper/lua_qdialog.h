#ifndef LUA_QDIALOG_H
#define LUA_QDIALOG_H

#include "lua_qt_wrapper.hpp"

typedef class_<QDialog, QWidget> LQDialog;
typedef class_<QFrame, QWidget> LQFrame;
typedef class_<QGroupBox, QWidget> LQGroupBox;

LQDialog  lqdialog();
LQFrame lqframe();
LQGroupBox lqgroupbox();
#endif // LUA_QDIALOG_H
