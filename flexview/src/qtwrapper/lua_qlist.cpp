#include "lua_qlist.h"

#include <luabind/luabind.hpp>
#include <luabind/tag_function.hpp>
#include <luabind/operator.hpp>
#include <boost/bind.hpp>
#include "qluaslot.h"
#include <luabind/adopt_policy.hpp>

template<class T, class pfnT>
void addItems(T* base, pfnT(T::* addItem), const object& obj)
{
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj),e; i!=e; ++i){
            QVariant v;
            QString key;
            if(type(i.key()) == LUA_TSTRING){
                key = object_cast<QString>(i.key());
                v.setValue(object(*i));
            }else if(type(*i) == LUA_TSTRING){
                key = object_cast<QString>(*i);
            }else{
                continue;
            }
            (base->*addItem)(key, v);
        }
    }
}


void lqcombobox_addItem1(QComboBox* combo, const QString& text, const QVariant& userData)
{
    combo->addItem(text,userData);
}

void lqcombobox_addItem2(QComboBox* combo, const QIcon& icon, const QString& text, const QVariant& userData)
{
    combo->addItem(icon,text,userData);
}

void lqcombobox_addItems(QComboBox* combo, const object& obj)
{
    addItems(combo, (void(QComboBox::*)(const QString&, const QVariant&))&QComboBox::addItem,obj);
    combo->addItems(list_cast<QString>(obj));
}


void lqcombobox_insertItem1(QComboBox* combo, int index, const QString& text, const QVariant& userData)
{
    combo->insertItem(index,text,userData);
}

void lqcombobox_insertItem2(QComboBox* combo, int index, const QIcon& icon, const QString& text, const QVariant& userData)
{
    combo->insertItem(index,icon,text,userData);
}

void lqcombobox_insertItems(QComboBox* combo, int index, const object& obj)
{
    combo->insertItems(index, list_cast<QString>(obj));
}

SIGNAL_PROPERYT(lqcombox, activated, QComboBox, "(int)")
SIGNAL_PROPERYT(lqcombox_str, activated, QComboBox, "(const QString&)")
SIGNAL_PROPERYT(lqcombox, currentIndexChanged, QComboBox, "(int)")
SIGNAL_PROPERYT(lqcombox_str, currentIndexChanged, QComboBox, "(const QString&)")
SIGNAL_PROPERYT(lqcombox, highlighted, QComboBox, "(int)")
SIGNAL_PROPERYT(lqcombox_str, highlighted, QComboBox, "(const QString&)")
SIGNAL_PROPERYT(lqcombox, editTextChanged, QComboBox, "(const QString&)")

SIGNAL_PROPERYT(lqlistwidget, currentItemChanged, QListWidget,  "( QListWidgetItem*,QListWidgetItem*)")
SIGNAL_PROPERYT(lqlistwidget, currentRowChanged, QListWidget,  "(int)")
SIGNAL_PROPERYT(lqlistwidget, currentTextChanged, QListWidget,  "(const QString &)")
SIGNAL_PROPERYT(lqlistwidget, itemActivated, QListWidget,  "(QListWidgetItem*)")
SIGNAL_PROPERYT(lqlistwidget, itemChanged, QListWidget,  "(QListWidgetItem*)")
SIGNAL_PROPERYT(lqlistwidget, itemClicked, QListWidget,  "(QListWidgetItem*)")
SIGNAL_PROPERYT(lqlistwidget, itemDoubleClicked, QListWidget,  "(QListWidgetItem*)")
SIGNAL_PROPERYT(lqlistwidget, itemEntered, QListWidget,  "(QListWidgetItem*)")
SIGNAL_PROPERYT(lqlistwidget, itemPressed, QListWidget,  "(QListWidgetItem*)")
SIGNAL_PROPERYT(lqlistwidget, itemSelectionChanged, QListWidget,  "()")

SIGNAL_PROPERYT(lqtreewidget, currentItemChanged, QTreeWidget, "(QTreeWidgetItem*,QTreeWidgetItem*)")
SIGNAL_PROPERYT(lqtreewidget, itemActivated, QTreeWidget,"(QTreeWidgetItem*,int)")
SIGNAL_PROPERYT(lqtreewidget, itemChanged, QTreeWidget,"(QTreeWidgetItem*,int)")
SIGNAL_PROPERYT(lqtreewidget, itemClicked, QTreeWidget,"(QTreeWidgetItem*,int)")
SIGNAL_PROPERYT(lqtreewidget, itemCollapsed, QTreeWidget,"(QTreeWidgetItem*)")
SIGNAL_PROPERYT(lqtreewidget, itemDoubleClicked, QTreeWidget,"(QTreeWidgetItem*,int)")
SIGNAL_PROPERYT(lqtreewidget, itemEntered, QTreeWidget,"(QTreeWidgetItem*,int)")
SIGNAL_PROPERYT(lqtreewidget, itemExpanded, QTreeWidget,"(QTreeWidgetItem*)")
SIGNAL_PROPERYT(lqtreewidget, itemPressed, QTreeWidget,"(QTreeWidgetItem*,int)")
SIGNAL_PROPERYT(lqtreewidget, itemSelectionChanged, QTreeWidget,"()")


SIGNAL_PROPERYT(lqtablewidget, cellActivated, QTableWidget, "(int,int)" )
SIGNAL_PROPERYT(lqtablewidget, cellChanged, QTableWidget, "(int,int)" )
SIGNAL_PROPERYT(lqtablewidget, cellClicked, QTableWidget, "(int,int)" )
SIGNAL_PROPERYT(lqtablewidget, cellDoubleClicked, QTableWidget, "(int,int)" )
SIGNAL_PROPERYT(lqtablewidget, cellEntered, QTableWidget, "(int,int)" )
SIGNAL_PROPERYT(lqtablewidget, cellPressed, QTableWidget, "(int,int)" )
SIGNAL_PROPERYT(lqtablewidget, currentCellChanged, QTableWidget, "(int,int,int,int)" )
SIGNAL_PROPERYT(lqtablewidget, currentItemChanged, QTableWidget, "(QTableWidgetItem*,QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, currentRowChanged, QTableWidget, "(QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, currentTextChanged, QTableWidget, "(QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, itemActivated, QTableWidget, "(QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, itemChanged, QTableWidget, "(QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, itemClicked, QTableWidget, "(QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, itemDoubleClicked, QTableWidget, "(QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, itemEntered, QTableWidget, "(QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, itemPressed, QTableWidget, "(QTableWidgetItem*)" )
SIGNAL_PROPERYT(lqtablewidget, itemSelectionChanged, QTableWidget, "()" )

static setter_map<QComboBox> lqcombobox_set_map;
static setter_map<QListWidgetItem> lqlistwidgetitem_set_map;
static setter_map<QListWidget> lqlistwidget_set_map;
static setter_map<QTreeWidgetItem> lqtreewidgetitem_set_map;
static setter_map<QTreeWidget> lqtreewidget_set_map;
static setter_map<QTableWidgetItem> lqtablewidgetitem_set_map;
static setter_map<QTableWidget> lqtablewidget_set_map;

QComboBox* lqcombobox_init(QComboBox* widget, const object& obj)
{
    lqwidget_init(widget, obj);
    for(iterator i(obj),e; i!=e; ++i){
        if(type(*i) == LUA_TTABLE){
            addItems(widget, (void(QComboBox::*)(const QString&,const QVariant&))&QComboBox::addItem, *i);
            //widget->addItems(list_cast<QString>(*i));
        }
    }
    return lq_general_init(widget, obj, lqcombobox_set_map);
}

template<>
void table_init_general<QComboBox>(const luabind::argument & arg, const object& obj)
{
    lqcombobox_init(construct<QComboBox>(arg), obj);
}

LQComboBox lqcombobox()
{
    return
    myclass_<QComboBox, QWidget>("QComboBox",lqcombobox_set_map)
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("__call", lqcombobox_init)
    .def("__init", table_init_general<QComboBox>)
    .def("addItem", tag_function<void(QComboBox*, const QString&)>(boost::bind(lqcombobox_addItem1, _1, _2,QVariant())))
    .def("addItem", lqcombobox_addItem1)
    .def("addItem", tag_function<void(QComboBox*, const QIcon&,const QString&)>(boost::bind(lqcombobox_addItem2, _1, _2, _3,QVariant())))
    .def("addItem", lqcombobox_addItem2)
    .def("addItems", lqcombobox_addItems)

    .def("insertItem", tag_function<void(QComboBox*,int,const QString&)>(boost::bind(lqcombobox_insertItem1, _1, _2, _3,QVariant())))
    .def("insertItem", lqcombobox_insertItem1)
    .def("insertItem", tag_function<void(QComboBox*,int,const QIcon&,const QString&)>(boost::bind(lqcombobox_insertItem2, _1,_2,_3,_4,QVariant())))
    .def("insertItem", lqcombobox_insertItem2)
    .def("insertItems", lqcombobox_insertItems)

    .def("itemText", &QComboBox::itemText)
    .def("itemIcon", &QComboBox::itemIcon)
    .def("itemData", tag_function<QVariant(QComboBox*,int)>(boost::bind(&QComboBox::itemData, _1, _2, Qt::UserRole)))
    .def("itemData", &QComboBox::itemData)
    .def("setItemData", tag_function<void(QComboBox*,int, const QVariant&)>(boost::bind(&QComboBox::setItemData, _1, _2, _3, Qt::UserRole)))
    .def("setItemData", &QComboBox::setItemData)

    .def("clear", &QComboBox::clear )
    .def("clearEditText", &QComboBox::clearEditText )
    .def("setCurrentIndex", &QComboBox::setCurrentIndex )
    .def("setEditText", &QComboBox::setEditText )

    .def("findText", &QComboBox::findText)
    .def("findText", tag_function<int(QComboBox*,const QString&)>(boost::bind( &QComboBox::findText,_1,_2, Qt::MatchExactly | Qt::MatchCaseSensitive )))

    .def("findData", &QComboBox::findData)
    .def("findData", tag_function<int(QComboBox*,const QVariant&, int)>(boost::bind( &QComboBox::findData,_1,_2, _3, Qt::MatchExactly | Qt::MatchCaseSensitive )))
    .def("findData", tag_function<int(QComboBox*,const QVariant&)>(boost::bind( &QComboBox::findData,_1,_2, Qt::UserRole,Qt::MatchExactly | Qt::MatchCaseSensitive )))

    .property("count", &QComboBox::count)
    .property("editable", &QComboBox::isEditable, &QComboBox::setEditable)
    .property("currentIndex", &QComboBox::currentIndex, &QComboBox::setCurrentIndex)
    .property("currentText", &QComboBox::currentText, &QComboBox::setEditText)
    .property("activated", lqcombox_get_activated, lqcombox_set_activated)
    .property("activatedString", lqcombox_str_get_activated, lqcombox_str_set_activated)
    .property("currentIndexChanged", lqcombox_get_currentIndexChanged, lqcombox_set_currentIndexChanged)
    .property("currentIndexChangedString", lqcombox_str_get_activated, lqcombox_str_set_activated)
    .property("highlighted", lqcombox_get_highlighted, lqcombox_set_highlighted)
    .property("highlightedString", lqcombox_str_get_highlighted, lqcombox_str_set_highlighted)
    .property("editTextChanged", lqcombox_get_editTextChanged, lqcombox_set_editTextChanged)

    .class_<QComboBox, QWidget>::property("lineEdit", &QComboBox::lineEdit, &QComboBox::setLineEdit)

    ;
}

QListWidgetItem* lqlistwidgetitem_init(QListWidgetItem* widget, const object& obj)
{
//    for(iterator i(obj),e; i!=e; ++i){
//        if(type(*i) == LUA_TTABLE){
//            addItems(widget, (void(QComboBox::*)(const QString&,const QVariant&))&QComboBox::addItem, *i);
//            //widget->addItems(list_cast<QString>(*i));
//        }
//    }
    return lq_general_init(widget, obj, lqlistwidgetitem_set_map);
}

template<>
void table_init_general<QListWidgetItem>(const luabind::argument & arg, const object& obj)
{
    lqlistwidgetitem_init(construct<QListWidgetItem>(arg), obj);
}

QListWidget* lqlistwidget_init(QListWidget* widget, const object& obj)
{
    lqwidget_init(widget, obj);
    for(iterator i(obj),e; i!=e; ++i){
        if(type(*i) == LUA_TTABLE){
            //addItems(widget, (void(QComboBox::*)(const QString&,const QVariant&))&QComboBox::addItem, *i);
            widget->addItems(list_cast<QString>(*i));
        }
    }
    return lq_general_init(widget, obj, lqlistwidget_set_map);
}

template<>
void table_init_general<QListWidget>(const luabind::argument & arg, const object& obj)
{
    lqlistwidget_init(construct<QListWidget>(arg), obj);
}

void lqlistwidgetitem_set_check_state(QListWidgetItem* w, int state)
{
    w->setCheckState(Qt::CheckState(state));
}

void lqlistwidgetitem_set_flags(QListWidgetItem* w, int flag)
{
    w->setFlags(Qt::ItemFlags(flag));
}

int lqlistwidgetitem_row(QListWidgetItem* i)
{
    QListWidget* l = i->listWidget();
    return l ? l->row(i) : -1;
}

LQListWidgetItem lqlistwidgetitem()
{
    (void)self;
    (void)const_self;
    return
     myclass_<QListWidgetItem,QListWidgetItem_wrap>("QListWidgetItem",lqlistwidgetitem_set_map)
    .def(constructor<>())
    .def(constructor<const QListWidgetItem&>())
    .def(constructor<QListWidget*>())
    .def(constructor<QListWidget*, int>())
    .def(constructor<const QString&>())
    .def(constructor<const QString&, QListWidget*>())
    .def(constructor<const QString&, QListWidget*, int>())
    .def(constructor<const QIcon&,const QString&>())
    .def(constructor<const QIcon&,const QString&, QListWidget*>())
    .def(constructor<const QIcon&,const QString&, QListWidget*, int>())

    .def("__call", lqlistwidgetitem_init)
    .def("__init", table_init_general<QListWidgetItem>)
    //.def("data", &QListWidgetItem::data, &QListWidgetItem::data)
    //.def("setData", &QListWidgetItem::setData, &QListWidgetItem::setData)
    //.def("__lt", &QListWidgetItem::operator <)
    .def("data", &QListWidgetItem::data, &QListWidgetItem_wrap::def_data)
    .def("setData", &QListWidgetItem::setData, &QListWidgetItem_wrap::def_setData)
    .def("__lt", &QListWidgetItem::operator <,  &QListWidgetItem_wrap::def_lt)

    .property("listWidget", &QListWidgetItem::listWidget)
    .property("background", &QListWidgetItem::background, &QListWidgetItem::setBackground)
    .property("backgroundColor", &QListWidgetItem::backgroundColor, &QListWidgetItem::setBackgroundColor)
    .property("checkState", &QListWidgetItem::checkState, lqlistwidgetitem_set_check_state)
    .property("flags", &QListWidgetItem::flags, lqlistwidgetitem_set_flags)
    .property("font", &QListWidgetItem::font, &QListWidgetItem::setFont)
    .property("foreground", &QListWidgetItem::foreground, &QListWidgetItem::setForeground)
    .property("hidden", &QListWidgetItem::isHidden, &QListWidgetItem::setHidden)
    .property("icon", &QListWidgetItem::icon, &QListWidgetItem::setIcon)
    .property("selected", &QListWidgetItem::isSelected, &QListWidgetItem::setSelected)
    .property("statusTip", &QListWidgetItem::statusTip, &QListWidgetItem::setStatusTip)
    .property("text", &QListWidgetItem::text, &QListWidgetItem::setText)
    .property("textAlignment", &QListWidgetItem::textAlignment, &QListWidgetItem::setTextAlignment)
    .property("textColor", &QListWidgetItem::textColor, &QListWidgetItem::setTextColor)
    .property("toolTip", &QListWidgetItem::toolTip, &QListWidgetItem::setToolTip)
    .property("whatsThis", &QListWidgetItem::whatsThis, &QListWidgetItem::setWhatsThis)
    .property("type", &QListWidgetItem::type)
    .property("row", lqlistwidgetitem_row)


//    .scope
//    [
//            class_<QListItem>("QListItem2")
//              .def(constructor<>())
//              .def(constructor<const QString&>())
//              .def("data", &QListItem::_data, &QListItem::_data)
//              .def("setData", &QListItem::_setData)
//    ]
    ;
}

void lqlistwidget_sortItems(QListWidget* w)
{
    w->sortItems();
}

void lqlistwidget_sortItems2(QListWidget* w, int order)
{
    w->sortItems(Qt::SortOrder(order));
}

void lqlistwidget_addItems(QListWidget* w, const object& obj)
{
    w->addItems(list_cast<QString>(obj));
}

void lqlistwidget_addItemsx(QListWidget* w, const QList<QListWidgetItem*>& obj)
{
    foreach(QListWidgetItem*i, obj){
        w->addItem(i);
    }
}

void lqlistwidget_insertItems(QListWidget* w, int row, const object& obj)
{
    w->insertItems(row,list_cast<QString>(obj));
}

void lqlistwidget_set_cur_row(QListWidget* w, int row)
{
    w->setCurrentRow(row);
}

void lqlistwidget_scrollToItem(QListWidget* w, QListWidgetItem* i, int hint)
{
    w->scrollToItem(i,QAbstractItemView::ScrollHint(hint));
}

void lqlistwidget_scrollToItem2(QListWidget* w, QListWidgetItem* i)
{
    w->scrollToItem(i);
}

object lqlistwidget_finditems(QListWidget* w, const QString& text, int f)
{
    object obj(luabind::newtable(__pL));
    QList<QListWidgetItem*> r = w->findItems(text, Qt::MatchFlags(f));
    for(int i=0;i<r.count(); i++){
        obj[i+1] = r.at(i);
    }
    return obj;
}

object lqlistwidget_selecteditems(QListWidget* w)
{
    object obj(luabind::newtable(__pL));
    QList<QListWidgetItem*> list = w->selectedItems();
    for(int i=0;i<list.count();i++){
        obj[i+1] = list.at(i);
    }
    return obj;
}

LQListWidget lqlistwidget()
{
    return
    myclass_<QListWidget, QListView>("QListWidget",lqlistwidget_set_map)
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("__call", lqlistwidget_init)
    .def("__init", table_init_general<QListWidget>)
    .def("addItem", (void(QListWidget::*)(const QString&))&QListWidget::addItem)
    .def("addItem", (void(QListWidget::*)(QListWidgetItem*))&QListWidget::addItem ,adopt(_2))
    .def("addItems", &QListWidget::addItems)
    //.def("addItems", lqlistwidget_addItemsx)
    .def("insertItem", (void(QListWidget::*)(int,const QString&))&QListWidget::insertItem)
    .def("insertItem", (void(QListWidget::*)(int,QListWidgetItem*))&QListWidget::insertItem, adopt(_3))
    .def("insertItems", &QListWidget::insertItems)

    .def("sortItems", lqlistwidget_sortItems)
    .def("sortItems", lqlistwidget_sortItems2)
    .def("row", &QListWidget::row)
    .def("item", &QListWidget::item)
    .def("itemAt", (QListWidgetItem*(QListWidget::*)(int,int)const)&QListWidget::itemAt)
    .def("itemAt", (QListWidgetItem*(QListWidget::*)(const QPoint&)const)&QListWidget::itemAt)
    .def("itemWidget", &QListWidget::itemWidget)
    .def("setItemWidget", &QListWidget::setItemWidget)
    .def("takeItem", &QListWidget::takeItem)
    .def("findItems", &QListWidget::findItems)
    .def("selectedItems", &QListWidget::selectedItems)
    .def("clear", &QListWidget::clear)
    .def("scrollToItem", lqlistwidget_scrollToItem)
    .def("scrollToItem", lqlistwidget_scrollToItem2)

    .property("count", &QListWidget::count)
    .property("sortingEnabled", &QListWidget::isSortingEnabled, &QListWidget::setSortingEnabled)
    .property("currentRow", &QListWidget::currentRow, lqlistwidget_set_cur_row)

    .sig_prop(lqlistwidget, currentItemChanged)
    .sig_prop(lqlistwidget, currentRowChanged)
    .sig_prop(lqlistwidget, currentTextChanged)
    .sig_prop(lqlistwidget, itemActivated)
    .sig_prop(lqlistwidget, itemChanged)
    .sig_prop(lqlistwidget, itemClicked)
    .sig_prop(lqlistwidget, itemDoubleClicked)
    .sig_prop(lqlistwidget, itemEntered)
    .sig_prop(lqlistwidget, itemPressed)
    .sig_prop(lqlistwidget, itemSelectionChanged)
    ;
}







QTreeWidgetItem* lqtreewidgetitem_init(QTreeWidgetItem* widget, const object& obj)
{
//    for(iterator i(obj),e; i!=e; ++i){
//        if(type(*i) == LUA_TTABLE){
//            addItems(widget, (void(QTreeWidget::*)(const QString&,const QVariant&))&QComboBox::addItem, *i);
//            //widget->addItems(list_cast<QString>(*i));
//        }
//    }
    return lq_general_init(widget, obj, lqtreewidgetitem_set_map);
}

template<>
void table_init_general<QTreeWidgetItem>(const luabind::argument & arg, const object& obj)
{
    lqtreewidgetitem_init(construct<QTreeWidgetItem>(arg), obj);
}

void lqtreewidgetitem_addChildren(QTreeWidgetItem* i, const object& obj)
{
    QList<QTreeWidgetItem*> children;
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj),e; i!=e; ++i){
            if(obj_name(*i) == "QTreeWidgetItem"){
                children.append(object_cast<QTreeWidgetItem*>(*i));
            }
        }
    }
    i->addChildren(children);
}

void lqtreewidgetitem_set_check_state(QTreeWidgetItem* i, int column, int state)
{
    i->setCheckState(column, Qt::CheckState(state));
}

void lqtreewidgetitem_set_flags(QTreeWidgetItem* i, int flag)
{
    i->setFlags(Qt::ItemFlags(flag));
}

object lqtreewidgetitem_takeChildren(QTreeWidgetItem* i)
{
    object obj(luabind::newtable(__pL));
    QList<QTreeWidgetItem*> children = i->takeChildren();
    for(int i=0; i<children.count(); i++){
        obj[i+1] = children.at(i);
    }
    return obj;
}

void lqtreewidgetitem_insertChildren(QTreeWidgetItem* i, int index, const object& obj)
{
    QList<QTreeWidgetItem*> children;
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj),e; i!=e; ++i){
            if(obj_name(*i) == "QTreeWidgetItem"){
                children.append(object_cast<QTreeWidgetItem*>(*i));
            }
        }
    }
    i->insertChildren(index,children);
}

template<class B, class R>
bool is_prop( R (B*))
{
    return true;
}

template<class B, class R>
bool is_prop( R(B::* )())
{
    return true;
}

template<class B, class R>
bool is_prop( R(B::* )()const)
{
    return true;
}

template<class B>bool is_prop( B f){return false;}

template<class Getter>
int test_func(Getter f){
    return is_prop(f);
}
LQTreeWidgetItem lqtreewidgetitem()
{
    return
     myclass_<QTreeWidgetItem,QTreeWidgetItem_wrap>("QTreeWidgetItem",lqtreewidgetitem_set_map)
    .def(constructor<>())
    .def(constructor<int>())
    .def(constructor<const QStringList&>())
    .def(constructor<const QStringList&, int>())
    .def(constructor<QTreeWidget*>())
    .def(constructor<QTreeWidget*, int>())
    .def(constructor<QTreeWidget*,const QStringList&>())
    .def(constructor<QTreeWidget*,const QStringList&, int>())
    .def(constructor<QTreeWidget*,QTreeWidgetItem*>())
    .def(constructor<QTreeWidget*,QTreeWidgetItem*, int>())
    .def(constructor<QTreeWidgetItem*>())
    .def(constructor<QTreeWidgetItem*, int>())
    .def(constructor<QTreeWidgetItem*,const QStringList&>())
    .def(constructor<QTreeWidgetItem*,const QStringList&, int>())
    .def(constructor<QTreeWidgetItem*,QTreeWidgetItem*>())
    .def(constructor<QTreeWidgetItem*,QTreeWidgetItem*, int>())
    .def(constructor<const QTreeWidgetItem&>())

    .def("__call", lqtreewidgetitem_init)
    .def("__init", table_init_general<QTreeWidgetItem>)
    .def("addChild", &QTreeWidgetItem::addChild, adopt(_2))
    .def("addChildren", &QTreeWidgetItem::addChildren)
    .def("child", &QTreeWidgetItem::child)
    .def("childCount", &QTreeWidgetItem::childCount)
    .def("columnCount", &QTreeWidgetItem::columnCount)
    .def("takeChild", &QTreeWidgetItem::takeChild, adopt(result))
    .def("takeChildren", lqtreewidgetitem_takeChildren)
    .def("indexOfChild", &QTreeWidgetItem::indexOfChild)
    .def("insertChild", &QTreeWidgetItem::insertChild, adopt(_3))
    .def("insertChildren", lqtreewidgetitem_insertChildren)

//    .def("data", &QTreeWidgetItem::data, &QTreeWidgetItem::data)
//    .def("setData", &QTreeWidgetItem::setData, &QTreeWidgetItem::setData)
//    .def("__lt", &QTreeWidgetItem::operator <)
    .def("data", &QTreeWidgetItem::data, &QTreeWidgetItem_wrap::def_data)
    .def("setData", &QTreeWidgetItem::setData, &QTreeWidgetItem_wrap::def_setData)
    .def("__lt", &QTreeWidgetItem::operator <, &QTreeWidgetItem_wrap::def_lt)

    .property("expanded", &QTreeWidgetItem::isExpanded, &QTreeWidgetItem::setExpanded)
    .property("firstColumnSpanned", &QTreeWidgetItem::isFirstColumnSpanned, &QTreeWidgetItem::setFirstColumnSpanned)
    .property("treeWidget", &QTreeWidgetItem::treeWidget)
    .property("selected", &QTreeWidgetItem::isSelected, &QTreeWidgetItem::setSelected)
    .property("hidden", &QTreeWidgetItem::isHidden, &QTreeWidgetItem::setHidden)
    .property("disabled", &QTreeWidgetItem::isDisabled, &QTreeWidgetItem::setDisabled)
    .property("flags", &QTreeWidgetItem::flags, lqtreewidgetitem_set_flags)

    .property("background", &QTreeWidgetItem::background, &QTreeWidgetItem::setBackground)
    .property("backgroundColor", &QTreeWidgetItem::backgroundColor, &QTreeWidgetItem::setBackgroundColor)
    .property("checkState", &QTreeWidgetItem::checkState, lqtreewidgetitem_set_check_state)
    .property("font", &QTreeWidgetItem::font, &QTreeWidgetItem::setFont)
    .property("foreground", &QTreeWidgetItem::foreground, &QTreeWidgetItem::setForeground)
    .property("icon", &QTreeWidgetItem::icon, &QTreeWidgetItem::setIcon)
    .property("statusTip", &QTreeWidgetItem::statusTip, &QTreeWidgetItem::setStatusTip)
    .property("text", &QTreeWidgetItem::text, &QTreeWidgetItem::setText)
    .property("textAlignment", &QTreeWidgetItem::textAlignment, &QTreeWidgetItem::setTextAlignment)
    .property("textColor", &QTreeWidgetItem::textColor, &QTreeWidgetItem::setTextColor)
    .property("toolTip", &QTreeWidgetItem::toolTip, &QTreeWidgetItem::setToolTip)
    .property("whatsThis", &QTreeWidgetItem::whatsThis, &QTreeWidgetItem::setWhatsThis)

    .property("type", &QTreeWidgetItem::type)
    .property("parent", &QTreeWidgetItem::parent)
    //.class_<QTreeWidgetItem>::def(smp.find(sp)->first.c_str(), &QTreeWidgetItem::setIcon)
    ;
}


QTreeWidget* lqtreewidget_init(QTreeWidget* widget, const object& obj)
{
    lqwidget_init(widget, obj);
    lq_general_init(widget, obj, lqtreewidget_set_map);
    for(iterator i(obj),e; i!=e; ++i){
        if(type(i.key()) == LUA_TSTRING && type(*i) == LUA_TTABLE){
            QString k = object_cast<QString> (i.key());
            if(k.compare("header",Qt::CaseInsensitive) == 0){
                widget->setHeaderLabels(list_cast<QString>(*i));
            }
        }
    }
    return widget;
}

template<>
void table_init_general<QTreeWidget>(const luabind::argument & arg, const object& obj)
{
    lqtreewidget_init(construct<QTreeWidget>(arg), obj);
}

void lqtreewidget_scrollToItem(QTreeWidget* w, QTreeWidgetItem* i, int hint)
{
    w->scrollToItem(i, QAbstractItemView::ScrollHint(hint));
}

void lqtreewidget_scrollToItem2(QTreeWidget* w, QTreeWidgetItem* i)
{
    w->scrollToItem(i);
}

QStringList lqtreewidget_get_header(QTreeWidget* w)
{
    QStringList list;
    QTreeWidgetItem* item = w->headerItem();
    for(int i=0;i<w->columnCount();i++){
        list.append( item->text(i) );
    }
    return list;
}

void lqtreewidget_test(QTreeWidget* w)
{
    (void)w;
}
namespace luabind{
QT_EMUN_CONVERTER(QItemSelectionModel::SelectionFlags)
QT_EMUN_CONVERTER(Qt::SortOrder)
QT_EMUN_CONVERTER(Qt::ItemFlags)
}
LQTreeWidget lqtreewidget()
{
    return
    myclass_<QTreeWidget, QTreeView>("QTreeWidget",lqtreewidget_set_map)
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("__call", lqtreewidget_init)
    .def("__init", table_init_general<QTreeWidget>)
    .def("addTopLevelItem", &QTreeWidget::addTopLevelItem, adopt(_2))
    .def("addTopLevelItems", &QTreeWidget::addTopLevelItems)
    .def("clear", &QTreeWidget::clear)
    .def("collapseItem", &QTreeWidget::collapseItem)
    .def("expandItem", &QTreeWidget::expandItem)
    .def("scrollToItem", lqtreewidget_scrollToItem)
    .def("scrollToItem", lqtreewidget_scrollToItem2)
    .def("selectedItems", &QTreeWidget::selectedItems)
    .def("findItems", &QTreeWidget::findItems)
    .def("findItems", tag_function<QList<QTreeWidgetItem*>(QTreeWidget*,const QString&,Qt::MatchFlags)>(boost::bind(&QTreeWidget::findItems, _1, _2, _3, 0)))
    .def("indexOfTopLevelItem", (int (QTreeWidget::*)(QTreeWidgetItem *) const)&QTreeWidget::indexOfTopLevelItem)
    .def("insertTopLevelItem", &QTreeWidget::insertTopLevelItem, adopt(_3))
    .def("insertTopLevelItems", &QTreeWidget::insertTopLevelItems)
    .def("itemAbove", &QTreeWidget::itemAbove)
    .def("itemAt", (QTreeWidgetItem*(QTreeWidget::*)(const QPoint&)const)&QTreeWidget::itemAt)
    .def("itemAt", (QTreeWidgetItem*(QTreeWidget::*)(int,int)const)&QTreeWidget::itemAt)
    .def("itemBelow", &QTreeWidget::itemBelow)
    .def("itemWidget", &QTreeWidget::itemWidget)
    .def("setItemWidget", &QTreeWidget::setItemWidget)
    .def("removeItemWidget", &QTreeWidget::removeItemWidget)
    .def("setCurrentItem", (void (QTreeWidget::*)(QTreeWidgetItem *))&QTreeWidget::setCurrentItem)
    .def("setCurrentItem", (void (QTreeWidget::*)(QTreeWidgetItem *,int))&QTreeWidget::setCurrentItem)
    .def("setCurrentItem", (void (QTreeWidget::*)(QTreeWidgetItem *,int,QItemSelectionModel::SelectionFlags))&QTreeWidget::setCurrentItem)
    .def("setHeaderItem", &QTreeWidget::setHeaderItem, adopt(_2))
    .def("setHeaderLabel", &QTreeWidget::setHeaderLabel)
    .def("setHeaderLabels", &QTreeWidget::setHeaderLabels)
    .def("sortColumn", &QTreeWidget::sortColumn)
    .def("sortItems", &QTreeWidget::sortItems)
    .def("takeTopLevelItem", &QTreeWidget::takeTopLevelItem, adopt(result))
    .def("topLevelItemCount", &QTreeWidget::topLevelItemCount)
    .def("topLevelItem", &QTreeWidget::topLevelItem)
    .def("visualItemRect", &QTreeWidget::visualItemRect)



    .property("columnCount", &QTreeWidget::columnCount, &QTreeWidget::setColumnCount)
    .property("currentColumn", &QTreeWidget::currentColumn)
    .property("currentItem", &QTreeWidget::currentItem)
    .property("invisibleRootItem", &QTreeWidget::invisibleRootItem)
    .sig_prop(lqtreewidget, currentItemChanged)
    .sig_prop(lqtreewidget, itemActivated)
    .sig_prop(lqtreewidget, itemChanged)
    .sig_prop(lqtreewidget, itemClicked)
    .sig_prop(lqtreewidget, itemCollapsed)
    .sig_prop(lqtreewidget, itemDoubleClicked)
    .sig_prop(lqtreewidget, itemEntered)
    .sig_prop(lqtreewidget, itemExpanded)
    .sig_prop(lqtreewidget, itemPressed)
    .sig_prop(lqtreewidget, itemSelectionChanged)
    .class_<QTreeWidget, QTreeView>::property("headerItem", &QTreeWidget::headerItem, &QTreeWidget::setHeaderItem)
    .property("headerLabels", lqtreewidget_get_header ,&QTreeWidget::setHeaderLabels)
    ;
}

QTableWidgetItem* lqtablewidgetitem_init(QTableWidgetItem* widget, const object& obj)
{
//    for(iterator i(obj),e; i!=e; ++i){
//        if(type(*i) == LUA_TTABLE){
//            addItems(widget, (void(QComboBox::*)(const QString&,const QVariant&))&QComboBox::addItem, *i);
//            //widget->addItems(table_cast<QString>(*i));
//        }
//    }
    return lq_general_init(widget, obj, lqtablewidgetitem_set_map);
}

template<>
void table_init_general<QTableWidgetItem>(const luabind::argument & arg, const object& obj)
{
    lqtablewidgetitem_init(construct<QTableWidgetItem>(arg), obj);
}

void lqtablewidgetitem_setCheckState(QTableWidgetItem* i, int s)
{
    i->setCheckState(Qt::CheckState(s));
}

void lqtablewidgetitem_setFlags(QTableWidgetItem* i, int s)
{
    i->setFlags(Qt::ItemFlags(s));
}
LQTableWidgetItem lqtablewidgetitem()
{
    return
     myclass_<QTableWidgetItem,QTableWidgetItem_wrap>("QTableWidgetItem",lqtablewidgetitem_set_map)
    .def(constructor<>())
    .def(constructor<int>())
    .def(constructor<const QString&>())
    .def(constructor<const QString&, int>())
    .def(constructor<const QIcon&,const QString&>())
    .def(constructor<const QIcon&,const QString&, int>())
    .def(constructor<const QTableWidgetItem&>())

    .def("__call", lqtablewidgetitem_init)
    .def("__init", table_init_general<QTableWidgetItem>)
//    .def("data", &QTableWidgetItem::data, &QTableWidgetItem::data)
//    .def("setData", &QTableWidgetItem::setData, &QTableWidgetItem::setData)
//    .def("__lt", &QTableWidgetItem::operator <)
    .def("data", &QTableWidgetItem::data, &QTableWidgetItem_wrap::def_data)
    .def("setData", &QTableWidgetItem::setData, &QTableWidgetItem_wrap::def_setData)
    .def("__lt", &QTableWidgetItem::operator <, &QTableWidgetItem_wrap::def_lt)

    .property("tableWidget", &QTableWidgetItem::tableWidget)
    .property("background", &QTableWidgetItem::background, &QTableWidgetItem::setBackground)
    .property("backgroundColor", &QTableWidgetItem::backgroundColor, &QTableWidgetItem::setBackgroundColor)
    .property("checkState", &QTableWidgetItem::checkState, lqtablewidgetitem_setCheckState)
    .property("flags", &QTableWidgetItem::flags, lqtablewidgetitem_setFlags)
    .property("font", &QTableWidgetItem::font, &QTableWidgetItem::setFont)
    .property("foreground", &QTableWidgetItem::foreground, &QTableWidgetItem::setForeground)
    .property("icon", &QTableWidgetItem::icon, &QTableWidgetItem::setIcon)
    .property("selected", &QTableWidgetItem::isSelected, &QTableWidgetItem::setSelected)
    .property("statusTip", &QTableWidgetItem::statusTip, &QTableWidgetItem::setStatusTip)
    .property("text", &QTableWidgetItem::text, &QTableWidgetItem::setText)
    .property("textAlignment", &QTableWidgetItem::textAlignment, &QTableWidgetItem::setTextAlignment)
    .property("textColor", &QTableWidgetItem::textColor, &QTableWidgetItem::setTextColor)
    .property("toolTip", &QTableWidgetItem::toolTip, &QTableWidgetItem::setToolTip)
    .property("whatsThis", &QTableWidgetItem::whatsThis, &QTableWidgetItem::setWhatsThis)
    .property("type", &QTableWidgetItem::type)
    .property("row", &QTableWidgetItem::row)
    .property("column", &QTableWidgetItem::column)
    ;
}

QTableWidget* lqtablewidget_init(QTableWidget* widget, const object& obj)
{
    lqwidget_init(widget, obj);
    lq_general_init(widget, obj, lqtablewidget_set_map);
    for(iterator i(obj),e; i!=e; ++i){
        if(type(i.key()) == LUA_TSTRING && type(*i) == LUA_TTABLE){
            QString k = object_cast<QString> (i.key());
            if(k.compare("vHeader",Qt::CaseInsensitive) == 0){
                widget->setVerticalHeaderLabels(list_cast<QString>(*i));
            }else if(k.compare("verticalHeader",Qt::CaseInsensitive) == 0){
                widget->setVerticalHeaderLabels(list_cast<QString>(*i));
            }else if(k.compare("hHeader",Qt::CaseInsensitive) == 0){
                widget->setHorizontalHeaderLabels(list_cast<QString>(*i));
            }else if(k.compare("vorizontalHeader",Qt::CaseInsensitive) == 0){
                widget->setHorizontalHeaderLabels(list_cast<QString>(*i));
            }
        }
    }
    return widget;
}

template<>
void table_init_general<QTableWidget>(const luabind::argument & arg, const object& obj)
{
    lqtablewidget_init(construct<QTableWidget>(arg), obj);
}

LQTableWidgetSelectionRange lqtablewidgetselectionrange()
{
    return
    class_<QTableWidgetSelectionRange>("QTableWidgetSelectionRange")
    .def(constructor<>())
    .def(constructor<int,int,int,int>())
    .def(constructor<const QTableWidgetSelectionRange&>())
    .def("topRow", &QTableWidgetSelectionRange::topRow)
    .def("bottomRow", &QTableWidgetSelectionRange::bottomRow)
    .def("leftColumn", &QTableWidgetSelectionRange::leftColumn)
    .def("rightColumn", &QTableWidgetSelectionRange::rightColumn)
    .def("columnCount", &QTableWidgetSelectionRange::columnCount)
    .def("rowCount", &QTableWidgetSelectionRange::rowCount)

    .property("top", &QTableWidgetSelectionRange::topRow)
    .property("bottom", &QTableWidgetSelectionRange::bottomRow)
    .property("left", &QTableWidgetSelectionRange::leftColumn)
    .property("right", &QTableWidgetSelectionRange::rightColumn)
    .property("column", &QTableWidgetSelectionRange::columnCount)
    .property("row", &QTableWidgetSelectionRange::rowCount)
    ;
}


void lqtablewidget_scrollToItem(QTableWidget* w, QTableWidgetItem* i, int hint)
{
    w->scrollToItem(i,QAbstractItemView::ScrollHint(hint));
}

void lqtablewidget_scrollToItem2(QTableWidget* w, QTableWidgetItem* i)
{
    w->scrollToItem(i);
}

QStringList lqtablewidget_get_h_header(QTableWidget* w)
{
    QStringList list;
    for(int i=0;i<w->columnCount();i++){
        list.append(w->horizontalHeaderItem(i)->text());
    }
    return list;
}

QStringList lqtablewidget_get_v_header(QTableWidget* w)
{
    QStringList list;
    for(int i=0;i<w->rowCount();i++){
        list.append(w->verticalHeaderItem(i)->text());
    }
    return list;
}

LQTableWidget lqtablewidget()
{
    return
    myclass_<QTableWidget, QTableView>("QTableWidget",lqtablewidget_set_map)
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def(constructor<int,int>())
    .def(constructor<int,int,QWidget*>())
    .def("__call", lqtablewidget_init)
    .def("__init", table_init_general<QTableWidget>)

    .def("cellWidget", &QTableWidget::cellWidget)
    .def("setCellWidget", &QTableWidget::setCellWidget)
    .def("column", &QTableWidget::column)
    .def("currentItem", &QTableWidget::currentItem)
    .def("setCurrentItem", (void (QTableWidget::*)(QTableWidgetItem *))&QTableWidget::setCurrentItem)
    .def("setCurrentItem", (void (QTableWidget::*)(QTableWidgetItem *, QItemSelectionModel::SelectionFlags))&QTableWidget::setCurrentItem)

    .def("currentRow", &QTableWidget::currentRow)
    .def("findItems", &QTableWidget::findItems)
    .def("selectedItems", &QTableWidget::selectedItems)
    .def("selectedRanges", &QTableWidget::selectedRanges)

    .def("horizontalHeaderItem", &QTableWidget::horizontalHeaderItem)
    .def("setHorizontalHeaderItem", &QTableWidget::setHorizontalHeaderItem, adopt(_3))
    .def("setHorizontalHeaderLabels", &QTableWidget::setHorizontalHeaderLabels)
    .def("takeHorizontalHeaderItem", &QTableWidget::takeHorizontalHeaderItem, adopt(result))

    .def("verticalHeaderItem", &QTableWidget::verticalHeaderItem)
    .def("setVerticalHeaderItem", &QTableWidget::setVerticalHeaderItem, adopt(_3))
    .def("setVerticalHeaderLabels", &QTableWidget::setVerticalHeaderLabels)
    .def("takeVerticalHeaderItem", &QTableWidget::takeVerticalHeaderItem, adopt(result))


    .def("item", &QTableWidget::item)
    .def("itemAt", (QTableWidgetItem *(QTableWidget::*)(int,int) const)&QTableWidget::itemAt)
    .def("itemAt", (QTableWidgetItem *(QTableWidget::*)(const QPoint&) const)&QTableWidget::itemAt)

    .def("removeCellWidget", &QTableWidget::removeCellWidget)
    .def("setCellWidget", &QTableWidget::setCellWidget)
    .def("row", &QTableWidget::row)
    .def("setCurrentCell", (void (QTableWidget::*)(int,int,QItemSelectionModel::SelectionFlags))&QTableWidget::setCurrentCell)
    .def("setCurrentCell", (void (QTableWidget::*)(int,int))&QTableWidget::setCurrentCell)
    .def("setCurrentItem", (void (QTableWidget::*)(QTableWidgetItem*,QItemSelectionModel::SelectionFlags))&QTableWidget::setCurrentItem)
    .def("setCurrentItem", (void (QTableWidget::*)(QTableWidgetItem*))&QTableWidget::setCurrentItem)

    .def("setItem", &QTableWidget::setItem, adopt(_4))
    .def("takeItem", &QTableWidget::takeItem, adopt(result))
    .def("setRangeSelected", &QTableWidget::setRangeSelected)
    .def("visualColumn", &QTableWidget::visualColumn)
    .def("visualRow", &QTableWidget::visualRow)
    .def("visualRect", &QTableWidget::visualRect)

    .def("clear", &QTableWidget::clear)
    .def("clearContents", &QTableWidget::clearContents)
    .def("insertColumn", &QTableWidget::insertColumn)
    .def("insertRow", &QTableWidget::insertRow)
    .def("removeColumn", &QTableWidget::removeColumn)
    .def("removeRow", &QTableWidget::removeRow)
    .def("scrollToItem", lqtablewidget_scrollToItem)
    .def("scrollToItem", lqtablewidget_scrollToItem2)


    .property("columnCount", &QTableWidget::columnCount, &QTableWidget::setColumnCount)
    .property("rowCount", &QTableWidget::rowCount, &QTableWidget::setRowCount)
    .property("currentColumn", &QTableWidget::currentColumn)

    .property("currentRow", &QTableWidget::currentRow)

    .sig_prop(lqtablewidget, cellActivated)
    .sig_prop(lqtablewidget, cellChanged)
    .sig_prop(lqtablewidget, cellClicked)
    .sig_prop(lqtablewidget, cellDoubleClicked)
    .sig_prop(lqtablewidget, cellEntered)
    .sig_prop(lqtablewidget, cellPressed)
    .sig_prop(lqtablewidget, currentCellChanged)
    .sig_prop(lqtablewidget, currentItemChanged)
    .sig_prop(lqtablewidget, currentRowChanged)
    .sig_prop(lqtablewidget, currentTextChanged)
    .sig_prop(lqtablewidget, itemActivated)
    .sig_prop(lqtablewidget, itemChanged)
    .sig_prop(lqtablewidget, itemClicked)
    .sig_prop(lqtablewidget, itemDoubleClicked)
    .sig_prop(lqtablewidget, itemEntered)
    .sig_prop(lqtablewidget, itemPressed)
    .sig_prop(lqtablewidget, itemSelectionChanged)

    .class_<QTableWidget, QTableView>::property("itemPrototype", &QTableWidget::itemPrototype, &QTableWidget::setItemPrototype)
    .property("horizontalHeader", lqtablewidget_get_h_header, &QTableWidget::setHorizontalHeaderLabels)
    .property("verticalHeader", lqtablewidget_get_v_header, &QTableWidget::setVerticalHeaderLabels)
    .property("hHeader", lqtablewidget_get_h_header, &QTableWidget::setHorizontalHeaderLabels)
    .property("vHeader", lqtablewidget_get_v_header, &QTableWidget::setVerticalHeaderLabels)
    ;
}

QVariant    lqmodelindex_data1(QModelIndex* w)
{
    return w->data();
}

QVariant    lqmodelindex_data2(QModelIndex* w, int role)
{
    return w->data( role );
}


LQModelIndex    lqmodelindex()
{
    return
    class_<QModelIndex>("QModelIndex")
    .def(constructor<>())
    .def(constructor<const QModelIndex&>())

    .def("child", &QModelIndex::child)
    .def("data", lqmodelindex_data1)
    .def("data", lqmodelindex_data2)
    .def("sibling", &QModelIndex::sibling)

    .def("__lt", &QModelIndex::operator <)
    .def("__eq", &QModelIndex::operator ==)

    .property("column", &QModelIndex::column)
    .property("flags", &QModelIndex::flags)
    .property("isValid", &QModelIndex::isValid)
    .property("model", &QModelIndex::model)
    .property("parent", &QModelIndex::parent)
    .property("row", &QModelIndex::row)
    ;
}

ENUM_FILTER(QAbstractItemView,defaultDropAction,setDefaultDropAction)
ENUM_FILTER(QAbstractItemView,editTriggers,setEditTriggers)
ENUM_FILTER(QAbstractItemView,horizontalScrollMode,setHorizontalScrollMode)
ENUM_FILTER(QAbstractItemView,selectionBehavior ,setSelectionBehavior )
ENUM_FILTER(QAbstractItemView,selectionMode ,setSelectionMode )
ENUM_FILTER(QAbstractItemView,textElideMode ,setTextElideMode )
ENUM_FILTER(QAbstractItemView,verticalScrollMode ,setVerticalScrollMode )


SIGNAL_PROPERYT(lqabstractitemview, activated, QAbstractItemView, "(const QModelIndex&)")
SIGNAL_PROPERYT(lqabstractitemview, clicked, QAbstractItemView, "(const QModelIndex&)")
SIGNAL_PROPERYT(lqabstractitemview, doubleClicked, QAbstractItemView, "(const QModelIndex&)")
SIGNAL_PROPERYT(lqabstractitemview, entered, QAbstractItemView, "(const QModelIndex&)")
SIGNAL_PROPERYT(lqabstractitemview, pressed, QAbstractItemView, "(const QModelIndex&)")
SIGNAL_PROPERYT(lqabstractitemview, viewportEntered, QAbstractItemView, "()")

LQAbstractItemView  lqabstractitemview()
{
    return
    class_<QAbstractItemView, QAbstractItemView_wrap, QAbstractScrollArea>("QAbstractItemView")
    .def(constructor<>())
    .def(constructor<QWidget*>())

    .property("alternatingRowColors", &QAbstractItemView::alternatingRowColors, &QAbstractItemView::setAlternatingRowColors)
    .property("autoScroll", &QAbstractItemView::hasAutoScroll, &QAbstractItemView::setAutoScroll )
    .property("autoScrollMargin", &QAbstractItemView::autoScrollMargin, &QAbstractItemView::setAutoScrollMargin )
    .property("defaultDropAction", QAbstractItemView_defaultDropAction, QAbstractItemView_setDefaultDropAction )
    .property("dragDropOverwriteMode", &QAbstractItemView::dragDropOverwriteMode, &QAbstractItemView::setDragDropOverwriteMode )
    .property("dragEnabled", &QAbstractItemView::dragEnabled, &QAbstractItemView::setDragEnabled )
    .property("editTriggers", QAbstractItemView_editTriggers, QAbstractItemView_setEditTriggers )
    .property("horizontalScrollMode", QAbstractItemView_horizontalScrollMode, QAbstractItemView_setHorizontalScrollMode )
    .property("iconSize", &QAbstractItemView::iconSize, &QAbstractItemView::setIconSize )
    .property("selectionBehavior", QAbstractItemView_selectionBehavior, QAbstractItemView_setSelectionBehavior )
    .property("selectionMode", QAbstractItemView_selectionMode, QAbstractItemView_setSelectionMode )
    .property("showDropIndicator", &QAbstractItemView::showDropIndicator, &QAbstractItemView::setDropIndicatorShown )
    .property("tabKeyNavigation", &QAbstractItemView::tabKeyNavigation, &QAbstractItemView::setTabKeyNavigation )
    .property("textElideMode", QAbstractItemView_textElideMode, QAbstractItemView_setTextElideMode )
    .property("verticalScrollMode", QAbstractItemView_verticalScrollMode, QAbstractItemView_setVerticalScrollMode)

    .property("currentIndex", &QAbstractItemView::currentIndex, &QAbstractItemView::setCurrentIndex)
    .def("setCurrentIndex", &QAbstractItemView::setCurrentIndex)
    .def("closePersistentEditor", &QAbstractItemView::closePersistentEditor)
    .def("indexAt", &QAbstractItemView::indexAt)
    .def("indexWidget", &QAbstractItemView::indexWidget)
    .def("setIndexWidget", &QAbstractItemView::setIndexWidget)
    .property("rootIndex", &QAbstractItemView::rootIndex)
    .property("setRootIndex", &QAbstractItemView::setRootIndex)
    .def("sizeHintForColumn", &QAbstractItemView::sizeHintForColumn)
    .def("sizeHintForIndex", &QAbstractItemView::sizeHintForIndex)
    .def("sizeHintForRow", &QAbstractItemView::sizeHintForRow)

    .def("clearSelection", &QAbstractItemView::clearSelection)
    .def("edit", (void (QAbstractItemView::*)(const QModelIndex &))&QAbstractItemView::edit)
    .def("scrollToTop", &QAbstractItemView::scrollToTop)
    .def("scrollToBottom", &QAbstractItemView::scrollToBottom)
    .def("update", (void (QAbstractItemView::*)(const QModelIndex &))&QAbstractItemView::update)
    .def("update", (void (QAbstractItemView::*)())&QAbstractItemView::update)

    .sig_prop(lqabstractitemview, activated)
    .sig_prop(lqabstractitemview, clicked)
    .sig_prop(lqabstractitemview, doubleClicked)
    .sig_prop(lqabstractitemview, entered)
    .sig_prop(lqabstractitemview, pressed)
    .sig_prop(lqabstractitemview, viewportEntered)
    ;
}


void lqcolumnview_scrollTo1(QColumnView* w, const QModelIndex & index, int hint)
{
    w->scrollTo(index, QColumnView::ScrollHint(hint));
}

void lqcolumnview_scrollTo2(QColumnView* w, const QModelIndex & index)
{
    w->scrollTo(index);
}

LQColumnView  lqcolumnview()
{
    return
    class_<QColumnView, QAbstractItemView>("QColumnView")
    .def(constructor<>())
    .def(constructor<QWidget*>())

    .property("columnWidths", &QColumnView::columnWidths, &QColumnView::setColumnWidths)
    .property("previewWidget", &QColumnView::previewWidget, &QColumnView::setPreviewWidget)
    .property("resizeGripsVisible", &QColumnView::resizeGripsVisible, &QColumnView::setResizeGripsVisible)

    .def("indexAt", &QColumnView::indexAt)
    .def("scrollTo", lqcolumnview_scrollTo1)
    .def("scrollTo", lqcolumnview_scrollTo2)
    .def("selectAll", &QColumnView::selectAll)
    .def("setRootIndex", &QColumnView::setRootIndex)
    .property("sizeHint", &QColumnView::sizeHint)
    .def("visualRect", &QColumnView::visualRect)
    ;
}

int lqheaderview_logicalIndexAt1(QHeaderView* w, int position)
{
    return w->logicalIndexAt(position);
}

int lqheaderview_logicalIndexAt2(QHeaderView* w, int x, int y)
{
    return w->logicalIndexAt(x,y);
}

int lqheaderview_logicalIndexAt3(QHeaderView* w, const QPoint & pos)
{
    return w->logicalIndexAt(pos);
}

void lqheaderview_setResizeMode1(QHeaderView* w, int mode)
{
    w->setResizeMode(QHeaderView::ResizeMode(mode));
}

void lqheaderview_setResizeMode2(QHeaderView* w, int index, int mode)
{
    w->setResizeMode(index, QHeaderView::ResizeMode(mode));
}

int lqheaderview_sortIndicatorOrder(QHeaderView* w)
{
    return (int)w->sortIndicatorOrder();
}

void lqheaderview_resizeSections2(QHeaderView* w, int mode)
{
    w->resizeSections(QHeaderView::ResizeMode(mode));
}

SIGNAL_PROPERYT(lqabstractitemview, geometriesChanged, QHeaderView, "()")
SIGNAL_PROPERYT(lqabstractitemview, sectionAutoResize, QHeaderView, "(int, QHeaderView::ResizeMode)")
SIGNAL_PROPERYT(lqabstractitemview, sectionClicked, QHeaderView, "(int)")
SIGNAL_PROPERYT(lqabstractitemview, sectionCountChanged, QHeaderView, "(int,int)")
SIGNAL_PROPERYT(lqabstractitemview, sectionDoubleClicked, QHeaderView, "(int)")
SIGNAL_PROPERYT(lqabstractitemview, sectionEntered, QHeaderView, "(int)")
SIGNAL_PROPERYT(lqabstractitemview, sectionHandleDoubleClicked, QHeaderView, "(int)")
SIGNAL_PROPERYT(lqabstractitemview, sectionMoved, QHeaderView, "(int,int,int)")
SIGNAL_PROPERYT(lqabstractitemview, sectionPressed, QHeaderView, "(int)")
SIGNAL_PROPERYT(lqabstractitemview, sectionResized, QHeaderView, "(int,int,int)")
SIGNAL_PROPERYT(lqabstractitemview, sortIndicatorChanged, QHeaderView, "(int,Qt::SortOrder)")

LQHeaderView lqheaderview()
{
    return
    class_<QHeaderView, QAbstractItemView>("QHeaderView")
    .def(constructor<Qt::Orientation>())
    .def(constructor<Qt::Orientation, QWidget*>())

    .property("cascadingSectionResizes", &QHeaderView::cascadingSectionResizes, &QHeaderView::setCascadingSectionResizes)
    .property("defaultAlignment", &QHeaderView::defaultAlignment, &QHeaderView::setDefaultAlignment)
    .property("defaultSectionSize", &QHeaderView::defaultSectionSize, &QHeaderView::setDefaultSectionSize)
    .property("highlightSections", &QHeaderView::highlightSections, &QHeaderView::setHighlightSections)
    .property("minimumSectionSize", &QHeaderView::minimumSectionSize, &QHeaderView::setMinimumSectionSize)
    .property("showSortIndicator", &QHeaderView::isSortIndicatorShown, &QHeaderView::setSortIndicatorShown)
    .property("stretchLastSection", &QHeaderView::stretchLastSection, &QHeaderView::setStretchLastSection)
    .property("clickable", &QHeaderView::isClickable, &QHeaderView::setClickable)
    .property("movable", &QHeaderView::isMovable, &QHeaderView::setMovable)

    .property("count", &QHeaderView::count)
    .property("hiddenSectionCount", &QHeaderView::hiddenSectionCount)
    .def("isSectionHidden", &QHeaderView::isSectionHidden)
    .def("setSectionHidden", &QHeaderView::setSectionHidden)
    .def("hideSection", &QHeaderView::hideSection)
    .property("length", &QHeaderView::length)
    .def("logicalIndex", &QHeaderView::logicalIndex)
    .def("logicalIndexAt", lqheaderview_logicalIndexAt1)
    .def("logicalIndexAt", lqheaderview_logicalIndexAt2)
    .def("logicalIndexAt", lqheaderview_logicalIndexAt3)
    .def("moveSection", &QHeaderView::moveSection)
    .property("offset", &QHeaderView::offset, &QHeaderView::setOffset)
    .def("setOffset", &QHeaderView::setOffset)
    .property("orientation", &QHeaderView::orientation)
    .def("resizeMode", &QHeaderView::resizeMode)
    .def("setResizeMode", lqheaderview_setResizeMode1)
    .def("setResizeMode", lqheaderview_setResizeMode2)

    .def("resizeSection", &QHeaderView::resizeSection)
    .def("resizeSections", lqheaderview_resizeSections2)
    .def("restoreState", &QHeaderView::restoreState)
    .def("saveState", (QByteArray(QHeaderView::* )()const)&QHeaderView::saveState)

    .def("setSortIndicator", &QHeaderView::setSortIndicator)
    .def("sortIndicatorOrder", lqheaderview_sortIndicatorOrder)
    .def("sortIndicatorSection", &QHeaderView::sortIndicatorSection)
    .def("sectionPosition", &QHeaderView::sectionPosition)
    .def("sectionSize", &QHeaderView::sectionSize)
    .def("sectionSizeHint", &QHeaderView::sectionSizeHint)
    .def("sectionViewportPosition", &QHeaderView::sectionViewportPosition)
    .def("showSection", &QHeaderView::showSection)
    .def("swapSections", &QHeaderView::swapSections)
    .def("visualIndex", &QHeaderView::visualIndex)
    .def("visualIndexAt", &QHeaderView::visualIndexAt)

    .def("headerDataChanged", &QHeaderView::headerDataChanged)
    .def("setOffsetToLastSection", &QHeaderView::setOffsetToLastSection)
    .def("setOffsetToSectionPosition", &QHeaderView::setOffsetToSectionPosition)

    .sig_prop(lqabstractitemview, geometriesChanged)
    .sig_prop(lqabstractitemview, sectionAutoResize)
    .sig_prop(lqabstractitemview, sectionClicked)
    .sig_prop(lqabstractitemview, sectionCountChanged)
    .sig_prop(lqabstractitemview, sectionDoubleClicked)
    .sig_prop(lqabstractitemview, sectionEntered)
    .sig_prop(lqabstractitemview, sectionHandleDoubleClicked)
    .sig_prop(lqabstractitemview, sectionMoved)
    .sig_prop(lqabstractitemview, sectionPressed)
    .sig_prop(lqabstractitemview, sectionResized)
    .sig_prop(lqabstractitemview, sortIndicatorChanged)
    ;
}


ENUM_FILTER(QListView,flow,setFlow)
ENUM_FILTER(QListView,layoutMode,setLayoutMode)
ENUM_FILTER(QListView,movement,setMovement)
ENUM_FILTER(QListView,resizeMode,setResizeMode)
ENUM_FILTER(QListView,viewMode,setViewMode)
LQListView lqlistview()
{
    return
    class_<QListView, QAbstractItemView>("QListView")
    .def(constructor<>())
    .def(constructor<QWidget*>())

            .property("batchSize", &QListView::batchSize, &QListView::setBatchSize)
            .property("flow", QListView_flow, QListView_setFlow)
            .property("gridSize", &QListView::gridSize, &QListView::setGridSize)
            .property("isWrapping", &QListView::isWrapping, &QListView::setWrapping)
            .property("layoutMode", QListView_layoutMode, QListView_setLayoutMode)
            .property("modelColumn", &QListView::modelColumn, &QListView::setModelColumn)
            .property("movement", QListView_movement, QListView_setMovement)
            .property("resizeMode", QListView_resizeMode, QListView_setResizeMode)
            .property("selectionRectVisible", &QListView::isSelectionRectVisible, &QListView::setSelectionRectVisible)
            .property("spacing", &QListView::spacing, &QListView::setSpacing)
            .property("uniformItemSizes", &QListView::uniformItemSizes, &QListView::setUniformItemSizes)
            .property("viewMode", QListView_viewMode, QListView_setViewMode)
            .property("wordWrap", &QListView::wordWrap, &QListView::setWordWrap)

    ;
}

ENUM_FILTER(QTableView,gridStyle,setGridStyle)

void lqtableview_sortByColumn1(QTableView* w, int column, int order)
{
    w->sortByColumn(column, Qt::SortOrder(order));
}
void lqtableview_sortByColumn2(QTableView* w, int column)
{
    w->sortByColumn(column);
}
LQTableView lqtableview()
{
    return
    class_<QTableView, QAbstractItemView>("QTableView")
    .def(constructor<>())
    .def(constructor<QWidget*>())
            .property("cornerButtonEnabled", &QTableView::isCornerButtonEnabled, &QTableView::setCornerButtonEnabled)
            .property("gridStyle", QTableView_gridStyle, QTableView_setGridStyle)
            .property("showGrid", &QTableView::showGrid, &QTableView::setShowGrid)
            .property("sortingEnabled", &QTableView::isSortingEnabled, &QTableView::setSortingEnabled)
            .property("wordWrap", &QTableView::wordWrap, &QTableView::wordWrap)
            .property("horizontalHeader", &QTableView::horizontalHeader, &QTableView::setHorizontalHeader)
            .property("verticalHeader", &QTableView::verticalHeader, &QTableView::setVerticalHeader)


            .def("clearSpans", &QTableView::clearSpans)
            .def("columnAt", &QTableView::columnAt)
            .def("columnSpan", &QTableView::columnSpan)
            .def("columnViewportPosition", &QTableView::columnViewportPosition)
            .def("columnWidth", &QTableView::columnWidth)
            .def("setColumnWidth", &QTableView::setColumnWidth)
            .def("isColumnHidden", &QTableView::isColumnHidden)
            .def("setColumnHidden", &QTableView::setColumnHidden)
            .def("isRowHidden", &QTableView::isRowHidden)
            .def("setRowHidden", &QTableView::setRowHidden)
            .def("rowAt", &QTableView::rowAt)
            .def("rowHeight", &QTableView::rowHeight)
            .def("setRowHeight", &QTableView::setRowHeight)
            .def("rowSpan", &QTableView::rowSpan)
            .def("rowViewportPosition", &QTableView::rowViewportPosition)
            .def("setSpan", &QTableView::setSpan)
            .def("showGrid", &QTableView::showGrid)
            .def("sortByColumn", lqtableview_sortByColumn1)
            .def("sortByColumn", lqtableview_sortByColumn2)

            .def("hideColumn", &QTableView::hideColumn)
            .def("hideRow", &QTableView::hideRow)
            .def("resizeColumnToContents", &QTableView::resizeColumnToContents)
            .def("resizeColumnsToContents", &QTableView::resizeColumnsToContents)
            .def("resizeRowToContents", &QTableView::resizeRowToContents)
            .def("resizeRowsToContents", &QTableView::resizeRowsToContents)
            .def("selectColumn", &QTableView::selectColumn)
            .def("selectRow", &QTableView::selectRow)
            .def("setShowGrid", &QTableView::setShowGrid)
            .def("showColumn", &QTableView::showColumn)
            .def("showRow", &QTableView::showRow)

    ;
}
void lqtreeview_sortByColumn1(QTreeView* w, int column, int order )
{
    w->sortByColumn(column, Qt::SortOrder(order));
}

void lqtreeview_sortByColumn2(QTreeView* w, int column )
{
    w->sortByColumn(column);
}

SIGNAL_PROPERYT(lqtreeview, collapsed, QTreeView, "(const QModelIndex&)")
SIGNAL_PROPERYT(lqtreeview, expanded, QTreeView, "(const QModelIndex&)")

LQTreeView lqtreeview()
{
    return
    class_<QTreeView, QAbstractItemView>("QTreeView")
    .def(constructor<>())
    .def(constructor<QWidget*>())
            .property("allColumnsShowFocus", &QTreeView::allColumnsShowFocus, &QTreeView::setAllColumnsShowFocus)
            .property("animated", &QTreeView::isAnimated, &QTreeView::setAnimated)
            .property("autoExpandDelay", &QTreeView::autoExpandDelay, &QTreeView::setAutoExpandDelay)
            .property("expandsOnDoubleClick", &QTreeView::expandsOnDoubleClick, &QTreeView::setExpandsOnDoubleClick)
            .property("headerHidden", &QTreeView::isHeaderHidden, &QTreeView::setHeaderHidden)
            .property("indentation", &QTreeView::indentation, &QTreeView::setIndentation)
            .property("itemsExpandable", &QTreeView::itemsExpandable, &QTreeView::setItemsExpandable)
            .property("rootIsDecorated", &QTreeView::rootIsDecorated, &QTreeView::setRootIsDecorated)
            .property("sortingEnabled", &QTreeView::isSortingEnabled, &QTreeView::setSortingEnabled)
            .property("uniformRowHeights", &QTreeView::uniformRowHeights, &QTreeView::setUniformRowHeights)
            .property("wordWrap", &QTreeView::wordWrap, &QTreeView::setWordWrap)
            .property("header", &QTreeView::header, &QTreeView::setHeader)

            .def("columnAt", &QTreeView::columnAt)
            .def("columnViewportPosition", &QTreeView::columnViewportPosition)
            .def("columnWidth", &QTreeView::columnWidth)
            .def("indexAbove", &QTreeView::indexAbove)
            .def("indexBelow", &QTreeView::indexBelow)
            .def("isColumnHidden", &QTreeView::isColumnHidden)
            .def("setColumnHidden", &QTreeView::setColumnHidden)
            .def("isExpanded", &QTreeView::isExpanded)
            .def("isFirstColumnSpanned", &QTreeView::isFirstColumnSpanned)
            .def("setFirstColumnSpanned", &QTreeView::setFirstColumnSpanned)
            .def("isRowHidden", &QTreeView::isRowHidden)
            .def("setRowHidden", &QTreeView::setRowHidden)
            .def("sortByColumn", lqtreeview_sortByColumn1)
            .def("sortByColumn", lqtreeview_sortByColumn2)

            .def("collapse", &QTreeView::collapse)
            .def("collapseAll", &QTreeView::collapseAll)
            .def("expand", &QTreeView::expand)
            .def("expandAll", &QTreeView::expandAll)
            .def("expandToDepth", &QTreeView::expandToDepth)
            .def("hideColumn", &QTreeView::hideColumn)
            .def("resizeColumnToContents", &QTreeView::resizeColumnToContents)
            .def("showColumn", &QTreeView::showColumn)

            .sig_prop(lqtreeview, collapsed)
            .sig_prop(lqtreeview, expanded)
    ;
}
