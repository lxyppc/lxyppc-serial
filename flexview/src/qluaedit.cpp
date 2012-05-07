#include "qluaedit.h"
#include <QtGui>

QLuaEdit::QLuaEdit(QWidget *parent) :
    QPlainTextEdit(parent)
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);
    setFont(font);
    highlighter = new LuaHighlighter(document());
    setLineWrapMode(QPlainTextEdit::NoWrap);

    lineNumberArea = new LineNumberArea(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
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
        QPlainTextEdit::keyPressEvent(event);
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

int QLuaEdit::lineNumberAreaWidth()
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

    return space;
}

void QLuaEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void QLuaEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void QLuaEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}



void QLuaEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}



void QLuaEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);


    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}
