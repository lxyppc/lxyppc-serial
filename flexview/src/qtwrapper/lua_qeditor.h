#ifndef LUA_QEDITOR_H
#define LUA_QEDITOR_H
#include "lua_qt_wrapper.hpp"
#include "hexeditor/qhexedit.h"
#include "../qluaedit.h"
typedef class_<QHexEdit,QWidget>                    LQHexEdit;
typedef class_<QLuaEdit,QTextEdit>                  LQLuaEdit;

LQHexEdit  lqhexedit();
LQLuaEdit lqluaedit();


#endif



