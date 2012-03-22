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

LQObject lqobject();
LQWidget lqwidget();

LQLayout lqlayout();
LQStackedLayout lqstatckedlayout();
LQGridLayout lqgridlayout();
LQFormLayout lqformlayout();
LQBoxLayout  lqboxlayout();
LQVBoxLayout lqvboxlayout();
LQHBoxLayout lqhboxlayout();

#endif
