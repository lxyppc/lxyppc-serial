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

//*
LQLayout lqlayout()
{
    return
    class_<QLayout,QLayoutWarp>("QLayout")
            .def(constructor<>())
            .def(constructor<QWidget*>())
    ;
}
//*/
LQStackedLayout lqstatckedlayout()
{
    return
    class_<QStackedLayout, QLayout>("QStackedLayout")
        .def(constructor<>())
    ;
}
LQGridLayout lqgridlayout();
LQFormLayout lqformlayout();
LQBoxLayout  lqboxlayout()
{
    return
    class_<QBoxLayout, QLayout>("QBoxLayout")
        .def(constructor<QBoxLayout::Direction>())
        .def(constructor<QBoxLayout::Direction,QWidget*>())
        .def("addLayout", (void (QBoxLayout::*)(QLayout *))&QBoxLayout::addLayout)
        .def("addLayout", (void (QBoxLayout::*)(QLayout *, int))&QBoxLayout::addLayout)
        .def("addWidget", (void	(QBoxLayout::*)( QWidget *, int, Qt::Alignment)) &QBoxLayout::addWidget)
        .def("addWidget", (void	(QBoxLayout::*)( QWidget *, int)) &QBoxLayout::addWidget)
        .def("addWidget", (void	(QBoxLayout::*)( QWidget *)) &QBoxLayout::addWidget)
    ;
}

LQVBoxLayout lqvboxlayout()
{
    return
    class_<QVBoxLayout, QBoxLayout>("QVBoxLayout")
        .def(constructor<>())
        .def(constructor<QWidget*>())
    ;
}
LQHBoxLayout lqhboxlayout()
{
    return
    class_<QHBoxLayout, QBoxLayout>("QHBoxLayout")
        .def(constructor<>())
        .def(constructor<QWidget*>())
    ;
}

