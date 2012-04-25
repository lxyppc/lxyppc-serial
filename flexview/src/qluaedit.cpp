#include "qluaedit.h"
#include <QtGui>

QLuaEdit::QLuaEdit(QWidget *parent) :
    QTextEdit(parent)
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    setFont(font);
    highlighter = new LuaHighlighter(document());
    setLineWrapMode(QTextEdit::NoWrap);
}

void QLuaEdit::addKeyWord(const QString& key)
{
    highlighter->addUserKeyword(key);
}

void QLuaEdit::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Tab){
        this->insertPlainText("    ");
    }else{
        QTextEdit::keyPressEvent(event);
    }
}

QString match(const QString& name, const std::map<QString,QString>& map)
{
    int len = 0;
    QString res;
    std::map<QString,QString>::const_iterator it = map.begin();
    for(; it != map.end(); it++){
        if(name.contains(it->first,Qt::CaseInsensitive)){
            if(it->first.length() > len){
                res = it->second;
                len = it->first.length();
            }
        }
    }
    return res;
}

QString QLuaEdit::toTagText() const
{
    QString res;
    QTextDocument* doc = this->document();
    int cnt = doc->blockCount();
    for(int i=0;i<cnt;i++){
        QTextBlock block = doc->findBlockByNumber(i);
        QString bres = block.text();
        MyTextBlockUserData* p = static_cast<MyTextBlockUserData*>(block.userData());
        if(p){
            int goff = 0;
            foreach(MyTextBlockUserData::HighlightInfo info, p->infoList){
                QString s = match(info.name,startMap);//  tr("[%1]").arg(info.name);
                bres.insert(info.offset + goff, s);
                goff+=s.length();
                s = match(info.name,endMap);//tr("[/%1]").arg(info.name);
                bres.insert(info.offset + info.len + goff, s);
                goff+=s.length();
            }
        }
        res += bres + "\r\n";
    }
    return res;
}

void QLuaEdit::setTag(const QString& name, const QString& start, const QString& end)
{
    startMap[name] = start;
    endMap[name] = end;
}



