#include "lua_qt_wrapper.hpp"


void lqcombobox_addItem(QComboBox* combo, const QString& text)
{
    combo->addItem(text);
}

void lqcombobox_addItem(QComboBox* combo, const QString& text, const QString& userData)
{
    combo->addItem(text,userData);
}

void lqcombobox_addItem(QComboBox* combo, const QIcon& icon, const QString& text)
{
    combo->addItem(icon,text);
}

void lqcombobox_addItem(QComboBox* combo, const QIcon& icon, const QString& text, const QString& userData)
{
    combo->addItem(icon,text,userData);
}

namespace luabind{
template<> QStringList object_cast<QStringList,object>(object const& obj)
{
    QStringList s;
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj),e; i!=e; ++i){
            if(type(*i) == LUA_TSTRING){
                s.append(object_cast<QString>(*i));
            }
        }
    }
    return s;
}
}

void lqcombobox_addItems(QComboBox* combo, const object& obj)
{
    combo->addItems(object_cast<QStringList>(obj));
}

class_<QComboBox, QWidget> lqcombobox()
{
    return
    class_<QComboBox, QWidget>("QComboBox")
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("addItem", (void (*)(QComboBox*, const QString&))lqcombobox_addItem)
    .def("addItem", (void (*)(QComboBox*, const QString&, const QString&))lqcombobox_addItem)
    .def("addItem", (void (*)(QComboBox*, const QIcon&, const QString&))lqcombobox_addItem)
    .def("addItem", (void (*)(QComboBox*, const QIcon&, const QString&, const QString&))lqcombobox_addItem)
    .def("addItems", lqcombobox_addItems)

    .property("count", &QComboBox::count)
    .property("currentIndex", &QComboBox::currentIndex)
    .property("currentText", &QComboBox::currentText)
    ;
}
