#ifndef LUA_QOBJECT_H
#define LUA_QOBJECT_H
#include "lua_qt_wrapper.hpp"
#include "boost/function.hpp"
#include "luabind/class_info.hpp"
using namespace luabind;

typedef class_<QObject>                     LQObject;
typedef class_<QWidget, QObject>            LQWidget;
typedef class_<QVariant>                    LQVariant;
typedef class_<QUiLoader, QObject>          LQUiLoader;
//typedef class_<QFormBuilder>                LQFormBuilder;

LQObject lqobject();
LQWidget lqwidget();
LQVariant lqvariant();
LQUiLoader lquiloader();
//LQFormBuilder lqformbuilder();
#endif
