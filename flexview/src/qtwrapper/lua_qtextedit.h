#ifndef LUA_QTEXTEDIT_H
#define LUA_QTEXTEDIT_H
#include "lua_qt_wrapper.hpp"
#include "qluaslot.h"
typedef class_<QLabel, QFrame>                      LQLabel;
typedef class_<QTextEdit, QAbstractScrollArea>      LQTextEdit;
typedef class_<QLineEdit, QWidget>                  LQLineEdit;

LQLabel lqlabel();
LQTextEdit lqtextedit();
LQLineEdit lqlineedit();
#endif

