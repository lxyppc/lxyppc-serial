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
    QString toTagText() const;
    void setTag(const QString& name, const QString& start, const QString& end);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent * event);
private:
    LuaHighlighter *highlighter;
    std::map<QString, QString>  startMap;
    std::map<QString, QString>  endMap;
};

#endif // QLUAEDIT_H
