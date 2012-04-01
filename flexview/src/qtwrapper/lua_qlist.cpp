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

static setter_map<QComboBox> lqcombobox_set_map;
static setter_map<QListWidgetItem> lqlistwidgetitem_set_map;
static setter_map<QListWidget> lqlistwidget_set_map;
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
//    for(iterator i(obj),e; i!=e; ++i){
//        if(type(*i) == LUA_TTABLE){
//            addItems(widget, (void(QComboBox::*)(const QString&,const QVariant&))&QComboBox::addItem, *i);
//            //widget->addItems(list_cast<QString>(*i));
//        }
//    }
    return lq_general_init(widget, obj, lqlistwidget_set_map);
}

template<>
void table_init_general<QListWidget>(const luabind::argument & arg, const object& obj)
{
    lqlistwidget_init(construct<QListWidget>(arg), obj);
}


struct TestItem
{
    TestItem(){
        qDebug()<<"TestItem()";
    }
    TestItem(const QString& t){
        m_text.setValue(t);
        qDebug()<<"TestItem(QString)";
    }
    virtual QVariant data(){
        qDebug()<<"TestItem::data  "<<m_text;
        return m_text;
    }
    QString text(){
        QVariant v = data();
        QString t = v.value<QString>();
        qDebug()<<"TestItem::text  "<<t;
        return t;
    }
    QVariant m_text;
};

struct TestItem_wrap : TestItem, wrap_base
{
    TestItem_wrap(){
        qDebug()<<"TestItem_wrap()";
    }
    TestItem_wrap(const QString& t):TestItem(t){
        qDebug()<<"TestItem_wrap(QString)";
    }
    virtual QVariant data(){
        QVariant v = call_member<QVariant>(this, "data");
        //object o = v.value<object>();
        //v = object_cast<QVariant>(o);
        //qDebug()<<"TestItem_wrap::data  "<<type(o);
        return v;
    }

    static QVariant def_data(TestItem& t){
        QVariant v = t.TestItem::data();
        qDebug()<<"TestItem_wrap::def_data   "<<v.value<QString>()<<"  "<<v;
        return v;
    }
};

LQListWidgetItem lqlistwidgetitem()
{
    (void)self;
    return
    class_<QListWidgetItem >("QListItem")
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
    .def("data", &QListWidgetItem::data)
    .def("setData", &QListWidgetItem::setData)
    .def("__lt", &QListWidgetItem::operator <)
//    .def("data", &QListWidgetItem::data, &QListWidgetItem_wrap::def_data)
//    .def("setData", &QListWidgetItem::setData, &QListWidgetItem_wrap::def_setData)
//    .def("__lt", &QListWidgetItem::operator <,  &QListWidgetItem_wrap::def_lt)
    .property("text", &QListWidgetItem::text, &QListWidgetItem::setText)

//    .scope
//    [
//            class_<TestItem,TestItem_wrap>("TestItem")
//              .def(constructor<>())
//              .def(constructor<const QString&>())
//              .def("data", &TestItem::data, &TestItem_wrap::def_data)
//              .def("text", &TestItem::text)
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

LQListWidget lqlistwidget()
{
    return
    class_<QListWidget, QFrame>("QListWidget")
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("__call", lqlistwidget_init)
    .def("__init", table_init_general<QListWidget>)
    .def("addItem", (void(QListWidget::*)(const QString&))&QListWidget::addItem)
    .def("addItem", (void(QListWidget::*)(QListWidgetItem*))&QListWidget::addItem)
    .def("sortItems", lqlistwidget_sortItems)
    .def("sortItems", lqlistwidget_sortItems2)
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
