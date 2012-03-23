#include "lua_qt_wrapper.hpp"
#include "qluaslot.h"
using namespace luabind;
bool sigfunc_connect(QObject* sender, const char* signal, object func);
QLuaSlot* get_slot(const QObject* obj, const char* member);

void lqaction_set_triggered(QAction* act, object obj)
{
    QLuaSlot* slot = get_slot(act,"triggered()");
    if(slot){
        slot->set_object(obj);
    }else{
        sigfunc_connect(act,"triggered()",obj);
    }
}

object lqaction_get_triggered(const QAction* act)
{
    QLuaSlot* slot = get_slot(act,"triggered()");
    if(slot){
        return slot->get_object();
    }
    return object();
}

LQAction lqaction()
{
    return
    class_<QAction,QObject>("QAction")
        .def(constructor<QObject*>())
        .def(constructor<const QString &, QObject*>())
        .def(constructor<const QIcon &, const QString &, QObject* >())
        .property("triggered",&lqaction_get_triggered, &lqaction_set_triggered);
}

QAction* lqmenubar_insert_menu(QMenuBar* menuBar, int pos, QMenu* menu)
{
    const QList<QAction*>& list = menuBar->actions();
    if(pos>=0 && pos< list.count()){
        return menuBar->insertMenu(list.at(pos), menu);
    }
    return menuBar->addMenu(menu);
}

QMenu* lqmenubar_insert_menu(QMenuBar* menuBar, int pos, const QString& title)
{
    QMenu* menu = new QMenu(title,menuBar);
    lqmenubar_insert_menu(menuBar,pos,menu);
    return menu;
}

LQMenuBar lqmenubar()
{
    return
    class_<QMenuBar,QWidget>("QMenuBar")
        .def(constructor<>())
        .def("addMenu", (QAction* (QMenuBar::*)(QMenu*))&QMenuBar::addMenu)
        .def("addMenu",(QMenu* (QMenuBar::*)(const QString &))&QMenuBar::addMenu)
        .def("insertMenu", ( QAction*(QMenuBar::*)(QAction *, QMenu *))&QMenuBar::insertMenu)
        .def("insertMenu", (QAction* (*)(QMenuBar*, int, QMenu*))&lqmenubar_insert_menu)
        .def("insertMenu", (QMenu* (*)(QMenuBar*, int, const QString&))&lqmenubar_insert_menu);
}

LQMenu  lqmenu()
{
    return
    class_<QMenu, QWidget>("QMenu")
        .def(constructor<>())
        .def(constructor<QWidget *>())
        .def(constructor<const QString&, QWidget *>())
        .def("addAction", (QAction*(QMenu::*)(const QString &))&QMenu::addAction)
        .def("addAction", (QAction*(QMenu::*)(const QIcon &, const QString &))&QMenu::addAction)
        .def("addAction", (void(QMenu::*)(QAction*))&QMenu::addAction)
        ;
}

LQIcon lqicon()
{
    return
    class_<QIcon>("QIcon")
        .def(constructor<>())
        .def(constructor<const QIcon&>())
        .def(constructor<const QString&>())
        ;
}





