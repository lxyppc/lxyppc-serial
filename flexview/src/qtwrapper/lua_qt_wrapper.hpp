#ifndef LUA_QT_WRAPPER_HPP
#define LUA_QT_WRAPPER_HPP
#include <QtGui>
#include "lua.hpp"
#include <luabind/luabind.hpp>
#include "converter.hpp"

using namespace luabind;

typedef class_<QObject>                     LQObject;
typedef class_<QWidget, QObject>            LQWidget;
typedef class_<QLayout, QObject>            LQLayout;
typedef class_<QStackedLayout, QLayout>     LQStackedLayout;
typedef class_<QGridLayout, QLayout>        LQGridLayout;
typedef class_<QFormLayout, QLayout>        LQFormLayout;
typedef class_<QBoxLayout, QLayout>         LQBoxLayout;
typedef class_<QVBoxLayout, QBoxLayout>     LQVBoxLayout;
typedef class_<QHBoxLayout, QBoxLayout>     LQHBoxLayout;

typedef class_<QIcon>                       LQIcon;
typedef class_<QAction,QObject>             LQAction;
typedef class_<QMenuBar,QWidget>            LQMenuBar;
typedef class_<QMenu,QWidget>               LQMenu;

typedef class_<QMainWindow,QWidget>         LQMainWindow;

LQObject lqobject();
LQWidget lqwidget();

LQLayout lqlayout();
LQStackedLayout lqstatckedlayout();
LQGridLayout lqgridlayout();
LQFormLayout lqformlayout();
LQBoxLayout  lqboxlayout();
LQVBoxLayout lqvboxlayout();
LQHBoxLayout lqhboxlayout();

LQAction lqaction();
LQMenuBar lqmenubar();
LQMenu  lqmenu();

LQMainWindow lqmainwindow();

LQIcon  lqicon();

class QTestType;
typedef class_<QTestType>         LQTestType;
LQTestType lqtesttype();

typedef void (*enum_func_t)(void* context, const object& key, const object& value);

void enum_table(const object& table, enum_func_t enum_func, void* context);
#endif
