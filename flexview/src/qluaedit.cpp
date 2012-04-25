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
                QString s = tr("[%1]").arg(info.name);
                bres.insert(info.offset + goff, s);
                goff+=s.length();
                s = tr("[/%1]").arg(info.name);
                bres.insert(info.offset + info.len + goff, s);
                goff+=s.length();
            }
        }
        res += bres + "\r\n";
    }
    return res;
}
