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
