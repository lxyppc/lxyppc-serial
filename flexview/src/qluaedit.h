#ifndef QLUAEDIT_H
#define QLUAEDIT_H

#include <QTextEdit>
#include "luahighlighter.h"

class QLuaEdit : public QTextEdit
{
Q_OBJECT
public:
    explicit QLuaEdit(QWidget *parent = 0);

    void addKeyWord(const QString& key);

signals:

public slots:

private:
    LuaHighlighter *highlighter;
};

#endif // QLUAEDIT_H
