#include "lua_qdialog.h"


QDialog* lqdialog_init(QDialog* widget, const object& obj)
{
    lqwidget_init(widget, obj);
    return widget;
}

template<>
void table_init_general<QDialog>(const luabind::argument & arg, const object& obj)
{
    lqdialog_init(construct<QDialog>(arg), obj);
}


QFrame* lqframe_init(QFrame* widget, const object& obj)
{
    lqwidget_init(widget, obj);
    return widget;
}

template<>
void table_init_general<QFrame>(const luabind::argument & arg, const object& obj)
{
    lqframe_init(construct<QFrame>(arg), obj);
}

LQDialog  lqdialog()
{
    return
    class_<QDialog, QWidget>("QDialog")
        .def(constructor<>())
        .def(constructor<QWidget*>())
        .def("__call", lqdialog_init)
        .def("__init", table_init_general<QDialog>)
    ;
}

LQFrame lqframe()
{
    return
    class_<QFrame, QWidget>("QFrame")
        .def(constructor<>())
        .def(constructor<QWidget*>())
        .def("__call", lqframe_init)
        .def("__init", table_init_general<QFrame>)
    ;
}
