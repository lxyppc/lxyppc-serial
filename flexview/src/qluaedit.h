#ifndef QLUAEDIT_H
#define QLUAEDIT_H

#include <QPlainTextEdit>
#include "luahighlighter.h"

class QLuaEdit : public QPlainTextEdit
{
Q_OBJECT
public:
    explicit QLuaEdit(QWidget *parent = 0);

    void addKeyWord(const QString& key);
    QString toTagText() const;
    void setTag(const QString& name, const QString& start, const QString& end);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

protected:
    void resizeEvent(QResizeEvent *event);
signals:

public slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
protected:
    void keyPressEvent(QKeyEvent * event);
private:
    LuaHighlighter *highlighter;
    std::map<QString, QString>  startMap;
    std::map<QString, QString>  endMap;
    QWidget *lineNumberArea;
};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(QLuaEdit *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    QLuaEdit *codeEditor;
};
#endif // QLUAEDIT_H
