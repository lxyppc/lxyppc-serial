#ifndef LUA_QLIST_H
#define LUA_QLIST_H
#include "lua_qt_wrapper.hpp"
#include "lite_ptr.h"

extern lua_State* __pL;
std::string obj_name(const object& o);
struct QListWidgetItem_wrap : public QListWidgetItem, wrap_base
{
    QListWidgetItem_wrap(QListWidget *view = 0, int type = Type):QListWidgetItem(view,type){
    }
    QListWidgetItem_wrap(const QString &text, QListWidget *view = 0, int type = Type):QListWidgetItem(text,view,type){
    }
    QListWidgetItem_wrap(const QIcon &icon, const QString &text,
                             QListWidget *view = 0, int type = Type):QListWidgetItem(icon,text,view,type){
    }
    QListWidgetItem_wrap(const QListWidgetItem &other):QListWidgetItem(other){
    }
    QVariant data(int role) const{
        return call_member<QVariant>(this, "data", role);
    }
    static QVariant def_data(QListWidgetItem* p, int role){
        return p->QListWidgetItem::data(role);
    }
    void setData(int role, const QVariant& data){
        call_member<void>(this, "setData" , role, data);
    }
    static void def_setData(QListWidgetItem*p, int role, const QVariant& data){
        p->QListWidgetItem::setData(role,data);
    }
    bool operator<(const QListWidgetItem &other) const {
        return call_member<bool>(this, "__lt", other);
    }
    static bool def_lt(const QListWidgetItem &This, const QListWidgetItem &other){
        return This.QListWidgetItem::operator <(other);
    }
};

struct QTreeWidgetItem_wrap : public QTreeWidgetItem, wrap_base
{
    QTreeWidgetItem_wrap(int type = Type):QTreeWidgetItem(type){}
    QTreeWidgetItem_wrap(const QStringList &text,int type = Type):QTreeWidgetItem(text,type){}
    QTreeWidgetItem_wrap(QTreeWidget *view, int type = Type):QTreeWidgetItem(view,type){}
    QTreeWidgetItem_wrap(QTreeWidget *view, const QStringList &text, int type = Type):QTreeWidgetItem(view,text,type){}
    QTreeWidgetItem_wrap(QTreeWidget *view, QTreeWidgetItem *after, int type = Type):QTreeWidgetItem(view,after,type){}
    QTreeWidgetItem_wrap(QTreeWidgetItem *parent, int type = Type):QTreeWidgetItem(parent,type){}
    QTreeWidgetItem_wrap(QTreeWidgetItem *parent, const QStringList &text, int type = Type):QTreeWidgetItem(parent,text,type){}
    QTreeWidgetItem_wrap(QTreeWidgetItem *parent, QTreeWidgetItem *after, int type = Type):QTreeWidgetItem(parent,after,type){}
    QTreeWidgetItem_wrap(const QTreeWidgetItem& other):QTreeWidgetItem(other){}

    QVariant data(int column,int role) const{
        return call_member<QVariant>(this, "data", column,role);
    }
    static QVariant def_data(QTreeWidgetItem* p, int column, int role){
        return p->QTreeWidgetItem::data(column,role);
    }
    void setData(int column, int role, const QVariant& data){
        call_member<void>(this, "setData" , column,role, data);
    }
    static void def_setData(QTreeWidgetItem*p, int column, int role, const QVariant& data){
        p->QTreeWidgetItem::setData(column,role,data);
    }
    bool operator<(const QTreeWidgetItem &other) const {
        return call_member<bool>(this, "__lt", other);
    }
    static bool def_lt(const QTreeWidgetItem &This, const QTreeWidgetItem &other){
        return This.QTreeWidgetItem::operator <(other);
    }
};

struct QTableWidgetItem_wrap : public QTableWidgetItem, wrap_base
{
    QTableWidgetItem_wrap(int type = Type):QTableWidgetItem(type){}
    QTableWidgetItem_wrap(const QString &text, int type = Type):QTableWidgetItem(text,type){}
    QTableWidgetItem_wrap(const QIcon &icon, const QString &text,int type = Type):QTableWidgetItem(icon,text,type){}
    QTableWidgetItem_wrap(const QTableWidgetItem& other):QTableWidgetItem(other){}
    QVariant data(int role) const{
        return call_member<QVariant>(this, "data", role);
    }
    static QVariant def_data(QTableWidgetItem* p, int role){
        return p->QTableWidgetItem::data(role);
    }
    void setData(int role, const QVariant& data){
        call_member<void>(this, "setData" , role, data);
    }
    static void def_setData(QTableWidgetItem*p, int role, const QVariant& data){
        p->QTableWidgetItem::setData(role,data);
    }
    bool operator<(const QTableWidgetItem &other) const {
        return call_member<bool>(this, "__lt", other);
    }
    static bool def_lt(const QTableWidgetItem &This, const QTableWidgetItem &other){
        return This.QTableWidgetItem::operator <(other);
    }
};

struct QAbstractItemView_wrap : public QAbstractItemView, wrap_base
{
    QAbstractItemView_wrap(QWidget* w = 0):QAbstractItemView(w) {}
    QRect visualRect(const QModelIndex &index) const { return QRect(); }
    void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible){}
    QModelIndex indexAt(const QPoint &point) const { return QModelIndex(); }

protected:
    QModelIndex moveCursor(CursorAction cursorAction,
                                   Qt::KeyboardModifiers modifiers) { return QModelIndex(); }

    int horizontalOffset() const {  return call_member<int>(this, "horizontalOffset"); }
    int verticalOffset() const {  return call_member<int>(this, "verticalOffset"); }

    bool isIndexHidden(const QModelIndex &index) const  { return call_member<bool>(this, "isIndexHidden", index); }

    void setSelection(const QRect &rect, QItemSelectionModel::SelectionFlags command) { call_member<void>(this, "setSelection", rect, command); }
    QRegion visualRegionForSelection(const QItemSelection &selection) const { return QRegion(); }
};

typedef class_<QModelIndex> LQModelIndex;
typedef class_<QAbstractItemView,QAbstractItemView_wrap,QAbstractScrollArea> LQAbstractItemView;

typedef class_<QColumnView, QAbstractItemView> LQColumnView;
typedef class_<QHeaderView, QAbstractItemView> LQHeaderView;

typedef class_<QListView, QAbstractItemView> LQListView;
typedef class_<QTableView, QAbstractItemView> LQTableView;
typedef class_<QTreeView, QAbstractItemView> LQTreeView;

typedef class_<QComboBox, QWidget> LQComboBox;
typedef class_<QListWidget, QListView> LQListWidget;
typedef class_<QListWidgetItem,QListWidgetItem_wrap> LQListWidgetItem;
typedef class_<QTreeWidget, QTreeView> LQTreeWidget;
typedef class_<QTreeWidgetItem,QTreeWidgetItem_wrap> LQTreeWidgetItem;
typedef class_<QTableWidget, QTableView> LQTableWidget;
typedef class_<QTableWidgetItem,QTableWidgetItem_wrap> LQTableWidgetItem;
typedef class_<QTableWidgetSelectionRange> LQTableWidgetSelectionRange;

LQModelIndex    lqmodelindex();
LQAbstractItemView  lqabstractitemview();

LQColumnView  lqcolumnview();
LQHeaderView lqheaderview();

LQListView lqlistview();
LQTableView lqtableview();
LQTreeView lqtreeview();

LQComboBox lqcombobox();
LQListWidgetItem lqlistwidgetitem();
LQListWidget lqlistwidget();
LQTreeWidget lqtreewidget();
LQTreeWidgetItem lqtreewidgetitem();
LQTableWidget lqtablewidget();
LQTableWidgetItem lqtablewidgetitem();
LQTableWidgetSelectionRange lqtablewidgetselectionrange();

#endif
