#include "lua_qftp.h"
#include "qluaslot.h"
#include <luabind/adopt_policy.hpp>
namespace luabind{
    QT_EMUN_CONVERTER(QFtp::Command)
    QT_EMUN_CONVERTER(QFtp::Error)
    QT_EMUN_CONVERTER(QFtp::State)
    QT_EMUN_CONVERTER(QFtp::TransferMode)
    QT_EMUN_CONVERTER(QFtp::TransferType)
    QT_EMUN_CONVERTER(QUrlInfo::PermissionSpec)
}

QFile* lqftp_currentDevice(QFtp* w)
{
    return static_cast<QFile*>(w->currentDevice());
}

int lqftp_connectToHost(QFtp* w, const QString & host){ return w->connectToHost(host); }
int lqftp_get1(QFtp* w, const QString & file){ return w->get(file); }
int lqftp_get2(QFtp* w, const QString & file, QFile* f){ return w->get(file,f); }
int lqftp_get3(QFtp* w, const QString & file, QFile* f, QFtp::TransferType t){ return w->get(file,f,t); }
int lqftp_list1(QFtp* w){ return w->list(); }

int lqftp_login1(QFtp* w){ return w->login(); }
int lqftp_login2(QFtp* w, const QString& user){ return w->login(user); }


int lqftp_put1(QFtp* w, QFile* dev, const QString& file){ return w->put(dev,file);}
int lqftp_put2(QFtp* w, QFile* dev, const QString& file, QFtp::TransferType t){ return w->put(dev,file,t);}
int lqftp_put3(QFtp* w, const QByteArray& data, const QString& file){ return w->put(data,file);}
int lqftp_put4(QFtp* w, const QByteArray& data, const QString& file, QFtp::TransferType t){ return w->put(data,file,t);}
QByteArray lqftp_read(QFtp* w, qint64 max)
{
    QByteArray arr(max,0);
    qint64 r = w->read(arr.data(), max);
    arr.resize(r);
    return arr;
}

SIGNAL_PROPERYT(lqftp, commandFinished, QFtp, "(int,bool)")
SIGNAL_PROPERYT(lqftp, commandStarted, QFtp, "(int)")
SIGNAL_PROPERYT(lqftp, dataTransferProgress, QFtp, "(qint64,qint64)")
SIGNAL_PROPERYT(lqftp, done, QFtp, "(bool)")
SIGNAL_PROPERYT(lqftp, listInfo, QFtp, "(const QUrlInfo &)")
SIGNAL_PROPERYT(lqftp, rawCommandReply, QFtp, "(int,const QString&)")
SIGNAL_PROPERYT(lqftp, readyRead, QFtp, "()")
SIGNAL_PROPERYT(lqftp, stateChanged, QFtp, "(int)")
LQFtp lqftp()
{
    return
    class_<QFtp,QObject>("QFtp")
    .def(constructor<QObject*>())
    .def(constructor<>())
    .def("cd", &QFtp::cd)
    .def("clearPendingCommands", &QFtp::clearPendingCommands)
    .def("close", &QFtp::close)
    .def("connectToHost", &QFtp::connectToHost)
    .def("connectToHost", lqftp_connectToHost)
    .def("currentCommand", &QFtp::currentCommand)
    .def("currentDevice", lqftp_currentDevice)
    .def("currentId", &QFtp::currentId)
    .def("get", lqftp_get1)
    .def("get", lqftp_get2, adopt(_3))
    .def("get", lqftp_get3, adopt(_3))
    .def("list", &QFtp::list)
    .def("list", lqftp_list1)
    .def("login", &QFtp::login)
    .def("login", lqftp_login1)
    .def("login", lqftp_login2)
    .def("mkdir", &QFtp::mkdir)
    .def("put", lqftp_put1)
    .def("put", lqftp_put2)
    .def("put", lqftp_put3)
    .def("put", lqftp_put4)
    .def("rawCommand", &QFtp::rawCommand)
    .def("read", lqftp_read)
    .def("readAll", &QFtp::readAll)
    .def("remove", &QFtp::remove)
    .def("rename", &QFtp::rename)
    .def("rmdir", &QFtp::rmdir)
    .def("setProxy", &QFtp::setProxy)
    .def("setTransferMode", &QFtp::setTransferMode)
    .def("abort", &QFtp::abort)



    .property("error", &QFtp::error)
    .property("errorString", &QFtp::errorString)
    .property("hasPendingCommands", &QFtp::hasPendingCommands)
    .property("state", &QFtp::state)
    .sig_prop(lqftp, commandFinished)
    .sig_prop(lqftp, commandStarted)
    .sig_prop(lqftp, dataTransferProgress)
    .sig_prop(lqftp, done)
    .sig_prop(lqftp, listInfo)
    .sig_prop(lqftp, rawCommandReply)
    .sig_prop(lqftp, readyRead)
    .sig_prop(lqftp, stateChanged)
    ;
}

LQUrlInfo lqurlinfo()
{
    return
    class_<QUrlInfo>("QUrlInfo")
    .def(constructor<const QUrlInfo&>())
    .def(constructor<>())
    //.def(constructor<const QString&,int,const QString&,const QString&,qint64,const QDateTime&,const QDateTime&,bool,bool,bool,bool,bool,bool>())
    //.def(constructor<const QUrl&,int,const QString&,const QString&,qint64,const QDateTime&,const QDateTime&,bool,bool,bool,bool,bool,bool>())
    .def("setDir", &QUrlInfo::setDir)
    .def("setFile", &QUrlInfo::setFile)
    .def("setSymLink", &QUrlInfo::setSymLink)
    .def("setWritable", &QUrlInfo::setWritable)
    .def("setReadable", &QUrlInfo::setReadable)


    .property("group", &QUrlInfo::group, &QUrlInfo::setGroup)
    .property("isDir", &QUrlInfo::isDir, &QUrlInfo::setDir)
    .property("isExecutable", &QUrlInfo::isExecutable)
    .property("isFile", &QUrlInfo::isFile, &QUrlInfo::setFile)
    .property("isReadable", &QUrlInfo::isReadable, &QUrlInfo::setReadable)
    .property("isSymLink", &QUrlInfo::isSymLink, &QUrlInfo::setSymLink)
    .property("isValid", &QUrlInfo::isValid)
    .property("isWritable", &QUrlInfo::isWritable, &QUrlInfo::setWritable)
    .property("lastModified", &QUrlInfo::lastModified, &QUrlInfo::setLastModified)
    .property("lastRead", &QUrlInfo::lastRead, &QUrlInfo::setLastRead)
    .property("name", &QUrlInfo::name, &QUrlInfo::setName)
    .property("owner", &QUrlInfo::owner, &QUrlInfo::setOwner)
    .property("permissions", &QUrlInfo::permissions, &QUrlInfo::setPermissions)
    .property("size", &QUrlInfo::size, &QUrlInfo::setSize)
    ;
}

QStringList lqtextcodec_aliases(QTextCodec* w)
{
    QStringList res;
    QList<QByteArray> r = w->aliases();
    foreach(QByteArray a, r){
        res.append( QString::fromAscii(a.data()));
    }
    return res;
}

QString lqtextcodec_fromUnicode(QTextCodec* w, const QString& s)
{
    QByteArray r = w->fromUnicode(s);
    return QString::fromAscii(r.data());
}

QString lqtextcodec_toUnicode(QTextCodec* w, const QString& s)
{
    return w->toUnicode(s.toAscii());
}

QString lqtextcodec_name(QTextCodec* w)
{
    return QString::fromAscii(w->name().data());
}

QString lqtextcodec_defname(QTextCodec* w)
{
    return QString::fromAscii(QTextCodec_wrap::def_name(w).data());
}

QStringList lqtextcodec_availableCodecs()
{
    QStringList res;
    QList<QByteArray> r = QTextCodec::availableCodecs();
    foreach(QByteArray a, r){
        res.append( QString::fromAscii(a.data()));
    }
    return res;
}

QTextCodec * lqtextcodec_codecForHtml1(const char* ba)
{
    return QTextCodec::codecForHtml(QByteArray::fromRawData(ba,strlen(ba)));
}

QTextCodec * lqtextcodec_codecForHtml2(const char* ba, QTextCodec* def)
{
    return QTextCodec::codecForHtml(QByteArray::fromRawData(ba,strlen(ba)),def);
}

QTextCodec * lqtextcodec_codecForUtfText1(const char* ba)
{
    return QTextCodec::codecForUtfText(QByteArray::fromRawData(ba,strlen(ba)));
}

QTextCodec * lqtextcodec_codecForUtfText2(const char* ba, QTextCodec* def)
{
    return QTextCodec::codecForUtfText(QByteArray::fromRawData(ba,strlen(ba)),def);
}

LQTextCodec lqtextcodec()
{
    return
    class_<QTextCodec,QTextCodec_wrap>("QTextCodec")
    .def("canEncode", (bool(QTextCodec::*)(const QString&)const)&QTextCodec::canEncode)
    .def("fromUnicode", lqtextcodec_fromUnicode)
    .def("toUnicode", lqtextcodec_toUnicode)
    .property("aliases", lqtextcodec_aliases)
    .def("name", lqtextcodec_name, lqtextcodec_defname)
    .def("mibEnum", &QTextCodec::mibEnum, &QTextCodec_wrap::def_mibEnum)
    .scope[
        def("availableCodecs", lqtextcodec_availableCodecs),
        def("availableMibs", &QTextCodec::availableMibs),
        def("codecForCStrings", &QTextCodec::codecForCStrings),
        def("codecForLocale", &QTextCodec::codecForLocale),
        def("codecForMib", &QTextCodec::codecForMib),
        def("codecForTr", &QTextCodec::codecForTr),
        def("setCodecForCStrings", &QTextCodec::setCodecForCStrings),
        def("setCodecForLocale", &QTextCodec::setCodecForLocale),
        def("setCodecForTr", &QTextCodec::setCodecForTr),
        def("codecForHtml", lqtextcodec_codecForHtml1),
        def("codecForHtml", lqtextcodec_codecForHtml2),
        def("codecForUtfText", lqtextcodec_codecForUtfText1),
        def("codecForUtfText", lqtextcodec_codecForUtfText2),
        def("codecForName", (QTextCodec*(*)(const char*))&QTextCodec::codecForName)
    ]
    ;
}

QString lqtextdecoder_toUnicode(QTextDecoder* w, const QString& s)
{
    return w->toUnicode(s.toAscii());
}
LQTextDecoder lqtextdecoder()
{
    return
    class_<QTextDecoder>("QTextDecoder")
    .def("QTextDecoder", lqtextdecoder_toUnicode)
    .property("hasFailure", &QTextDecoder::hasFailure)
    ;
}

QString lqtextencoder_fromUnicode(QTextEncoder* w, const QString& s)
{
    QByteArray r = w->fromUnicode(s);
    return QString::fromAscii(r.data());
}

LQTextEncoder lqtextencoder()
{
    return
    class_<QTextEncoder>("QTextEncoder")
    .def("fromUnicode", lqtextencoder_fromUnicode)
    .property("hasFailure", &QTextEncoder::hasFailure)
    ;
}




