#include "lua_qeditor.h"
static setter_map<QHexEdit> lqhexeidt_set_map;

namespace luabind{
template<> QByteArray object_cast<QByteArray, object>(const object& obj)
{
    QByteArray arr;
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj),e; i!=e; ++i){
            int v = 0;
            if(type(*i) == LUA_TNUMBER){
                v = object_cast<int>(*i);
            }
            arr.append((char)v);
        }
    }
    return arr;
}
}


QHexEdit* lqhexedit_init(QHexEdit* widget, const object& obj)
{
    lqwidget_init(widget,obj);
    lq_general_init(widget, obj, lqhexeidt_set_map);
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj),e; i!=e; ++i){
            if(type(*i) == LUA_TTABLE){
                widget->setData(object_cast<QByteArray>(*i));
            }else if(type(*i) == LUA_TSTRING){
                QString s = object_cast<QString>(*i);
                widget->setData(s.toAscii());
            }
        }
    }
    return widget;
}

template<>
void table_init_general<QHexEdit>(const luabind::argument & arg, const object& obj)
{
    lqhexedit_init(construct<QHexEdit>(arg), obj);
}


QPlainTextEdit* lqplaintextedit_init(QPlainTextEdit* widget, const object& obj);
QLuaEdit* lqluaedit_init(QLuaEdit* widget, const object& obj)
{
    lqplaintextedit_init(widget,obj);
    if(type(obj) == LUA_TTABLE){
        for(iterator i(obj),e; i!=e; ++i){
            if(type(*i) == LUA_TTABLE){
                for(iterator i2(*i),e2; i2!=e2; ++i2){
                    if(type(*i2) == LUA_TSTRING){
                        widget->addKeyWord(object_cast<QString>(*i2));
                    }
                }
            }
        }
    }
    return widget;
}

template<>
void table_init_general<QLuaEdit>(const luabind::argument & arg, const object& obj)
{
    lqluaedit_init(construct<QLuaEdit>(arg), obj);
}

void lqhexedit_append(QHexEdit* w, const QByteArray& a)
{
    w->insert(w->data().size(),a);
    //w->setData(w->data() + a);
}

LQHexEdit  lqhexedit()
{
    return
    myclass_<QHexEdit, QWidget>("QHexEdit",lqhexeidt_set_map)
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("__call", lqhexedit_init)
    .def("__init", table_init_general<QHexEdit>)
    .def("undo", &QHexEdit::undo)
    .def("redo", &QHexEdit::redo)
    .def("clear", &QHexEdit::clear)
    .def("append", lqhexedit_append)
    .def("scrollToEnd", &QHexEdit::scrollToEnd)



    .property("overwriteMode", &QHexEdit::overwriteMode, &QHexEdit::setOverwriteMode)
    .property("addressOffset", &QHexEdit::addressOffset, &QHexEdit::setAddressOffset)
    .property("addressAreaColor", &QHexEdit::addressAreaColor, &QHexEdit::setAddressAreaColor)
    .property("highlightingColor", &QHexEdit::highlightingColor, &QHexEdit::setHighlightingColor)
    .property("selectionColor", &QHexEdit::selectionColor, &QHexEdit::setSelectionColor)
    .property("readOnly", &QHexEdit::isReadOnly, &QHexEdit::setReadOnly)

    .class_<QHexEdit, QWidget>::property("data", &QHexEdit::data, &QHexEdit::setData)
    ;
}


LQLuaEdit lqluaedit()
{
    return
    class_<QLuaEdit,QPlainTextEdit>("QLuaEdit")
    .def(constructor<>())
    .def(constructor<QWidget*>())
    .def("__call", lqluaedit_init)
    .def("__init", table_init_general<QLuaEdit>)
    .def("addKeyWord", &QLuaEdit::addKeyWord)
    .def("setTag", &QLuaEdit::setTag)
    .property("tagText", &QLuaEdit::toTagText)

    ;
}






