#include "lua_qt_wrapper.hpp"
#include "luabind/detail/object_rep.hpp"
using namespace luabind;

QMainWindow* lqmainwindow_init(QMainWindow* widget, const object& init_table)
{
    if(type(init_table) != LUA_TTABLE) return widget;

    for(iterator i(init_table), e; i != e; ++i){
        if(type(*i) == LUA_TUSERDATA){
            try{
                QMainWindow* w = object_cast<QMainWindow*>(*i);
                widget-> layout()->addWidget(w);
            }
            catch (...)
            {
                    std::cerr << "Terminated with unknown exception   edsdsg\n";
            }
        }else if(type(*i) == LUA_TTABLE){
        }
        qDebug()<<"obj"<<"  "<<type(*i);
    }

    object mt = getmetatable(init_table);
    for(iterator i(mt), e; i != e; ++i){
        qDebug()<<"obj"<<"  "<<type(*i)<<"  "<<object_cast<int>(*i);
    }

    return widget;
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
        .def("__call", &lqmainwindow_init)
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
    (void)init_table;
    qDebug()<<"QTestType call";
    return x;
}

LQTestType lqtesttype()
{
    return
    class_<QTestType>("QTestType")
        .def(constructor<>())
        //.def(constructor<const object&>())
        .def("__call", init_test_type)
        ;
}
