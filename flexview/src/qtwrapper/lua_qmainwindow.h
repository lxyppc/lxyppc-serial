#ifndef LUA_QMAINWINDOW_H
#define LUA_QMAINWINDOW_H
#include "lua_qt_wrapper.hpp"
#include "luabind/class_info.hpp"
#include "luabind/detail/object_rep.hpp"
using namespace luabind;

typedef class_<QMainWindow,QWidget>         LQMainWindow;
typedef class_<QDockWidget,QWidget>         LQDockWidget;
typedef class_<QStatusBar,QWidget>          LQStatusBar;

LQMainWindow lqmainwindow();
LQDockWidget lqdockwidget();
LQStatusBar lqstatusbar();

class QTestType;
typedef class_<QTestType>         LQTestType;
LQTestType lqtesttype();
#endif
