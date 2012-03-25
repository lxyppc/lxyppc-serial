#include "lua_qt_wrapper.hpp"
#include "luabind/detail/constructor.hpp"
#include "luabind/class_info.hpp"
using namespace luabind;

template<typename T>
T* construct(const argument& arg){
    luabind::detail::construct<T, std::auto_ptr<T>, constructor<>::signature >()(arg);
    return object_cast<T*>(arg);
}

QString toString(const object& obj)
{
    switch(type(obj)){
    case LUA_TNUMBER:
        return QString("%1").arg(object_cast<int>(obj));
    case LUA_TSTRING:
        return object_cast<QString>(obj);
    case LUA_TUSERDATA:
    case LUA_TFUNCTION:
        return QString::fromLocal8Bit(get_class_info(argument(from_stack(obj.interpreter(),0))).name.c_str());
    }
    return QString::fromLocal8Bit("Unkonwn?");
}

QMainWindow* lqmainwindow_init(QMainWindow* widget, const object& init_table)
{
    for (iterator i(init_table), e; i != e; ++i){
        qDebug()<<"key:"<<toString(i.key())<<"val:"<<toString(*i);
    }
    //enum_table(init_table, qmainwindowparam, widget);
    return widget;
}

void table_init_qmainwindow(const luabind::argument & arg, const object& obj)
{
    lqmainwindow_init(construct<QMainWindow>(arg), obj);
}

LQMainWindow lqmainwindow()
{
    return
    class_<QMainWindow, QWidget>("QMainWindow")
        .def(constructor<>())
        .def("setCentralWidget",&QMainWindow::setCentralWidget)
        .def("menuBar",(QMenuBar *(QMainWindow::*)()const)&QMainWindow::menuBar)
        .def("addToolBar", (QToolBar *(QMainWindow::*)(const QString &))&QMainWindow::addToolBar)
        .def("addToolBar", (void (QMainWindow::*)(Qt::ToolBarArea, QToolBar *))&QMainWindow::addToolBar)
        .def("addToolBar", (void (QMainWindow::*)(QToolBar *))&QMainWindow::addToolBar)
        //.def("__call", &lqmainwindow_init)
        .def("__init", &table_init_qmainwindow)
        ;
}

class QTestType
{
public:
    QTestType(){
        qDebug()<<"QTestType()";
    }
    QTestType(const object& obj){
        (void)obj;
        qDebug()<<"QTestType";
    }
};

QTestType* init_test_type(QTestType* x, const object& init_table)
{
    enum_table(init_table, 0, x);
    return x;
}


void init_tp(const luabind::argument & arg, const object& obj)
{
    init_test_type(construct<QTestType>(arg), obj);
}



LQTestType lqtesttype()
{
    return
    class_<QTestType>("QTestType")
        .def(constructor<>())
        //.def(constructor<const object&>())
        .def("__call", init_test_type)
        .def("__init", init_tp)
        ;
}
