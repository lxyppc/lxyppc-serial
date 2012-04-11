#include "lua_qaction.h"
#include "luabind/tag_function.hpp"
bool sigfunc_connect(QObject* sender, const char* signal, object func);
QLuaSlot* get_slot(const QObject* obj, const char* member);

SIGNAL_PROPERYT(lqaction, triggered, QAction, "()")
//void lqaction_set_triggered(QAction* act, object obj)
//{
//    QLuaSlot* slot = get_slot(act,"triggered()");
//    qDebug()<<type(obj);
//    if(slot){
//        slot->set_object(obj);
//    }else{
//        sigfunc_connect(act,"triggered()",obj);
//    }
//}
//
//object lqaction_get_triggered(const QAction* act)
//{
//    QLuaSlot* slot = get_slot(act,"triggered()");
//    if(slot){
//        return slot->get_object();
//    }
//    return object();
//}

static setter_map<QAction> lqaction_set_map;

QAction* lqaction_init(QAction* widget, const object& table)
{
    if(type(table) == LUA_TTABLE){
        for (iterator i(table), e; i != e; ++i){
            if(type(i.key()) == LUA_TSTRING){
                QString key = object_cast<QString>(i.key());
                if(lqaction_set_map.find(key) != lqaction_set_map.end()){
                    lqaction_set_map[key](widget,*i);
                }/*else if(key.compare("triggered", Qt::CaseInsensitive) == 0){
                    lqaction_set_triggered(widget, *i);
                }*/
            }

            if(type(*i) == LUA_TUSERDATA){
                if(q_cast(*i, (void(QAction::*)( const QIcon &))&QAction::setIcon, widget)){
                }else if(q_cast(*i, &QAction::setShortcut, widget)){
                }else if(q_cast(*i, &QAction::setMenu, widget)){
                }
            }/*else if(type(*i)== LUA_TSTRING){
                if(q_cast(*i, (QAction*(QToolBar::*)(const QString&))&QToolBar::addAction, widget)){
                }
            }*/
            //qDebug()<<"key:"<<toString(i.key())<<"val:"<<toString(*i);
        }
    }
    return widget;
}

void null_action_init(const argument& arg)
{
    construct<QAction, QObject*>(arg, 0);
}

void string_action_init(const argument& arg, const QString& text)
{
    construct<QAction,const QString&, QObject*>(arg,text, 0);
}

void table_action_init(const argument& arg, const object& table)
{
    lqaction_init(construct<QAction,QObject*>(arg,0), table);
}

LQAction lqaction()
{
    return
    myclass_<QAction,QObject>("QAction",lqaction_set_map)
        .def(constructor<QObject*>())
        .def(constructor<const QString &, QObject*>())
        .def(constructor<const QIcon &, const QString &, QObject* >())
        .def("__call", &lqaction_init)
        .def("__init", &table_action_init)
        .def("__init", &string_action_init)
        .def("__init", &null_action_init)

        .property("text",&QAction::text, &QAction::setText)
        .property("toolTip",&QAction::toolTip, &QAction::setToolTip)
        .property("checkable",&QAction::isCheckable, &QAction::setCheckable)
        .property("checked",&QAction::isChecked, &QAction::setChecked)
        .property("enabled",&QAction::isEnabled, &QAction::setEnabled)
        .property("visible",&QAction::isVisible, &QAction::setVisible)
        .property("statusTip",&QAction::statusTip, &QAction::setStatusTip)
        .property("triggered",&lqaction_get_triggered, &lqaction_set_triggered)
        .class_<QAction,QObject>::property("icon",&QAction::icon, &QAction::setIcon)
        .property("shortcut",&QAction::shortcut, &QAction::setShortcut)
        .property("menu", &QAction::menu, &QAction::setMenu)
        ;
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

QMenuBar* lqmenubar_init(QMenuBar* widget, const object& table)
{
    if(type(table) == LUA_TTABLE){
        for (iterator i(table), e; i != e; ++i){
            if(type(*i) == LUA_TUSERDATA){
                if(q_cast(*i, (void(QMenuBar::*)( QAction*))&QMenuBar::addAction, widget)){
                    QAction* act = object_cast<QAction*>(*i);
                    act->setParent(widget);
                }
            }else if(type(*i)== LUA_TSTRING){
                if(q_cast(*i, (QMenu*(QMenuBar::*)(const QString&))&QMenuBar::addMenu, widget)){
                }
            }
        }
    }
    return widget;
}

void table_menubar_init(const argument& arg, const object& table)
{
    lqmenubar_init(construct<QMenuBar>(arg), table);
}

LQMenuBar lqmenubar()
{
    return
    class_<QMenuBar,QWidget>("QMenuBar")
        .def(constructor<>())
        .def("addMenu", (QAction* (QMenuBar::*)(QMenu*))&QMenuBar::addMenu)
        .def("addMenu",(QMenu* (QMenuBar::*)(const QString &))&QMenuBar::addMenu)
        .def("addAction", (void (QMenuBar::*)(QAction *action))&QMenuBar::addAction)
        .def("addAction", (QAction* (QMenuBar::*)(const QString&))&QMenuBar::addAction)

        .def("insertMenu", ( QAction*(QMenuBar::*)(QAction *, QMenu *))&QMenuBar::insertMenu)
        .def("insertMenu", (QAction* (*)(QMenuBar*, int, QMenu*))&lqmenubar_insert_menu)
        .def("insertMenu", (QMenu* (*)(QMenuBar*, int, const QString&))&lqmenubar_insert_menu)

        .def("__call", &lqmenubar_init)
        .def("__init", &table_menubar_init)

        .property("defaultUp", &QMenuBar::isDefaultUp, &QMenuBar::setDefaultUp)
        ;
}


QMenu* lqmenu_init(QMenu* widget, const object& table)
{
    if(type(table) == LUA_TTABLE){
        for (iterator i(table), e; i != e; ++i){
            if(type(*i) == LUA_TUSERDATA){
                if(q_cast(*i, (void(QMenu::*)( QAction*))&QMenu::addAction, widget)){
                    QAction* act = object_cast<QAction*>(*i);
                    act->setParent(widget);
                }
            }else if(type(*i)== LUA_TSTRING){
                if(q_cast(*i, (QAction*(QMenu::*)(const QString&))&QMenu::addAction, widget)){
                }
            }
            //qDebug()<<"key:"<<toString(i.key())<<"val:"<<toString(*i);
        }
    }
    return widget;
}

void table_menu_init(const argument& arg, const object& table)
{
    lqmenu_init(construct<QMenu>(arg), table);
}

LQMenu  lqmenu()
{
    return
    class_<QMenu, QWidget>("QMenu")
        .def(constructor<>())
        .def(constructor<QWidget *>())
        .def(constructor<const QString&, QWidget *>())
        .def(constructor<const QString&>())
        .def("addAction", (QAction*(QMenu::*)(const QString &))&QMenu::addAction)
        .def("addAction", (QAction*(QMenu::*)(const QIcon &, const QString &))&QMenu::addAction)
        .def("addAction", (void(QMenu::*)(QAction*))&QMenu::addAction)
        .def("__call", &lqmenu_init)
        .def("__init", &table_menu_init)

        .property("title", &QMenu::title, &QMenu::setTitle)
        .property("icon", &QMenu::icon, &QMenu::setIcon)
        ;
}

QToolBar* lqtoolbar_init(QToolBar* widget, const object& table)
{
    if(type(table) == LUA_TTABLE){
        for (iterator i(table), e; i != e; ++i){
            if(type(*i) == LUA_TUSERDATA){
                if(q_cast(*i, (void(QToolBar::*)( QAction*))&QToolBar::addAction, widget)){
                    QAction* act = object_cast<QAction*>(*i);
                    act->setParent(widget);
                }
            }else if(type(*i)== LUA_TSTRING){
                if(q_cast(*i, (QAction*(QToolBar::*)(const QString&))&QToolBar::addAction, widget)){
                }
            }
            //qDebug()<<"key:"<<toString(i.key())<<"val:"<<toString(*i);
        }
    }
    return widget;
}

void table_toolbar_init(const argument& arg, const object& table)
{
    lqtoolbar_init(construct<QToolBar>(arg), table);
}

LQToolBar lqtoolbar()
{
    return
    class_<QToolBar, QWidget>("QToolBar")
         .def(constructor<>())
         .def(constructor<const QString&>())
         .def("addAction", (void(QToolBar::*)( QAction*))&QToolBar::addAction)
         .def("addAction", (QAction*(QToolBar::*)( const QString&))&QToolBar::addAction)
         .def("addAction", (QAction*(QToolBar::*)(const QIcon&,const QString&))&QToolBar::addAction)
         .def("toggleViewAction", &QToolBar::toggleViewAction)
         .def("__call", &lqtoolbar_init)
         .def("__init", &table_toolbar_init)
         .property("allowedAreas", &QToolBar::allowedAreas, &QToolBar::setAllowedAreas)
         .property("floatable", &QToolBar::isFloatable, &QToolBar::setFloatable)
         .property("floating", &QToolBar::isFloating)
         .property("movable", &QToolBar::isMovable, &QToolBar::setMovable)
         .property("allowedAreas", &QToolBar::allowedAreas, &QToolBar::setAllowedAreas)
         .property("orientation", &QToolBar::orientation, &QToolBar::setOrientation)
         ;
}


#define _r const QRect&
#define _p QPainter*
#define _ri int,int,int,int
#define  _R  (void (QIcon::*)(QPainter *, const QRect &, Qt::Alignment,QIcon::Mode,QIcon::State)const)
#define  _RI (void (QIcon::*)(QPainter *, int,int,int,int, Qt::Alignment,QIcon::Mode,QIcon::State)const)
#define _F(a, arg...) void (QIcon*,a, ## arg)

namespace luabind{
    QT_EMUN_CONVERTER(QIcon::Mode)
    QT_EMUN_CONVERTER(QIcon::State)
}
LQIcon lqicon()
{
    return
    class_<QIcon>("QIcon")
        .def(constructor<>())
        .def(constructor<const QIcon&>())
        .def(constructor<const QString&>())
        .def("paint", _R &QIcon::paint)
        .def("paint", _RI &QIcon::paint)
        .def("paint", tag_function<_F(_p,_r)>(boost::bind(_R &QIcon::paint, _1,_2,_3,Qt::AlignCenter,QIcon::Normal,QIcon::Off) ))
        .def("paint", tag_function<_F(_p,_r,Qt::Alignment)>(boost::bind(_R &QIcon::paint, _1,_2,_3,_4,QIcon::Normal,QIcon::Off) ))
        .def("paint", tag_function<_F(_p,_r,Qt::Alignment,QIcon::Mode)>(boost::bind(_R &QIcon::paint, _1,_2,_3,_4,_5,QIcon::Off) ))
        .def("paint", tag_function<_F(_p,_ri)>(boost::bind(_RI &QIcon::paint, _1,_2,_3,_4,_5,_6,Qt::AlignCenter,QIcon::Normal,QIcon::Off) ))
        .def("paint", tag_function<_F(_p,_ri,Qt::Alignment)>(boost::bind(_RI &QIcon::paint, _1,_2,_3,_4,_5,_6,_7,QIcon::Normal,QIcon::Off) ))
        .def("paint", tag_function<_F(_p,_ri,Qt::Alignment,QIcon::Mode)>(boost::bind(_RI &QIcon::paint, _1,_2,_3,_4,_5,_6,_7,_8,QIcon::Off) ))
        ;
}

