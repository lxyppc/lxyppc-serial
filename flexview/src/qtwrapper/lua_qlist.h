#ifndef LUA_QLIST_H
#define LUA_QLIST_H
#include "lua_qt_wrapper.hpp"
#include "lite_ptr.h"

extern lua_State* __pL;
std::string obj_name(const object& o);
struct QListWidgetItem_wrap : public QListWidgetItem, wrap_base
{
    QListWidgetItem_wrap(QListWidget *view = 0, int type = Type):QListWidgetItem(view,type){
        This = object(luabind::from_stack(__pL,1));
        qDebug()<<obj_name(This).c_str();
    }
    QListWidgetItem_wrap(const QString &text, QListWidget *view = 0, int type = Type):QListWidgetItem(text,view,type){
//        qDebug()<< "wrap::("<<text<<")"<<lua_type( detail::wrap_access::ref(*this).state(), -1);
//        qDebug()<<"QListWidgetItem_wrap::(QString)";
//        qDebug()<<text<<"  "<<view<<"  "<<type;
        mt = text;
        This = object(luabind::from_stack(__pL,1));
        qDebug()<<obj_name(This).c_str();
    }
    QListWidgetItem_wrap(const QIcon &icon, const QString &text,
                             QListWidget *view = 0, int type = Type):QListWidgetItem(icon,text,view,type){
        This = object(luabind::from_stack(__pL,1));
        qDebug()<<obj_name(This).c_str();
    }
    QListWidgetItem_wrap(const QListWidgetItem &other):QListWidgetItem(other){
//        qDebug()<< "wrap::(other)"<<lua_type( detail::wrap_access::ref(*this).state(), -1);
        This = object(luabind::from_stack(__pL,1));
        qDebug()<<obj_name(This).c_str();
    }
    //QListWidgetItem_wrap(const QListWidgetItem_wrap &other):QListWidgetItem(other){}


    QVariant data(int role) const
    {
//        qDebug()<< "wrap::data("<<role<<")"<<lua_type( detail::wrap_access::ref(*this).state(), -1)<<mt;
        QVariant v = call_member<QVariant>(this, "data", role);
//        qDebug()<<"QListWidgetItem_wrap::data("<<role<<")"<<(role == 0? v.value<QString>():"");
        return v;
    }

    static QVariant def_data(QListWidgetItem* p, int role){
        //qDebug()<< "wrap::def_data("<<role<<")"<<lua_type( detail::wrap_access::ref(*this).state(), -1);
        QVariant v = p->QListWidgetItem::data(role);
//        qDebug()<<"QListWidgetItem_wrap::def_data("<<role<<")"<<(role == 0? v.value<QString>():"");
        return v;
    }

    void setData(int role, const QVariant& data)
    {
//        qDebug()<< "wrap::setData("<<role<<")"<<lua_type( detail::wrap_access::ref(*this).state(), -1)<<mt;
//        qDebug()<<"QListWidgetItem_wrap::setData("<<role<<")"<<(role == 0? data.value<QString>():"");
        call_member<void>(this, "setData" , role, data);
    }

    static void def_setData(QListWidgetItem*p, int role, const QVariant& data){
        //qDebug()<< "wrap::def_setData("<<role<<")"<<lua_type( detail::wrap_access::ref(*this).state(), -1);
//        qDebug()<<"QListWidgetItem_wrap::def_setData("<<role<<")"<<(role == 0? data.value<QString>():"");
        p->QListWidgetItem::setData(role,data);
    }

    bool operator<(const QListWidgetItem &other) const
    {
//        qDebug()<< "wrap::<(other)"<<lua_type( detail::wrap_access::ref(*this).state(), -1)<<mt;
//        qDebug()<<"QListWidgetItem_wrap::operator<";
        return call_member<bool>(this, "__lt", other);
    }

    static bool def_lt(const QListWidgetItem &This, const QListWidgetItem &other){
//        qDebug()<<"QListWidgetItem_wrap::def_lt";
        return This.QListWidgetItem::operator <(other);
    }

    QString mt;
    object This;
};

struct QListItem : QListWidgetItem
{
    QListItem(QListWidget *view = 0, int type = Type):QListWidgetItem(view,type),This(luabind::from_stack(__pL,1)){
        init();
    }
    QListItem(const QString &text, QListWidget *view = 0, int type = Type):QListWidgetItem(text,view,type),This(luabind::from_stack(__pL,1)){
        init();
    }
    QListItem(const QIcon &icon, const QString &text,
                             QListWidget *view = 0, int type = Type):QListWidgetItem(icon,text,view,type),This(luabind::from_stack(__pL,1)){
        init();
    }
    QListItem(const QListWidgetItem &other):QListWidgetItem(other),This(luabind::from_stack(__pL,1)){
        init();
    }

    void init(){
        //This = object(luabind::from_stack(__pL,1));
        object f = This["data"];
        std::string n = obj_name(This);
        qDebug()<<n.c_str();
        if(strcmp(n.c_str(),"QListItem2") != 0){
            if(f && luabind::type(f) == LUA_TFUNCTION){
                fun = f;
            }
        }
    }

    QVariant _data(int role) const{
        return QListWidgetItem::data(role);
    }
    void _setData(int role, const QVariant& data)
    {
        QListWidgetItem::setData(role,data);
    }
    virtual QVariant data(int role) const
    {
        if(fun && luabind::type(fun) == LUA_TFUNCTION){
            try{
                //return call_function<QVariant>(fun,This,role);
                return call_member<QVariant>(This,"data",role);
            }catch(...){
                qDebug()<<"error";
            }
        }
        return _data(role);
    }
    virtual void setData(int role, const QVariant& data)
    {
        _setData(role,data);
    }
    bool operator<(const QListWidgetItem &other) const
    {
        return QListWidgetItem::operator <(other);
    }
    object fun;
    object This;
};

typedef class_<QComboBox, QWidget> LQComboBox;
typedef class_<QListWidget, QFrame> LQListWidget;
typedef class_<QListWidgetItem> LQListWidgetItem;
typedef class_<QTreeWidget, QFrame> LQTreeWidget;
typedef class_<QTreeWidgetItem> LQTreeWidgetItem;
typedef class_<QTableWidget, QFrame> LQTableWidget;
typedef class_<QTableWidgetItem> LQTableWidgetItem;
typedef class_<QTableWidgetSelectionRange> LQTableWidgetSelectionRange;


LQComboBox lqcombobox();
LQListWidgetItem lqlistwidgetitem();
LQListWidget lqlistwidget();
LQTreeWidget lqtreewidget();
LQTreeWidgetItem lqtreewidgetitem();
LQTableWidget lqtablewidget();
LQTableWidgetItem lqtablewidgetitem();
LQTableWidgetSelectionRange lqtablewidgetselectionrange();

#endif
