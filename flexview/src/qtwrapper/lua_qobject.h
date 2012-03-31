#ifndef LUA_QOBJECT_H
#define LUA_QOBJECT_H
#include "lua_qt_wrapper.hpp"
#include "boost/function.hpp"
#include "luabind/class_info.hpp"
using namespace luabind;

typedef class_<QObject>                     LQObject;
typedef class_<QWidget, QObject>            LQWidget;

LQObject lqobject();
LQWidget lqwidget();

#endif
