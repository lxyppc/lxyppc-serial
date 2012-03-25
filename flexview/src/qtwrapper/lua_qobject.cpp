#include "lua_qt_wrapper.hpp"
#include "boost/function.hpp"
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

template<typename OT, typename T>
T obj_value_cast(const OT & obj, T def)
{
    if(obj && type(obj) == LUA_TNUMBER){
        return object_cast<T>(obj);
    }
    return def;
}

template<typename T>
T get_property(const object& obj, T def, const char* p1 = 0, const char* p2 = 0, const char* p3 = 0, const char* p4 = 0);
template<>
int get_property(const object& obj, int def, const char* p1, const char* p2, const char* p3, const char* p4)
{
    if(type(obj) != LUA_TTABLE) return def;
    if(p1 && obj[p1] && type(obj[p1]) == LUA_TNUMBER){
        return object_cast<int>(obj[p1]);
    }else if(p2 && obj[p2] && type(obj[p2]) == LUA_TNUMBER){
        return object_cast<int>(obj[p2]);
    }else if(p3 && obj[p3] && type(obj[p3]) == LUA_TNUMBER){
        return object_cast<int>(obj[p3]);
    }else if(p4 && obj[p4] && type(obj[p4]) == LUA_TNUMBER){
        return object_cast<int>(obj[p4]);
    }
    return def;
}

template<>
QString get_property(const object& obj, QString def, const char* p1, const char* p2, const char* p3, const char* p4)
{
    if(type(obj) != LUA_TTABLE) return def;
    if(p1 && obj[p1] && type(obj[p1]) == LUA_TSTRING){
        return object_cast<const char*>(obj[p1]);
    }else if(p2 && obj[p2] && type(obj[p2]) == LUA_TSTRING){
        return object_cast<const char*>(obj[p2]);
    }else if(p3 && obj[p3] && type(obj[p3]) == LUA_TSTRING){
        return object_cast<const char*>(obj[p3]);
    }else if(p4 && obj[p4] && type(obj[p4]) == LUA_TSTRING){
        return object_cast<const char*>(obj[p4]);
    }
    return def;
}

typedef boost::function<void(QWidget*, int)> set_int_t;

struct my_les{
bool operator()(const QString& l, const QString& r){
    return l.compare(r, Qt::CaseInsensitive) < 0;
}
};

static std::map<QString, set_int_t,my_les> lqwidget_set_map;

QWidget* lqwidget_init(QWidget* widget, const object& obj)
{
    //QRect rect = widget->geometry();
    QString styleSheet = widget->styleSheet();
    //rect.setX( get_property(obj, rect.x(), "x", "X") );
    //rect.setY( get_property(obj, rect.y(), "y", "Y") );
    //rect.setWidth( get_property(obj, rect.width(), "w", "W", "width", "Width") );
    //rect.setHeight( get_property(obj, rect.height(), "h", "H", "height", "Height") );
    styleSheet = get_property(obj, styleSheet, "styleSheet");
    //widget->setGeometry( rect );
    widget->setStyleSheet(styleSheet);

    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj), e; i != e; ++i){
            if(type(i.key()) == LUA_TSTRING){
                QString key = object_cast<QString>(i.key());
                if(lqwidget_set_map.find(key) != lqwidget_set_map.end()){
                    if(type(*i) == LUA_TNUMBER){
                        qDebug()<<"Set key:"<<key<<"val:"<<object_cast<int>(*i);
                        lqwidget_set_map[key](widget, object_cast<int>(*i));
                    }
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
    rect.setWidth(width);
    w->setGeometry(rect);
}

void lqwidget_set_height(QWidget* w, int height)
{
    QRect rect = w->geometry();
    rect.setHeight(height);
    w->setGeometry(rect);
}

static struct {
    const char* name[8];
    set_int_t func;
}init_map[] = {
    { {"x"}, lqwidget_set_x},
    { {"y"}, lqwidget_set_y},
    { {"w","width"}, lqwidget_set_width},
    { {"h","height"}, lqwidget_set_height},
};

template<typename T>
void for_all(const T& t)
{
    for(typename T::const_iterator it = t.begin();it!=t.end();it++){
        qDebug()<<it->first;
    }
}

//boost::function_traits<>::arity
//boost::function_traits<>:
LQWidget lqwidget()
{
    for(unsigned int i=0;i<sizeof(init_map)/sizeof(init_map[0]);i++){
        const char** p = init_map[i].name;
        while(*p){
            lqwidget_set_map[QString::fromLocal8Bit(*p)] = init_map[i].func;
            p++;
        }
    }
    //qDebug()<<boost::function_traits<void(int,int)>::arity;
    //boost::function<void(int,int)>::type;
    //qDebug()<<boost::function_traits<void(int,int)>::arity;
//std::map<QString, set_int_t, my_les>::const_iterator
    for_all(lqwidget_set_map);
    return
    class_<QWidget, QObject>("QWidget")
            .def(constructor<>())
            .def("show",&QWidget::show)
            .def("showMaximized",&QWidget::showMaximized)
            .def("setWindowTitle",&QWidget::setWindowTitle)
            .def("setGeometry", (void (QWidget::*)(int, int, int, int))&QWidget::setGeometry)
            .def("addAction", &QWidget::addAction)
            .def("init", &lqwidget_init)
            .def("__call", &lqwidget_init)
            .def("actionCount", lqwidget_actionCount)
            .def("action",lqwidget_action)
            .property("x", &QWidget::x, lqwidget_set_x)
            .property("y", &QWidget::y, lqwidget_set_y)
            .property("width", &QWidget::width, lqwidget_set_width)
            .property("heigth", &QWidget::height, lqwidget_set_height)
            .property("enabled", &QWidget::isEnabled, &QWidget::setEnabled)
            .property("styleSheet", &QWidget::styleSheet, &QWidget::setStyleSheet)
            ;
}

