#include "lua_qt_wrapper.hpp"
#include "luabind/class_info.hpp"
#include "luabind/detail/object_rep.hpp"
using namespace luabind;

QString toString(const object& obj)
{
    switch(type(obj)){
    case LUA_TNUMBER:
        return QString("%1").arg(object_cast<int>(obj));
    case LUA_TSTRING:
        return object_cast<QString>(obj);
    case LUA_TUSERDATA:
    case LUA_TFUNCTION:
        {
            detail::object_rep* p = detail::get_instance(obj.interpreter(),0);
            if(p){
                qDebug()<<"raw: "<<p->crep()->name();
            }
        }
        return QString::fromLocal8Bit(get_class_info(argument(from_stack(obj.interpreter(),0))).name.c_str());
    }
    return QString::fromLocal8Bit("Unkonwn?");
}

QMainWindow* lqmainwindow_init(QMainWindow* widget, const object& init_table)
{
    lqwidget_init(widget,init_table);
    if(type(init_table) == LUA_TTABLE){
        for (iterator i(init_table), e; i != e; ++i){
            if(is_class<QDockWidget>(*i)){
                Qt::DockWidgetArea area = Qt::BottomDockWidgetArea;
                if(type(i.key()) == LUA_TSTRING){
                    QString key = object_cast<QString>(i.key());
                    if(key.compare("leftdock",Qt::CaseInsensitive) == 0){
                        area = Qt::LeftDockWidgetArea;
                    }else if(key.compare("rightdock",Qt::CaseInsensitive) == 0){
                        area = Qt::RightDockWidgetArea;
                    }else if(key.compare("topdock",Qt::CaseInsensitive) == 0){
                        area = Qt::TopDockWidgetArea;
                    }else if(key.compare("bottomdock",Qt::CaseInsensitive) == 0){
                        area = Qt::BottomDockWidgetArea;
                    }
                }
                widget->addDockWidget(area, object_cast<QDockWidget*>(*i));
            }else

            if(type(*i) == LUA_TUSERDATA){
                //qDebug()<<"type:"<<toString(*i);
                if(q_cast(*i, &QMainWindow::setMenuBar, widget)){
                }else if(q_cast(*i, (void (QMainWindow::*)(QToolBar *))&QMainWindow::addToolBar, widget)){
                }else if(q_cast(*i, (QAction*(QMenuBar::*)(QMenu*))&QMenuBar::addMenu, widget->menuBar())){
                }else if(q_cast(*i, (void(QMenuBar::*)(QAction*))&QMenuBar::addAction, widget->menuBar())){
                }else if(q_cast(*i, (void (QMainWindow::*)(QStatusBar *))&QMainWindow::setStatusBar,widget)){
                    widget->addDockWidget(Qt::TopDockWidgetArea, new QDockWidget("123"));
                }else{
                    q_cast(*i, &QMainWindow::setCentralWidget, widget);
                }
            }
            //qDebug()<<"key:"<<toString(i.key())<<"val:"<<toString(*i);
        }
    }
    return widget;
}

void table_init_qmainwindow(const luabind::argument & arg, const object& obj)
{
    lqmainwindow_init(construct<QMainWindow>(arg), obj);
}

QByteArray get_state(QMainWindow* w)
{
    return w->saveState();
}

void set_state(QMainWindow* w, const QByteArray& arr)
{
    w->restoreState(arr);
}

LQMainWindow lqmainwindow()
{
    return
    class_<QMainWindow, QWidget>("QMainWindow")
        .def(constructor<>())
        .def("addToolBar", (QToolBar *(QMainWindow::*)(const QString &))&QMainWindow::addToolBar)
        .def("addToolBar", (void (QMainWindow::*)(Qt::ToolBarArea, QToolBar *))&QMainWindow::addToolBar)
        .def("addToolBar", (void (QMainWindow::*)(QToolBar *))&QMainWindow::addToolBar)
        .def("removeToolBar", &QMainWindow::removeToolBar)
        .def("__call", &lqmainwindow_init)
        .def("__init", &table_init_qmainwindow)
        .property("menuBar", &QMainWindow::menuBar, &QMainWindow::setMenuBar)
        .property("centralWidget", &QMainWindow::centralWidget, &QMainWindow::setCentralWidget)
        .property("state", get_state, set_state)
        .property("statusBar", &QMainWindow::statusBar, &QMainWindow::setStatusBar)
        ;
}

QDockWidget* lqdockwidget_init(QDockWidget* widget, const object& init_table)
{
    if(type(init_table) == LUA_TTABLE){
        for (iterator i(init_table), e; i != e; ++i){

            if(type(i.key()) == LUA_TSTRING){
                QString key = object_cast<QString>(i.key());
                if(key.compare("widget",Qt::CaseInsensitive) == 0){
                    q_cast(*i, &QDockWidget::setWidget, widget);
                }else if(key.compare("titleBarWidget",Qt::CaseInsensitive) == 0){
                    q_cast(*i, &QDockWidget::setTitleBarWidget, widget);
                }else if(key.compare("titlebar",Qt::CaseInsensitive) == 0){
                    q_cast(*i, &QDockWidget::setTitleBarWidget, widget);
                }
            }else{
                q_cast(*i, &QDockWidget::setWidget, widget);
            }
        }
    }
    return widget;
}

void table_init_qdockwidget(const luabind::argument & arg, const object& obj)
{
    lqdockwidget_init(construct<QDockWidget>(arg), obj);
}

LQDockWidget lqdockwidget()
{
    return
    class_<QDockWidget, QWidget>("QDockWidget")
        .def(constructor<>())
        .def(constructor<QWidget*>())
        .def(constructor<const QString& >())
        .def(constructor<const QString&, QWidget*>())
        .def("toggleViewAction", &QDockWidget::toggleViewAction)

        .def("__call", &lqdockwidget_init)
        .def("__init", &table_init_qdockwidget)

        .property("floating", &QDockWidget::isFloating, &QDockWidget::setFloating )
        .property("windowTitle", &QDockWidget::windowTitle, &QDockWidget::setWindowTitle )
        .property("widget", &QDockWidget::widget, &QDockWidget::setWidget)
        .property("titleBarWidget", &QDockWidget::titleBarWidget, &QDockWidget::setTitleBarWidget)
        .property("allowedAreas", &QDockWidget::allowedAreas, &QDockWidget::setAllowedAreas)
        .property("features", &QDockWidget::features, &QDockWidget::setFeatures)
        ;
}

LQStatusBar lqstatusbar()
{
    return
    class_<QStatusBar, QWidget>("QStatusBar")
         .def(constructor<>())
         .def(constructor<QWidget*>())
         .def("addWidget", &QStatusBar::addWidget)
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
    void showText(){
        qDebug()<<"showText";
    }

    QString text(){
        return "test";
    }

    void setText(const QString& t){
        (void)t;
    }
};

QTestType* init_test_type(QTestType* x, const object& init_table)
{
    (void)init_table;
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
        .def("showText", &QTestType::showText)
        .property("showText", &QTestType::text, &QTestType::setText)
        ;
}
