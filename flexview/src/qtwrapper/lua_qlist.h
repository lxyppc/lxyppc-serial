#ifndef LUA_QLIST_H
#define LUA_QLIST_H
#include "lua_qt_wrapper.hpp"

struct QListWidgetItem_wrap : QListWidgetItem, wrap_base
{
    QListWidgetItem_wrap(QListWidget *view = 0, int type = Type):QListWidgetItem(view,type){}
    QListWidgetItem_wrap(const QString &text, QListWidget *view = 0, int type = Type):QListWidgetItem(text,view,type){}
    QListWidgetItem_wrap(const QIcon &icon, const QString &text,
                             QListWidget *view = 0, int type = Type):QListWidgetItem(icon,text,view,type){}
    QListWidgetItem_wrap(const QListWidgetItem &other):QListWidgetItem(other){}


    virtual QVariant data(int role) const
    {
        return call_member<QVariant>(this, "data", role);
    }

    static QVariant def_data(QListWidgetItem* p, int role){
        return p->QListWidgetItem::data(role);
    }

    virtual void setData(int role, const QVariant& data)
    {
        call_member<void>(this, "setData" , role, data);
    }

    static void def_setData(QListWidgetItem*p, int role, const QVariant& data){
        p->QListWidgetItem::setData(role,data);
    }

    bool operator<(const QListWidgetItem &other) const
    {
        return call_member<bool>(this, "__lt", other);
    }

    static bool def_lt(const QListWidgetItem &This, const QListWidgetItem &other){
        return This.QListWidgetItem::operator <(other);
    }

};
typedef class_<QComboBox, QWidget> LQComboBox;
typedef class_<QListWidget, QFrame> LQListWidget;
typedef class_<QListWidgetItem,QListWidgetItem_wrap> LQListWidgetItem;
typedef class_<QTreeWidget, QFrame> LQTreeWidget;

LQComboBox lqcombobox();
LQListWidgetItem lqlistwidgetitem();
LQListWidget lqlistwidget();
LQTreeWidget lqtreewidget();

#endif
