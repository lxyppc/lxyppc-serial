#include "lua_qobject.h"
#include <luabind/adopt_policy.hpp>
#include <QtNetwork>

QObject* lqobject_get_filter(QObject* obj)
{
    return obj;
}

struct myFilter : public QObject
{
    myFilter(const object& obj):m_obj(obj){}
    virtual bool eventFilter(QObject * obj, QEvent * evt)
    {
        bool res = false;
        if(type(m_obj) == LUA_TFUNCTION){
            res = call_function<bool>(m_obj,obj,evt);
        }else if(type(m_obj) == LUA_TTABLE){
            object c,f;
            for(iterator i(m_obj),e;i!=e;++i){
                if(type(*i) == LUA_TUSERDATA){
                    c = *i;
                }else if(type(*i) == LUA_TFUNCTION){
                    f = *i;
                }else if(type(*i) == LUA_TSTRING){
                    f = *i;
                }
            }
            if(f && c){
                if(type(f) == LUA_TFUNCTION){
                    res = call_function<bool>(f,c,obj,evt);
                }else if(type(f) == LUA_TSTRING){
                    res = call_member<bool>(c,object_cast<const char*>(f),obj,evt);
                }
            }
        }
        if(res) return res;
        return QObject::eventFilter(obj,evt);
    }
private:
    object m_obj;
};
std::string obj_name(const object& o);
void lqobject_set_filter(QObject* parent, const object& obj)
{
    if(type(obj) == LUA_TUSERDATA){
        try{
            std::string name = obj_name(obj);
            QObject* o = object_cast<QObject*>(obj);
            parent->installEventFilter(o);
            return;
        }catch(...){
        }
    }
    parent->installEventFilter(new myFilter(obj));
}

void installEventFilter_x(QObject* o, QObject* f)
{
    o->installEventFilter(f);
}

LQObject lqobject()
{
    return
    class_<QObject>("QObject")
            .def(constructor<>())
            .def(constructor<QObject*>())
            .def("installEventFilter", installEventFilter_x)
            .def("removeEventFilter", &QObject::removeEventFilter)
            .def("killTimer", &QObject::killTimer)
            .def("startTimer", &QObject::startTimer)
            .def("property", &QObject::property)
            .def("setProperty", &QObject::setProperty)
            .def("setParent", &QObject::setParent)
            .property("objectName", &QObject::objectName, &QObject::setObjectName)
            .property("eventFilter", lqobject_get_filter, lqobject_set_filter)
            .property("parent", &QObject::parent, &QObject::setParent)
   ;
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
    rect.moveLeft(x);
    w->setGeometry(rect);
}

void lqwidget_set_y(QWidget* w, int y)
{
    QRect rect = w->geometry();
    rect.moveTop(y);
    w->setGeometry(rect);
}

void lqwidget_set_width(QWidget* w, int width)
{
    QRect rect = w->geometry();
    //qDebug()<<"set W:"<<width;
    rect.setWidth(width);
    w->setGeometry(rect);
}

void lqwidget_set_height(QWidget* w, int height)
{
    QRect rect = w->geometry();
    //qDebug()<<"set H:"<<height;
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

bool lqwidget_eq(QWidget* l, QWidget* r)
{
    return l == r;
}
namespace luabind{
    QT_EMUN_CONVERTER(Qt::ContextMenuPolicy)
}
ENUM_FILTER(QWidget, contextMenuPolicy, setContextMenuPolicy)
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
            .def("__eq", lqwidget_eq)
            .def("setFocus",(void (QWidget::*)(Qt::FocusReason))&QWidget::setFocus)
            .def("setFocus",(void (QWidget::*)())&QWidget::setFocus)


            .def("setGeometry", (void (QWidget::*)(int, int, int, int))&QWidget::setGeometry)
            .def("addAction", &QWidget::addAction)
            .def("__call", &lqwidget_init)
            .def("actionCount", lqwidget_actionCount)
            .def("action",lqwidget_action)
            .def("saveGeometry", &QWidget::saveGeometry)
            .def("restoreGeometry", &QWidget::restoreGeometry)
            .def("setAttribute", &QWidget::setAttribute)
            .def("testAttribute", &QWidget::testAttribute)

            .property("windowTitle", &QWidget::windowTitle, &QWidget::setWindowTitle)
            .property("windowIcon", &QWidget::windowIcon, &QWidget::setWindowIcon)
            .property("windowIconText", &QWidget::windowIconText, &QWidget::setWindowIconText)
            .property("windowFilePath", &QWidget::windowFilePath, &QWidget::setWindowFilePath)
            .property("title", &QWidget::windowTitle, &QWidget::setWindowTitle)
            .property("styleSheet", &QWidget::styleSheet, &QWidget::setStyleSheet)
            .property("enabled", &QWidget::isEnabled, &QWidget::setEnabled)
            .property("windowModified", &QWidget::isWindowModified, &QWidget::setWindowModified)
            .property("modified", &QWidget::isWindowModified, &QWidget::setWindowModified)
            .property("visible", &QWidget::isVisible, &QWidget::setVisible)
            .property("hidden", &QWidget::isHidden, &QWidget::setHidden)
            .property("mouseTracking", &QWidget::hasMouseTracking, &QWidget::setMouseTracking)
            .property("toolTip", &QWidget::toolTip, &QWidget::setToolTip)
            .property("statusTip", &QWidget::statusTip, &QWidget::setStatusTip)
            .property("whatsThis", &QWidget::whatsThis, &QWidget::setWhatsThis)
            .property("font", &QWidget::font, &QWidget::setFont)
            .property("focus", &QWidget::hasFocus)
            .property("contextMenuPolicy", QWidget_contextMenuPolicy, QWidget_setContextMenuPolicy)

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
            .property("acceptDrops", &QWidget::acceptDrops, &QWidget::setAcceptDrops)

            .class_<QWidget, QObject>::property("cursor", &QWidget::cursor, &QWidget::setCursor)

            .scope[
               def("setTabOrder", &QWidget::setTabOrder)
            ]
            ;
}


void lqvariant_init(const argument& arg, const object& obj)
{
    QVariant* var = construct<QVariant>(arg);
    var->setValue(obj);
}

object lqvariant_to_object(QVariant* var);
QString lqvariant_tostring(QVariant* var)
{
    return QString::fromLocal8Bit("QVariant type:") + QString::fromLocal8Bit( var->typeName());
}

LQVariant lqvariant()
{
    return
    class_<QVariant>("QVariant")
        .def(constructor<>())
        .def(constructor<const QVariant&>())
        .def(constructor<const QString&>())
        .def(constructor<const QSize&>())
        .def(constructor<const QFont&>())
        .def(constructor<const QBrush&>())
        .def(constructor<const QColor&>())
        .def(constructor<const QIcon&>())
        .def(constructor<const QRect&>())
        .def(constructor<const QPoint&>())
        .def(constructor<int>())
        .def("__init", lqvariant_init)
        .def("__tostring", lqvariant_tostring)

        .def("toObject", lqvariant_to_object)
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

#define IS_CLASS2(cls,name)  \
    template<>bool is_class<cls>(const object& obj){ return obj_name_is(obj,#name);}\
    template<>bool is_class<cls*>(const object& obj){ return obj_name_is(obj,#name);}\
    template<>bool is_class<const cls&>(const object& obj){ return obj_name_is(obj,#name);}\
    template<>bool is_class<const cls*>(const object& obj){ return obj_name_is(obj,#name);}

IS_CLASS(QMenuBar)
IS_CLASS(QToolBar)
IS_CLASS(QStatusBar)
IS_CLASS(QDockWidget)
IS_CLASS(QMenu)
//IS_CLASS(QString)
IS_CLASS(QIcon)
IS_CLASS(QAction)
IS_CLASS(QPoint)
IS_CLASS(QLine)
IS_CLASS(QRect)
IS_CLASS(QSize)
IS_CLASS(QMargins)
IS_CLASS(QColor)
IS_CLASS(QBrush)
IS_CLASS(QFont)
IS_CLASS(QKeySequence)
IS_CLASS(QVariant_wrapper)
IS_CLASS2(QListWidgetItem,QListItem)
IS_CLASS2(QTreeWidgetItem,QTreeItem)
IS_CLASS2(QTableWidgetItem,QTableItem)
IS_CLASS(QTableWidgetSelectionRange)
IS_CLASS(QHostAddress)
IS_CLASS(QNetworkInterface)
IS_CLASS(QNetworkAddressEntry)
IS_CLASS(QUrl)

template<>bool is_class<QString>(const object& obj){ return type(obj) == LUA_TSTRING;}
template<>bool is_class<QWidget*>(const object& obj){ return type(obj) == LUA_TUSERDATA; }
template<>bool is_class<QLayout*>(const object& obj){
    return obj_name_contain(obj, "Layout");
}
template<>bool is_class<QLayout>(const object& obj){
    return obj_name_contain(obj, "Layout");
}

template<>bool is_class<double>(const object& obj){
    return type(obj) == LUA_TNUMBER;
}

template<>bool is_class<QRgb>(const object& obj){
    return type(obj) == LUA_TNUMBER;
}

template<>bool is_class<int>(const object& obj){
    return type(obj) == LUA_TNUMBER;
}

bool is_QVariant_wrapper(const luabind::object& obj)
{
    return is_class<QVariant_wrapper>(obj);
}

#define SET_VAL(n) \
else if(name == #n){\
    v.setValue(object_cast<n>(obj));\
    return v;\
}

QVariant var_from(lua_State* L, int index)
{
    QVariant v;
    object obj(luabind::from_stack(L,index));
    switch(type(obj)){
    case LUA_TSTRING:
        {
            v.setValue(object_cast<QString>(obj));
            return v;
        }
    case LUA_TNUMBER:
        {
            v.setValue(object_cast<int>(obj));
            return v;
        }
    case LUA_TUSERDATA:
        {
            std::string name = obj_name(obj);
            if(name == "QVariant_wrapper"){
                QVariant_wrapper* wp = object_cast<QVariant_wrapper*>(obj);
                return wp->variant();
            }
            SET_VAL(QSize)
            SET_VAL(QFont)
            SET_VAL(QBrush)
            SET_VAL(QColor)
            SET_VAL(QIcon)
            SET_VAL(QRect)
            SET_VAL(QPoint)
        }
    }
    v.setValue(obj);
    return v;
}

template<class T>
void make_return(lua_State* L,const T& t)
{
    object o = luabind::newtable(L);
    o["holder"] = t;
    object w = o["holder"];
    //o["holder"] = luabind::nil;
    w.push(L);
}

#define TO_VAL(T)\
else if(v.canConvert<T>()){\
    T r = v.value<T>();\
    luabind::detail::make_pointee_instance(L, r, boost::mpl::true_());\
    /*make_return(L,r);*/\
    return;\
}

#define TO_OBJ(T)\
else if(v.canConvert<T>()){\
    T r = v.value<T>();\
          object o = luabind::newtable(L);\
          o[1] = r;\
    return o[1];\
}
extern lua_State* __pL;
object lqvariant_to_object(QVariant* var)
{
    QVariant& v = *var;
    lua_State* L = __pL;
        if(v.canConvert<QString>()){
            QString s = v.value<QString>();
            object o = luabind::newtable(L);
            o[1] = s;
            return o[1];
        }else if(v.canConvert<int>()){
            int i = v.value<int>();
            object o = luabind::newtable(L);
            o[1] = i;
            return o[1];
        }else if(v.canConvert<double>()){
            double i = v.value<double>();
            object o = luabind::newtable(L);
            o[1] = i;
            return o[1];
        }
        TO_OBJ(QSize)
        TO_OBJ(QFont)
        TO_OBJ(QBrush)
        TO_OBJ(QColor)
        TO_OBJ(QIcon)
        TO_OBJ(QRect)
        TO_OBJ(QPoint)
        else if(v.canConvert<object>()){
            return v.value<object>();
        }
        return object();
}

void var_to(lua_State* L, QVariant const& v)
{
    if(v.canConvert<QString>()){
        QString s = v.value<QString>();
        lua_pushstring(L,s.toStdString().c_str());
        return;
    }else if(v.canConvert<int>()){
        int i = v.value<int>();
        lua_pushnumber(L,i);
        return;
    }else if(v.canConvert<double>()){
        double i = v.value<double>();
        lua_pushnumber(L,i);
        return;
    }
    TO_VAL(QSize)
    TO_VAL(QFont)
    TO_VAL(QBrush)
    TO_VAL(QColor)
    TO_VAL(QIcon)
    TO_VAL(QRect)
    TO_VAL(QPoint)
    else
        if(v.canConvert<object>()){
        object o = v.value<object>();
        o.push(L);
        return;
    }else{
        QVariant_wrapper wrapper;
        wrapper.setVariant(v);
        //make_return(L,wrapper);
        luabind::detail::make_pointee_instance(L, wrapper, boost::mpl::true_());
        //object o = luabind::newtable(L);
        //o["varwrapper"] = wrapper;
        //object w = o["varwrapper"];
        //o.push(L);
        return;
    }
    lua_pushnil(L);
}
