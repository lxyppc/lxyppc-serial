#ifndef LUA_QT_WRAPPER_HPP
#define LUA_QT_WRAPPER_HPP
#include <QtGui>
#include "lua.hpp"
#include <luabind/luabind.hpp>
#include "boost/function.hpp"
#include "luabind/detail/constructor.hpp"
#include "converter.hpp"

using namespace luabind;
struct QLayoutWarp : public QLayout, public luabind::wrap_base
{
    QLayoutWarp(QWidget* w):QLayout(w){}
    QLayoutWarp(){}
    virtual void addItem ( QLayoutItem * item ) {
            call_member<void>(this, "addItem", item);
    }
    virtual int	count () const {return call_member<int>(this, "count");}
    virtual int	indexOf ( QWidget * widget ) const{return call_member<int>(this, "indexOf", widget);}
    virtual QLayoutItem * itemAt ( int index ) const { return call_member<QLayoutItem*>(this, "itemAt", index);}
    virtual QLayoutItem *	takeAt ( int index ) {return call_member<QLayoutItem*>(this, "takeAt", index);}
    virtual QSize sizeHint() const {return call_member<QSize>(this, "sizeHint");}
    virtual QSize minimumSize() const {return call_member<QSize>(this, "minimumSize");}
    virtual QSize maximumSize() const {return call_member<QSize>(this, "maximumSize");}
    virtual Qt::Orientations expandingDirections() {return call_member<Qt::Orientations>(this, "expandingDirections");}
    //virtual void setGeometry(const QRect& rect) { call_member<void>(this, "setGeometry", rect); }
    //virtual QRect geometry() const { return call_member<QRect>(this, "geometry"); }
    virtual bool isEmpty() const {return call_member<bool>(this, "isEmpty");}
    virtual bool hasHeightForWidth() const{ return call_member<bool>(this, "hasHeightForWidth");}
    virtual int heightForWidth(int h) const{ return call_member<int>(this, "heightForWidth", h);}
    virtual int minimumHeightForWidth(int h) const{ return call_member<int>(this, "minimumHeightForWidth", h);}
    virtual void invalidate(){ call_member<void>(this, "invalidate"); }

    virtual QWidget *widget(){ return call_member<QWidget*>(this, "widget"); }
    virtual QLayout *layout(){ return call_member<QLayout*>(this, "layout");}
    virtual QSpacerItem *spacerItem(){ return call_member<QSpacerItem*>(this, "spacerItem");}
};

struct QAbstractButtonWrap : public QAbstractButton, public luabind::wrap_base
{
    QAbstractButtonWrap(QWidget* w):QAbstractButton(w){}
    QAbstractButtonWrap(){}
    virtual void paintEvent(QPaintEvent *e) {  call_member<void>(this, "paintEvent", e); }
};

typedef class_<QObject>                     LQObject;
typedef class_<QWidget, QObject>            LQWidget;
typedef class_<QLayout, QLayoutWarp>        LQLayout;
typedef class_<QStackedLayout, QLayout>     LQStackedLayout;
typedef class_<QGridLayout, QLayout>        LQGridLayout;
typedef class_<QFormLayout, QLayout>        LQFormLayout;
typedef class_<QBoxLayout, QLayout>         LQBoxLayout;
typedef class_<QVBoxLayout, QBoxLayout>     LQVBoxLayout;
typedef class_<QHBoxLayout, QBoxLayout>     LQHBoxLayout;

typedef class_<QIcon>                       LQIcon;
typedef class_<QAction,QObject>             LQAction;
typedef class_<QMenuBar,QWidget>            LQMenuBar;
typedef class_<QMenu,QWidget>               LQMenu;
typedef class_<QToolBar, QWidget>           LQToolBar;

typedef class_<QMainWindow,QWidget>         LQMainWindow;
typedef class_<QDockWidget,QWidget>         LQDockWidget;

typedef class_<QPoint>                      LQPoint;
typedef class_<QRect>                       LQRect;
typedef class_<QSize>                       LQSize;
typedef class_<QMargins>                    LQMargins;

typedef class_<QLabel, QFrame>                      LQLabel;
typedef class_<QTextEdit, QAbstractScrollArea>      LQTextEdit;
typedef class_<QLineEdit, QWidget>                  LQLineEdit;

typedef class_<QAbstractButton, QAbstractButtonWrap, QWidget> LQAbstractButton;
typedef class_<QCheckBox, QAbstractButton>          LQCheckBox;
typedef class_<QPushButton, QAbstractButton>        LQPushButton;
typedef class_<QRadioButton, QAbstractButton>       LQRadioButton;
typedef class_<QToolButton, QAbstractButton>        LQToolButton;
typedef class_<QButtonGroup, QObject>               LQButtonGroup;
typedef class_<QKeySequence>                        LQKeySequence;

LQObject lqobject();
LQWidget lqwidget();

LQLayout lqlayout();
LQStackedLayout lqstatckedlayout();
LQGridLayout lqgridlayout();
LQFormLayout lqformlayout();
LQBoxLayout  lqboxlayout();
LQVBoxLayout lqvboxlayout();
LQHBoxLayout lqhboxlayout();

LQAction lqaction();
LQMenuBar lqmenubar();
LQMenu  lqmenu();
LQToolBar lqtoolbar();

LQMainWindow lqmainwindow();
LQDockWidget lqdockwidget();

LQIcon  lqicon();

LQPoint lqpoint();
LQRect  lqrect();
LQSize  lqsize();
LQMargins lqmargins();

LQLabel lqlabel();
LQTextEdit lqtextedit();
LQLineEdit lqlineedit();

LQAbstractButton lqabstractbutton();
LQCheckBox lqcheckbox();
LQPushButton lqpushbutton();
LQRadioButton lqradionbutton();
LQToolButton lqtoolbutton();
LQButtonGroup lqbuttongroup();
LQKeySequence lqkeysequence();

QWidget* lqwidget_init(QWidget* widget, const object& init_table);

class QTestType;
typedef class_<QTestType>         LQTestType;
LQTestType lqtesttype();


bool obj_name_is(const object& obj, const char* name);
template<typename T>bool is_class(const object& obj);//{ return false;}
/*
   cast a object to the member function param 1 type, if fail, return false
  */
template<class BT, class PFN>
bool q_cast(const object& obj, PFN(BT::* pfn), BT* m){
    try{
        typedef typename boost::function_traits<PFN>::arg1_type T;
        typedef typename boost::remove_reference<T>::type T1;
        typedef typename boost::remove_const<T1>::type T2;
        if(!is_class<T2>(obj)) return false;
        T2 t = object_cast<T2>(obj);
        (m->*pfn)(t);
        return true;
    }catch(...){
    }
    return false;
}

template<class BT, class PFN, int n, class P1>
bool q_cast(const object& obj, PFN(BT::* pfn), BT* m, boost::arg<n>, P1 p1)
{
    try{
        typedef typename boost::function_traits<PFN>::arg1_type T;
        typedef typename boost::remove_reference<T>::type T1;
        typedef typename boost::remove_const<T1>::type T2;
        if(!is_class<T2>(obj)) return false;
        T2 t = object_cast<T2>(obj);
        (m->*pfn)(t,p1);
        return true;
    }catch(...){
    }
    return false;
}

template<class BT, class PFN, int n, class P1>
bool q_cast(const object& obj, PFN(BT::* pfn), BT* m, P1 p1, boost::arg<n>)
{
    try{
        typedef typename boost::function_traits<PFN>::arg2_type T;
        typedef typename boost::remove_reference<T>::type T1;
        typedef typename boost::remove_const<T1>::type T2;
        if(!is_class<T2>(obj)) return false;
        T2 t = object_cast<T2>(obj);
        (m->*pfn)(p1,t);
        return true;
    }catch(...){
    }
    return false;
}

/* constructor of classes
  */
template<typename T>
T* construct(const argument& arg){
    luabind::detail::construct<T, std::auto_ptr<T>, typename constructor<>::signature >()(arg);
    return object_cast<T*>(arg);
}

template<typename T, typename T1>
T* construct(const argument& arg, T1 t1){
    luabind::detail::construct<T, std::auto_ptr<T>, typename constructor<T1>::signature >()(arg,t1);
    return object_cast<T*>(arg);
}

template<typename T, typename T1, typename T2>
T* construct(const argument& arg, T1 t1, T2 t2){
    luabind::detail::construct<T, std::auto_ptr<T>, typename constructor<T1,T2>::signature >()(arg,t1,t2);
    return object_cast<T*>(arg);
}




template<typename Type> struct LuaType{enum{v = 0};};
template<> struct LuaType<int>{enum{v = LUA_TNUMBER};};
template<> struct LuaType<const QString&>{enum{v = LUA_TSTRING};};
template<> struct LuaType<bool>{enum{v = LUA_TBOOLEAN};};

template<typename T>
struct ValueSetter
{
    /*
    template<typename Tfn>
    ValueSetter(Tfn* pfn):arg_n(boost::function_traits<Tfn>::arity){
        memset(param,0,sizeof(param));
        my_test< boost::is_same<T*, typename boost::function_traits<Tfn>::arg1_type>::value >();
        my_test<boost::function_traits<Tfn>::arity==2>();
        boost::function<Tfn> p = pfn;
        param[0] = LuaType<typename boost::function_traits<Tfn>::arg2_type>::v;
        assign_pfn(p);
    }

    template<typename Tfn>
    ValueSetter(Tfn (T::*pfn) ):arg_n(boost::function_traits<Tfn>::arity+1){
        memset(param,0,sizeof(param));
        my_test<boost::function_traits<Tfn>::arity==1>();
        typedef typename boost::function_traits<Tfn>::result_type newTfn(T*,typename boost::function_traits<Tfn>::arg1_type);
        boost::function<newTfn> p = pfn;
        param[0] = LuaType<typename boost::function_traits<newTfn>::arg2_type>::v;
        assign_pfn(p);
    }
    */

    ValueSetter():arg_n(0){}

    template<typename R, typename T1>
    ValueSetter(R (T::*pfn)(T1) ):arg_n(2){
        memset(param,0,sizeof(param));
        boost::function<R(T*,T1)> p = pfn;
        param[0] = LuaType<T1>::v;
        assign_pfn(p);
    }

    template<typename R, typename T1>
    ValueSetter(R pfn(T*,T1) ):arg_n(2){
        memset(param,0,sizeof(param));
        boost::function<R(T*,T1)> p = pfn;
        param[0] = LuaType<T1>::v;
        assign_pfn(p);
    }

    void assign_pfn(boost::function<void(T*,int)> pfn){
        fn_int = pfn;
    }
    void assign_pfn(boost::function<void(T*,const QString&)> pfn){
        fn_string = pfn;
    }
    void assign_pfn(boost::function<void(T*,bool)> pfn){
        fn_bool = pfn;
    }
    void assign_pfn(boost::function<void(T*,const QPoint&)> pfn){
        fn_point = pfn;
    }
    void assign_pfn(boost::function<void(T*,const QSize&)> pfn){
        fn_size = pfn;
    }
    void assign_pfn(boost::function<void(T*,const QRect&)> pfn){
        fn_rect = pfn;
    }
    void assign_pfn(boost::function<void(T*,QLayout*)> pfn){
        fn_layout = pfn;
    }
    void assign_pfn(boost::function<void(T*,const QMargins&)> pfn){
        fn_margins = pfn;
    }

    void operator()(T* This, const object& obj){
        switch(arg_n){
        case 2:
            if(type(obj) == param[0]){
                switch(param[0]){
                case LUA_TNUMBER:
                    fn_int(This, object_cast<int>(obj));
                    break;
                case LUA_TSTRING:
                    fn_string(This, object_cast<QString>(obj));
                    break;
                case LUA_TBOOLEAN:
                    fn_bool(This, object_cast<bool>(obj));
                    break;
                default:
                    break;
                }
            }else if(type(obj) == LUA_TUSERDATA){
                if(is_class<QPoint>(obj)){
                    fn_point(This, object_cast<QPoint>(obj));
                }else if(is_class<QSize>(obj)){
                    fn_size(This, object_cast<QSize>(obj));
                }else if(is_class<QRect>(obj)){
                    fn_rect(This, object_cast<QRect>(obj));
                }else if(is_class<QMargins>(obj)){
                    fn_margins(This, object_cast<QMargins>(obj));
                }else if(is_class<QLayout*>(obj)){
                    fn_layout(This, object_cast<QLayout*>(obj));
                }
            }
            break;
        case 3:
            break;
        }
    }
    unsigned int arg_n;
    int param[4];
    boost::function<void(T*, int)>  fn_int;
    boost::function<void(T*, const QString&)>  fn_string;
    boost::function<void(T*, bool)>  fn_bool;
    boost::function<void(T*, const QPoint&)>  fn_point;
    boost::function<void(T*, const QSize&)>  fn_size;
    boost::function<void(T*, const QRect&)>   fn_rect;
    boost::function<void(T*, QLayout*)>  fn_layout;
    boost::function<void(T*, const QMargins&)>  fn_margins;
};

struct my_les{
bool operator()(const QString& l, const QString& r){
    return l.compare(r, Qt::CaseInsensitive) < 0;
}
};

template<class T>
struct setter_map : public std::map<QString, ValueSetter<T>, my_les>
{
};

template<typename T>
T* lq_general_init(T* widget, const object& obj, setter_map<T>& set_map)
{
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj), e; i != e; ++i){
            if(type(i.key()) == LUA_TSTRING){
                QString key = object_cast<QString>(i.key());
                if(set_map.find(key) != set_map.end()){
                    set_map[key](widget,*i);
                }
            }
        }
    }
    return widget;
}

template<typename T>
void table_init_general(const luabind::argument & arg, const object& obj);

template<class T, class X1 = detail::unspecified, class X2 = detail::unspecified, class X3 = detail::unspecified>
struct myclass_ : public class_<T,X1,X2,X3>
{
    typedef std::map<QString, ValueSetter<T>, my_les >  map_t;
    myclass_(const char* name, setter_map<T>& mp):class_<T,X1,X2,X3>(name){set_map = &mp;}
    myclass_(const char* name):class_<T,X1,X2,X3>(name){ set_map = 0; }
    template<class T1>
    myclass_& def(T1 t1){
        class_<T,X1,X2,X3>::def(t1);
        return *this;
    }
    template<class T1, class T2>
    myclass_& def(T1 t1, T2 t2){
        class_<T,X1,X2,X3>::def(t1,t2);
        return *this;
    }
    template<class T1, class T2, class T3>
    myclass_& def(T1 t1, T2 t2, T3 t3){
        class_<T,X1,X2,X3>::def(t1,t2,t3);
        return *this;
    }
    template<class T1, class T2, class T3, class T4>
    myclass_& def(T1 t1, T2 t2, T3 t3, T4 t4){
        class_<T,X1,X2,X3>::def(t1,t2,t3,t4);
        return *this;
    }

    template<class Getter>
    myclass_& property(const char* prop, Getter g){
        class_<T,X1,X2,X3>::property(prop,g);
        return *this;
    }

    template<class Getter, class Setter>
    myclass_& property(const char* prop, Getter g, Setter s){
        if(set_map)(*set_map)[QString::fromLocal8Bit(prop)] = s;
        class_<T,X1,X2,X3>::property(prop,g,s);
        return *this;
    }
    template<class Getter, class Setter, class P1>
    myclass_& property(const char* prop, Getter g, Setter s, const P1& p1){
        if(set_map)(*set_map)[QString::fromLocal8Bit(prop)] = s;
        class_<T,X1,X2,X3>::property(prop,g,s,p1);
        return *this;
    }
    template<class Getter, class Setter, class P1, class P2>
    myclass_& property(const char* prop, Getter g, Setter s, const P1& p1, const P2& p2){
        if(set_map)(*set_map)[QString::fromLocal8Bit(prop)] = s;
        class_<T,X1,X2,X3>::property(prop,g,s,p1,p2);
        return *this;
    }
    setter_map<T>* set_map;
};

#endif
