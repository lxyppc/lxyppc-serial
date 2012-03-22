#include "lua_qt_wrapper.hpp"
using namespace luabind;

/*
LQLayout lqlayout()
{
    return
    class_<QLayout,QObject>("QLayout")
            .def(constructor<>())
            .def(constructor<QWidget*>())
            .def("activate",&QLayout::activate)
            .def("addWidget", &QLayout::addWidget)
            .def("contentsMargins", &QLayout::contentsMargins)
            .def("contentsRect", &QLayout::contentsRect)
            .def("getContentsMargins", &QLayout::getContentsMargins)
            .def("isEnabled", &QLayout::isEnabled)
            .def("count", &QLayout::count)
            .def("indexOf", &QLayout::indexOf)
            .def("menuBar", &QLayout::menuBar);
}
*/
LQStackedLayout lqstatckedlayout();
LQGridLayout lqgridlayout();
LQFormLayout lqformlayout();
LQBoxLayout  lqboxlayout();
LQVBoxLayout lqvboxlayout();
LQHBoxLayout lqhboxlayout();

