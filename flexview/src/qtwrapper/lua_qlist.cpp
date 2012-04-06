#include "lua_qlist.h"

#include <luabind/luabind.hpp>
#include <luabind/tag_function.hpp>
#include <luabind/operator.hpp>
#include <boost/bind.hpp>
#include "qluaslot.h"

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

static setter_map<QComboBox> lqcombobox_set_map;
static setter_map<QListWidgetItem> lqlistwidgetitem_set_map;
static setter_map<QListWidget> lqlistwidget_set_map;
static setter_map<QTreeWidgetItem> lqtreewidgetitem_set_map;
static setter_map<QTreeWidget> lqtreewidget_set_map;
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
    return
     myclass_<QListWidgetItem>("QListItem",lqlistwidgetitem_set_map)
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
    .def("data", &QListWidgetItem::data, &QListWidgetItem::data)
    .def("setData", &QListWidgetItem::setData, &QListWidgetItem::setData)
    .def("__lt", &QListWidgetItem::operator <)
//    .def("data", &QListWidgetItem::data, &QListWidgetItem_wrap::def_data)
//    .def("setData", &QListWidgetItem::setData, &QListWidgetItem_wrap::def_setData)
//    .def("__lt", &QListWidgetItem::operator <,  &QListWidgetItem_wrap::def_lt)

    .property("listWidget", &QListWidgetItem::listWidget)
    .property("background", &QListWidgetItem::background, &QListWidgetItem::setBackground)
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
    QList<QListWidgetItem*> list = w->findItems(text, Qt::MatchFlags(f));
    for(int i=0;i<list.count();i++){
        obj[i+1] = list.at(i);
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
    myclass_<QListWidget, QFrame>("QListWidget",lqlistwidget_set_map)
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("__call", lqlistwidget_init)
    .def("__init", table_init_general<QListWidget>)
    .def("addItem", (void(QListWidget::*)(const QString&))&QListWidget::addItem)
    .def("addItem", (void(QListWidget::*)(QListWidgetItem*))&QListWidget::addItem)
    .def("addItems", lqlistwidget_addItems)
    .def("insertItem", (void(QListWidget::*)(int,const QString&))&QListWidget::insertItem)
    .def("insertItem", (void(QListWidget::*)(int,QListWidgetItem*))&QListWidget::insertItem)
    .def("insertItems", lqlistwidget_insertItems)

    .def("sortItems", lqlistwidget_sortItems)
    .def("sortItems", lqlistwidget_sortItems2)
    .def("row", &QListWidget::row)
    .def("item", &QListWidget::item)
    .def("itemAt", (QListWidgetItem*(QListWidget::*)(int,int)const)&QListWidget::itemAt)
    .def("itemAt", (QListWidgetItem*(QListWidget::*)(const QPoint&)const)&QListWidget::itemAt)
    .def("itemWidget", &QListWidget::itemWidget)
    .def("setItemWidget", &QListWidget::setItemWidget)
    .def("takeItem", &QListWidget::takeItem)
    .def("findItems", lqlistwidget_finditems)
    .def("selectedItems", lqlistwidget_selecteditems)
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

LQTreeWidgetItem lqtreewidgetitem()
{

    return
     myclass_<QTreeWidgetItem>("QTreeItem",lqtreewidgetitem_set_map)
     #if 0
    .def(constructor<>())
    .def(constructor<int>())
    .def(constructor<const QStringList&>())
    .def(constructor<const QStringList&, int>())

    .def(constructor<const QTreeWidgetItem&>())
    .def(constructor<QTreeWidget*>())
    .def(constructor<QTreeWidget*, int>())
    .def(constructor<const QString&>())
    .def(constructor<const QString&, QTreeWidget*>())
    .def(constructor<const QString&, QTreeWidget*, int>())
    .def(constructor<const QIcon&,const QString&>())
    .def(constructor<const QIcon&,const QString&, QTreeWidget*>())
    .def(constructor<const QIcon&,const QString&, QTreeWidget*, int>())

    .def("__call", lqtreewidgetitem_init)
    .def("__init", table_init_general<QTreeWidgetItem>)
    .def("data", &QTreeWidgetItem::data, &QTreeWidgetItem::data)
    .def("setData", &QTreeWidgetItem::setData, &QTreeWidgetItem::setData)
    .def("__lt", &QTreeWidgetItem::operator <)
//    .def("data", &QTreeWidgetItem::data, &QTreeWidgetItem_wrap::def_data)
//    .def("setData", &QTreeWidgetItem::setData, &QTreeWidgetItem_wrap::def_setData)
//    .def("__lt", &QTreeWidgetItem::operator <,  &QTreeWidgetItem_wrap::def_lt)

    .property("treeWidget", &QTreeWidgetItem::treeWidget)
    .property("background", &QTreeWidgetItem::background, &QTreeWidgetItem::setBackground)
    .property("checkState", &QTreeWidgetItem::checkState, lqtreewidgetitem_set_check_state)
    .property("flags", &QTreeWidgetItem::flags, lqtreewidgetitem_set_flags)
    .property("font", &QTreeWidgetItem::font, &QTreeWidgetItem::setFont)
    .property("foreground", &QTreeWidgetItem::foreground, &QTreeWidgetItem::setForeground)
    .property("hidden", &QTreeWidgetItem::isHidden, &QTreeWidgetItem::setHidden)
    .property("icon", &QTreeWidgetItem::icon, &QTreeWidgetItem::setIcon)
    .property("selected", &QTreeWidgetItem::isSelected, &QTreeWidgetItem::setSelected)
    .property("statusTip", &QTreeWidgetItem::statusTip, &QTreeWidgetItem::setStatusTip)
    .property("text", &QTreeWidgetItem::text, &QTreeWidgetItem::setText)
    .property("textAlignment", &QTreeWidgetItem::textAlignment, &QTreeWidgetItem::setTextAlignment)
    .property("textColor", &QTreeWidgetItem::textColor, &QTreeWidgetItem::setTextColor)
    .property("toolTip", &QTreeWidgetItem::toolTip, &QTreeWidgetItem::setToolTip)
    .property("whatsThis", &QTreeWidgetItem::whatsThis, &QTreeWidgetItem::setWhatsThis)
    .property("type", &QTreeWidgetItem::type)
    .property("row", lqtreewidgetitem_row)
#endif
    ;
}


QTreeWidget* lqtreewidget_init(QTreeWidget* widget, const object& obj)
{
    lqwidget_init(widget, obj);
//    for(iterator i(obj),e; i!=e; ++i){
//        if(type(*i) == LUA_TTABLE){
//            addItems(widget, (void(QTreeWidget::*)(const QString&,const QVariant&))&QComboBox::addItem, *i);
//            //widget->addItems(list_cast<QString>(*i));
//        }
//    }
    return lq_general_init(widget, obj, lqtreewidget_set_map);
}

template<>
void table_init_general<QTreeWidget>(const luabind::argument & arg, const object& obj)
{
    lqtreewidget_init(construct<QTreeWidget>(arg), obj);
}

LQTreeWidget lqtreewidget()
{
    return
    class_<QTreeWidget, QFrame>("QTreeWidget")
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("__call", lqtreewidget_init)
    .def("__init", table_init_general<QTreeWidget>)
    ;
}
