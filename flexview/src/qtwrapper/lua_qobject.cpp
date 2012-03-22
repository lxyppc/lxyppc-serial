#include "lua_qt_wrapper.hpp"
using namespace luabind;

LQObject lqobject()
{
    return
    class_<QObject>("QObject")
            .def(constructor<>())
            .def(constructor<QObject*>());
}

LQWidget lqwidget()
{
    return
    class_<QWidget, QObject>("QWidget")
            .def(constructor<>())
            .def("show",&QWidget::show)
            .def("showMaximized",&QWidget::showMaximized)
            .def("setWindowTitle",&QWidget::setWindowTitle)
            .def("setGeometry", (void (QWidget::*)(int, int, int, int))&QWidget::setGeometry);
}

