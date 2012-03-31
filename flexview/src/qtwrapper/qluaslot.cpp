#include "qluaslot.h"
#include <QDebug>

QLuaSlot::QLuaSlot(const QString& signature) :
    QObject(0),m_signature(signature)
{
    //qDebug()<<"QLua Slot create: "<<this;;
}

QLuaSlot::QLuaSlot(const object& obj, const QString& signature) :
        QObject(0), m_obj(obj),m_signature(signature)
{
    m_method = signature.left( signature.indexOf(QChar('('),0));
    //qDebug()<<"QLua Slot create by obj: "<<this;;
}

QLuaSlot::~QLuaSlot()
{
    //qDebug()<<"QLua Slot delete:"<<this;
}

void QLuaSlot::emit_gen_signal()
{
    emit general_signal();
}

void QLuaSlot::emit_gen_signal(QString s)
{
    emit general_signal(s);
}

void QLuaSlot::emit_gen_signal(int v)
{
    emit general_signal(v);
}

QByteArray QLuaSlot::slot() const
{
    QString sub = m_signature;
    sub.remove(0, sub.indexOf(QChar('(')));
    QString m = QString("1general_slot%1").arg(sub);
    return m.toAscii();
}

QByteArray QLuaSlot::signal() const
{
    QString sub = m_signature;
    sub.remove(0, sub.indexOf(QChar('(')));
    QString m = QString("2general_signal%1").arg(sub);
    return m.toAscii();
}

void general_slot(const object& m_obj, const QString& m_method)
{
    if(type(m_obj) == LUA_TFUNCTION){
        call_function<void>(m_obj);
    }else if(type(m_obj) == LUA_TTABLE){
        object c,f;
        for(iterator i(m_obj),e;i!=e;++i){
            if(type(*i) == LUA_TUSERDATA){
                c = *i;
            }else if(type(*i) == LUA_TFUNCTION){
                f = *i;
            }else if(type(*i) == LUA_TSTRING){
                f = *i;
            }
        }
        if(f && c){
            if(type(f) == LUA_TFUNCTION){
                call_function<void>(f,c);
            }else if(type(f) == LUA_TSTRING){
                call_member<void>(c,object_cast<const char*>(f));
            }
        }
    }else{
        call_member<void>(m_obj,m_method.toStdString().c_str());
    }
}

template<class T>
void general_slot(const object& m_obj, const QString& m_method, T t)
{
    if(type(m_obj) == LUA_TFUNCTION){
        call_function<void>(m_obj,t);
    }else if(type(m_obj) == LUA_TTABLE){
        object c,f;
        for(iterator i(m_obj),e;i!=e;++i){
            if(type(*i) == LUA_TUSERDATA){
                c = *i;
            }else if(type(*i) == LUA_TFUNCTION){
                f = *i;
            }else if(type(*i) == LUA_TSTRING){
                f = *i;
            }
        }
        if(f && c){
            if(type(f) == LUA_TFUNCTION){
                call_function<void>(f,c,t);
            }else if(type(f) == LUA_TSTRING){
                call_member<void>(c,object_cast<const char*>(f),t);
            }
        }
    }else{
        call_member<void>(m_obj,m_method.toStdString().c_str(),t);
    }
}

inline void gen_slot(const object& m_obj, const QString& m_method)
{
    try{
        general_slot(m_obj,m_method);
    }
    catch (...)
    {}
}

template<typename T>
inline void gen_slot(const object& m_obj, const QString& m_method, T t)
{
    try{
        general_slot(m_obj,m_method,t);
    }
    catch (...)
    {}
}

void QLuaSlot::general_slot()
{
    ::gen_slot(m_obj,m_method);
}

void QLuaSlot::general_slot(char param)
{
    ::gen_slot(m_obj,m_method,param);
}

void QLuaSlot::general_slot(short param)
{
    ::gen_slot(m_obj,m_method,param);
}

void QLuaSlot::general_slot(int param)
{
    ::gen_slot(m_obj,m_method,param);
}

void QLuaSlot::general_slot(bool param)
{
    ::gen_slot(m_obj,m_method,param);
}

void QLuaSlot::general_slot(const QString& param)
{
    ::gen_slot(m_obj,m_method,param.toStdString().c_str());
}
