#include <QtGui>
#include "qluaslot.h"
#include <luabind/luabind.hpp>
#include "../luadialog.h"
#include "lite_ptr.h"
#include "lua_qt_wrapper.hpp"
using namespace luabind;
typedef lite_ptr<QLuaSlot> auto_slot;
Q_DECLARE_METATYPE(auto_slot)
lua_State* __pL = 0;

static QString getName(const QString& s){
    return s.left( s.indexOf(QChar('('),0));
}

bool checkMember(int index, const char * name)
{
    object o1(from_stack(__pL, index));
    if(type(o1) == LUA_TUSERDATA){
        object fun = o1[name];
        if(!fun){
            throw std::runtime_error(QString("member: %1 not defined").arg(name).toStdString());
            return false;
        }
        if(type(fun) != LUA_TFUNCTION){
            throw std::runtime_error(QString("member: %1 is not function").arg(name).toStdString());
            return false;
        }
    }else{
        throw std::runtime_error(QString("parameter %1 is not a valid object").arg(index).toStdString());
        return false;
    }
    return true;
}

QLuaSlot* get_signal(QObject* obj, const char* signal)
{
    QByteArray sig = QMetaObject::normalizedSignature(signal);
    QVariant v = obj->property(sig);
    if(v.isValid()){
        if(v.canConvert<auto_slot >()){
            auto_slot aslot = v.value<auto_slot>();
            return aslot.get();
        }
    }
    {
        auto_slot aslot(new QLuaSlot(signal));
        QVariant v;
        v.setValue(aslot);
        obj->setProperty(sig, v);
        return aslot.get();
    }
}

QLuaSlot* get_slot(QObject* obj, int index, const char* member)
{
    QByteArray mem = QMetaObject::normalizedSignature(member);
    QVariant v = obj->property(mem);
    if(v.isValid()){
        if(v.canConvert<auto_slot >()){
            auto_slot aslot = v.value<auto_slot>();
            return aslot.get();
        }
    }
    {
        auto_slot aslot(new QLuaSlot(object(from_stack(__pL, index)) , member));
        QVariant v;
        v.setValue(aslot);
        obj->setProperty(mem, v);
        return aslot.get();
    }
}

bool sigslot_connect(QObject* sender, const char* signal, QObject* recv, const char* member)
{
    QString s = QString("2%1").arg(signal);
    QString m = QString("1%1").arg(member);
    QByteArray sig = QMetaObject::normalizedSignature(signal);
    QByteArray slt = QMetaObject::normalizedSignature(member);
    int iSig = sender->metaObject()->indexOfSignal(sig);
    int iSlot = recv->metaObject()->indexOfSlot(slt);
    bool res = false;
    //qDebug()<<"iSignal:"<<iSig<<"  iSlot:"<<iSlot;
    //qDebug()<<(int)type(object(from_stack(__pL, 1)))<<(int)type(object(from_stack(__pL, 2)))
    //        <<(int)type(object(from_stack(__pL, 3)))<<(int)type(object(from_stack(__pL, 4)));
    if(iSig != -1 && iSlot != -1){
        res = QObject::connect(sender, s.toStdString().c_str(), recv, m.toStdString().c_str());
    }else if(iSig == -1 && iSlot == -1){
        if(!checkMember(1, getName(signal).toStdString().c_str())) return false;
        if(!checkMember(3, getName(member).toStdString().c_str())) return false;
        QLuaSlot* p_signal = get_signal(sender, signal);
        QLuaSlot* p_slot = get_slot(recv, 3, member);
        res = QObject::connect(p_signal, p_signal->signal() , p_slot, p_slot->slot());
    }else if(iSig == -1){
        // no signal, has slot
        if(!checkMember(1, getName(signal).toStdString().c_str())) return false;
        QLuaSlot* p_signal = get_signal(sender, signal);
        res = QObject::connect(p_signal, p_signal->signal(), recv, m.toStdString().c_str());
    }else{
        // has signal, not slot
        if(!checkMember(3, getName(member).toStdString().c_str())) return false;
        QLuaSlot* p_slot = get_slot(recv, 3, member);
        res = QObject::connect(sender, s.toStdString().c_str(), p_slot, p_slot->slot());
    }
    return res;
}

void emit_signal(QObject* sender, object obj)
{
    const char* signal = object_cast<const char*>(obj);
    QByteArray sig = QMetaObject::normalizedSignature(signal);
    //qDebug()<<"emit_signal "<<object_cast<const char*>(obj)<<"  "<<sender->property(sig).toString();
    //qDebug()<<(bool)p1<<(bool)p2<<(bool)p3;
    //qDebug()<<"top:"<<lua_gettop(__pL);
    int top = lua_gettop(__pL);
    QVariant v = sender->property(sig);
    if(v.isValid() && v.canConvert<auto_slot>()){
    }else{
        return;
    }
    auto_slot s = v.value<auto_slot>();
    switch(top){
    case 2:
        {
            s.get()->emit_gen_signal();
        }
        break;
    case 3:
        {
            object p1(from_stack(__pL, 3));
            //qDebug()<<"type:"<<type(p1);
            if(type(p1) == LUA_TSTRING){
                s.get()->emit_gen_signal(object_cast<QString>(p1));
            }else if(type(p1) == LUA_TNUMBER){
                s.get()->emit_gen_signal(object_cast<int>(p1));
            }
        }
        break;
    }
}

void register_classes(lua_State* L, char const* name = 0)
{
    __pL = L;
    luabind::open(L);
    luabind::module(L, name)
    [
        lqobject(),
        lqwidget(),

        class_<QDialog, QWidget>("QDialog")
            .def(constructor<>()),


        class_<QMainWindow, QWidget>("QMainWindow")
            .def(constructor<>())
            .def("setCentralWidget",&QMainWindow::setCentralWidget)
            .def("menuBar",(QMenuBar *(QMainWindow::*)()const)&QMainWindow::menuBar),

        class_<QFrame,QWidget>("QFrame")
            .def(constructor<>()),

        class_<QAbstractScrollArea,QFrame>("QAbstractScrollArea")
            .def(constructor<>()),

        class_<QMdiArea,QAbstractScrollArea>("QMdiArea")
            .def(constructor<>()),

        class_<LuaDialog,QDialog>("LuaDialog")
            .def(constructor<>())
            .def("loadScript", &LuaDialog::loadScript)
            .def("saveScript", &LuaDialog::saveScript),

        class_<QAction,QObject>("QAction")
            .def(constructor<QObject*>())
            .def(constructor<const QString &, QObject*>())
            .def(constructor<const QIcon &, const QString &, QObject* >()),

        class_<QMenuBar,QWidget>("QMenuBar")
            .def(constructor<>())
            .def("addMenu", (QAction* (QMenuBar::*)(QMenu*))&QMenuBar::addMenu)
            .def("addMenu",(QMenu* (QMenuBar::*)(const QString &))&QMenuBar::addMenu),

        class_<QMenu, QWidget>("QMenu")
            .def(constructor<>())
            .def(constructor<QWidget *>())
            .def(constructor<const QString&, QWidget *>())
            .def("addAction", (QAction*(QMenu::*)(const QString &))&QMenu::addAction)
            .def("addAction", (QAction*(QMenu::*)(const QIcon &, const QString &))&QMenu::addAction),

        def("connect", (bool(*)(QObject* , const char* , QObject* , const char* ))&sigslot_connect),
        def("emit_signal", (void (*)(QObject*,object))&emit_signal),
        def("emit_signal", (void (*)(QObject*,object,object))&emit_signal),
        def("emit_signal", (void (*)(QObject*,object,object,object))&emit_signal),
        def("emit_signal", (void (*)(QObject*,object,object,object,object))&emit_signal)
    ];
}

static int pcall_handler(lua_State* L)
{
    (void)L;
    return 1;
}

void run_script_init(QMainWindow* mainwindow)
{
    QFile file("../src/script.lua");
    if(!file.open(QFile::ReadOnly|QFile::Text)){
        qDebug()<<"script file missing";
        return;
    }
    try{
        char const* str = file.readAll().data();
        lua_pushcclosure(__pL, &pcall_handler, 0);
        if (luaL_loadbuffer(__pL, str, std::strlen(str), str))
        {
            std::string err(lua_tostring(__pL, -1));
            lua_pop(__pL, 2);
            qDebug()<<"Script load fail:"<<err.c_str();
        }else{
            if (lua_pcall(__pL, 0, 0, -2))
            {
                std::string err(lua_tostring(__pL, -1));
                lua_pop(__pL, 2);
                qDebug()<<"Script call fail:"<<err.c_str();
            }
            call_function<int>(__pL, "init_mainwindow", mainwindow);
        }
    }
    catch (luabind::error const& e)
    {
            std::cerr << "Terminated with exception: \"" << e.what() << "\"\n"
                    << lua_tostring(e.state(), -1) << "\n";
            return;
    }
    catch (std::exception const& e)
    {
            std::cerr << "Terminated with exception: \"" << e.what() << "\"\n";
            return;
    }
    catch (std::string const &e)
    {
            std::cerr << "Terminated with unknown exception\n" << e;
            return;
    }
    catch (...)
    {
            std::cerr << "Terminated with unknown exception\n";
            return;
    }

}
