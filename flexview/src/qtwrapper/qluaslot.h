#ifndef QLUASLOT_H
#define QLUASLOT_H

#include <QObject>
#include "lua.hpp"
#include <luabind/luabind.hpp>
#include <boost/smart_ptr.hpp>
using namespace luabind;

class QLuaSlot : public QObject
{
Q_OBJECT
public:
    explicit QLuaSlot(const QString& signature);
    QLuaSlot(const object& obj, const QString& signature);
    void emit_gen_signal();
    void emit_gen_signal(QString);
    void emit_gen_signal(int);
    ~QLuaSlot();
    QByteArray slot() const;
    QByteArray signal() const;
signals:
    void general_signal();
    void general_signal(char);
    void general_signal(short);
    void general_signal(int);
    void general_signal(QString);
public slots:
    void general_slot();
    void general_slot(char);
    void general_slot(short);
    void general_slot(int);
    void general_slot(QString);
private:
    object m_obj;
    QString m_method;
    QString m_signature;
};
//typedef boost::shared_ptr<QLuaSlot> auto_slot;

#endif // QLUASLOT_H
