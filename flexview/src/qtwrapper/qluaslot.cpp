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

void QLuaSlot::general_slot()
{
    call_member<void>(m_obj,m_method.toStdString().c_str());
}

void QLuaSlot::general_slot(char param)
{
    call_member<void>(m_obj,m_method.toStdString().c_str(), param);
}

void QLuaSlot::general_slot(short param)
{
    call_member<void>(m_obj,m_method.toStdString().c_str(), param);
}

void QLuaSlot::general_slot(int param)
{
    call_member<void>(m_obj,m_method.toStdString().c_str(), param);
}

void QLuaSlot::general_slot(QString param)
{
    call_member<void>(m_obj,m_method.toStdString().c_str(), param.toStdString().c_str());
}
