#include "lua_qdialog.h"
#include "qluaslot.h"

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

static setter_map<QGroupBox> lqgroupbox_set_map;
QGroupBox* lqgroupbox_init(QGroupBox* widget, const object& obj)
{
    lqwidget_init(widget, obj);
    return lq_general_init(widget, obj, lqgroupbox_set_map);
}

template<>
void table_init_general<QGroupBox>(const luabind::argument & arg, const object& obj)
{
    lqgroupbox_init(construct<QGroupBox>(arg), obj);
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

SIGNAL_PROPERYT(lqgroupbox, clicked, QGroupBox, "(bool)" )
SIGNAL_PROPERYT(lqgroupbox, toggled, QGroupBox, "(bool)" )

LQGroupBox lqgroupbox()
{
    return
    myclass_<QGroupBox, QWidget>("QGroupBox",lqgroupbox_set_map)
        .def(constructor<>())
        .def(constructor<QWidget*>())
        .def(constructor<const QString&>())
        .def(constructor<const QString&, QWidget*>())
        .def("__call", lqgroupbox_init)
        .def("__init", table_init_general<QGroupBox>)
        .property("flat", &QGroupBox::isFlat ,&QGroupBox::setFlat)
        .property("checkable", &QGroupBox::isCheckable,&QGroupBox::setCheckable)
        .property("checked", &QGroupBox::isChecked ,&QGroupBox::setChecked)
        .property("title", &QGroupBox::title,&QGroupBox::setTitle)
        .sig_prop(lqgroupbox, clicked)
        .sig_prop(lqgroupbox, toggled)
    ;
}
