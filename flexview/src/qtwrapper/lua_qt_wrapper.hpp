#ifndef LUA_QT_WRAPPER_HPP
#define LUA_QT_WRAPPER_HPP
#include <QtGui>
#include "lua.hpp"
#include <luabind/luabind.hpp>
#include "boost/function.hpp"
#include "converter.hpp"

using namespace luabind;

typedef class_<QObject>                     LQObject;
typedef class_<QWidget, QObject>            LQWidget;
typedef class_<QLayout, QObject>            LQLayout;
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

typedef class_<QMainWindow,QWidget>         LQMainWindow;

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

LQMainWindow lqmainwindow();

LQIcon  lqicon();

class QTestType;
typedef class_<QTestType>         LQTestType;
LQTestType lqtesttype();

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

template<class T, class X1 = detail::unspecified, class X2 = detail::unspecified, class X3 = detail::unspecified>
struct myclass_ : public class_<T,X1,X2,X3>
{
    typedef std::map<QString, ValueSetter<T>, my_les >  map_t;
    myclass_(const char* name, setter_map<T>& mp):class_<T,X1,X2,X3>(name),set_map(&mp){}
    myclass_(const char* name):class_<T,X1,X2,X3>(name),set_map(0){}
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
