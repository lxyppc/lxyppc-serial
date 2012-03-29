#include "lua_qt_wrapper.hpp"
#include "boost/function.hpp"
#include "luabind/class_info.hpp"
using namespace luabind;

LQObject lqobject()
{
    return
    class_<QObject>("QObject")
            .def(constructor<>())
            .def(constructor<QObject*>());
}

int lqwidget_actionCount(QWidget* widget)
{
    return widget->actions().count();
}

QAction* lqwidget_action(QWidget* widget, int index)
{
    int cnt = widget->actions().count();
    if(index>=0 && index<cnt)
        return widget->actions().at(index);
    return 0;
}

static setter_map<QWidget> lqwidget_set_map;

QWidget* lqwidget_init(QWidget* widget, const object& obj)
{
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj), e; i != e; ++i){
            if(type(i.key()) == LUA_TSTRING){
                QString key = object_cast<QString>(i.key());
                if(lqwidget_set_map.find(key) != lqwidget_set_map.end()){
                    lqwidget_set_map[key](widget,*i);
                }
            }
        }
    }
    return widget;
}


void lqwidget_set_x(QWidget* w, int x)
{
    QRect rect = w->geometry();
    rect.setX(x);
    w->setGeometry(rect);
}

void lqwidget_set_y(QWidget* w, int y)
{
    QRect rect = w->geometry();
    rect.setY(y);
    w->setGeometry(rect);
}

void lqwidget_set_width(QWidget* w, int width)
{
    QRect rect = w->geometry();
    qDebug()<<"set W:"<<width;
    rect.setWidth(width);
    w->setGeometry(rect);
}

void lqwidget_set_height(QWidget* w, int height)
{
    QRect rect = w->geometry();
    qDebug()<<"set H:"<<height;
    rect.setHeight(height);
    w->setGeometry(rect);
}

template<typename T>
void for_all(const T& t)
{
    for(typename T::const_iterator it = t.begin();it!=t.end();it++){
        qDebug()<<it->first;
    }
}

LQWidget lqwidget()
{
    return
    myclass_<QWidget, QObject>("QWidget",lqwidget_set_map)
            .def(constructor<>())
            .def("show",&QWidget::show)
            .def("showMaximized",&QWidget::showMaximized)
            .def("showFullScreen",&QWidget::showFullScreen)
            .def("showMinimized",&QWidget::showMinimized)
            .def("showNormal",&QWidget::showNormal)
            .def("update",(void(QWidget::*)())&QWidget::update)
            .def("close",&QWidget::close)
            .def("hide",&QWidget::hide)
            .def("lower",&QWidget::lower)
            .def("raise",&QWidget::raise)
            .def("repaint",(void(QWidget::*)())&QWidget::repaint)


            .def("setGeometry", (void (QWidget::*)(int, int, int, int))&QWidget::setGeometry)
            .def("addAction", &QWidget::addAction)
            .def("__call", &lqwidget_init)
            .def("actionCount", lqwidget_actionCount)
            .def("action",lqwidget_action)

            .property("windowTitle", &QWidget::windowTitle, &QWidget::setWindowTitle)
            .property("title", &QWidget::windowTitle, &QWidget::setWindowTitle)
            .property("styleSheet", &QWidget::styleSheet, &QWidget::setStyleSheet)
            .property("enabled", &QWidget::isEnabled, &QWidget::setEnabled)
            .property("windowModified", &QWidget::isWindowModified, &QWidget::setWindowModified)
            .property("modified", &QWidget::isWindowModified, &QWidget::setWindowModified)
            .property("visible", &QWidget::isVisible, &QWidget::setVisible)
            .property("hidden", &QWidget::isHidden, &QWidget::setHidden)

            .property("x", &QWidget::x, lqwidget_set_x)
            .property("y", &QWidget::y, lqwidget_set_y)
            .property("width", &QWidget::width, lqwidget_set_width)
            .property("heigth", &QWidget::height, lqwidget_set_height)
            .property("w", &QWidget::width, lqwidget_set_width)
            .property("h", &QWidget::height, lqwidget_set_height)

            .property("maximumHeight", &QWidget::maximumHeight, &QWidget::setMaximumHeight)
            .property("maximumWidth", &QWidget::maximumWidth, &QWidget::setMaximumWidth)
            .property("maxHeight", &QWidget::maximumHeight, &QWidget::setMaximumHeight)
            .property("maxWidth", &QWidget::maximumWidth, &QWidget::setMaximumWidth)
            .property("maxH", &QWidget::maximumHeight, &QWidget::setMaximumHeight)
            .property("maxW", &QWidget::maximumWidth, &QWidget::setMaximumWidth)

            .property("minimumHeight", &QWidget::minimumHeight, &QWidget::setMinimumHeight)
            .property("minimumWidth", &QWidget::minimumWidth, &QWidget::setMinimumWidth)
            .property("minHeight", &QWidget::minimumHeight, &QWidget::setMinimumHeight)
            .property("minWidth", &QWidget::minimumWidth, &QWidget::setMinimumWidth)
            .property("minH", &QWidget::minimumHeight, &QWidget::setMinimumHeight)
            .property("minW", &QWidget::minimumWidth, &QWidget::setMinimumWidth)

            .property("geometry", &QWidget::geometry, (void(QWidget::*)(const QRect&))&QWidget::setGeometry)

            .property("layout", &QWidget::layout, &QWidget::setLayout)

            .scope[
               def("setTabOrder", &QWidget::setTabOrder)
            ]
            ;
}

std::string obj_name(const object& o)
{
    lua_State* L = o.interpreter();
    std::string name;

    o.push(L);
    detail::object_rep* obj = detail::get_instance(L, -1);
    if (!obj)
    {
        name = lua_typename(L, lua_type(L, -1));
        lua_pop(L, 1);
        return name;
    }

    lua_pop(L, 1);
    name = obj->crep()->name();
    return name;
}


bool obj_name_is(const object& o, const char* name){
    object obj = o;
    return strcmp(obj_name(obj).c_str(), name) == 0;
//    lua_State* L = obj.interpreter();
////    std::string str = get_class_info(argument(from_stack(L,0))).name;
////    return strcmp(str.c_str(),name) == 0;
//
//    obj.push(L);
//    detail::object_rep* p = detail::get_instance(L,-1);
//    //lua_pop(L, 1);
//    if(p){
//        return strcmp(p->crep()->name(),name) == 0;
//    }else{
//        return false;
//    }
}

bool obj_name_contain(const object& o, const char* name){
    object obj = o;
    return strstr(obj_name(obj).c_str(), name) != 0;
//    lua_State* L = obj.interpreter();
////    std::string str = get_class_info(argument(from_stack(L,0))).name;
////    return strstr(str.c_str(),name) != 0;
//
//    obj.push(L);
//    detail::object_rep* p = detail::get_instance(L,-1);
//    //lua_pop(L, 1);
//    if(p){
//        return strstr(p->crep()->name(),name) != 0;
//    }else{
//        return false;
//    }
}

#define IS_CLASS(name)  \
    template<>bool is_class<name>(const object& obj){ return obj_name_is(obj,#name);}\
    template<>bool is_class<name*>(const object& obj){ return obj_name_is(obj,#name);}\
    template<>bool is_class<const name&>(const object& obj){ return obj_name_is(obj,#name);}\
    template<>bool is_class<const name*>(const object& obj){ return obj_name_is(obj,#name);}

IS_CLASS(QMenuBar)
IS_CLASS(QToolBar)
IS_CLASS(QDockWidget)
IS_CLASS(QMenu)
//IS_CLASS(QString)
IS_CLASS(QIcon)
IS_CLASS(QAction)
IS_CLASS(QPoint)
IS_CLASS(QRect)
IS_CLASS(QSize)
IS_CLASS(QMargins)
IS_CLASS(QKeySequence)

template<>bool is_class<QString>(const object& obj){ return type(obj) == LUA_TSTRING;}
template<>bool is_class<QWidget*>(const object& obj){ return type(obj) == LUA_TUSERDATA; }
template<>bool is_class<QLayout*>(const object& obj){
    return obj_name_contain(obj, "Layout");
}
template<>bool is_class<QLayout>(const object& obj){
    return obj_name_contain(obj, "Layout");
}
