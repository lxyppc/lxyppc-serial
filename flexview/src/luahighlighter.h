#ifndef LUAHIGHLIGHTER_H
#define LUAHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#define LONG_QUOTA_LEVEL 10

class LuaHighlighter : public QSyntaxHighlighter
{
Q_OBJECT
public:
    explicit LuaHighlighter(QTextDocument *parent = 0);

    void addUserKeyword(const QString& keyword);

protected:
    void highlightBlock(const QString &text);

private:
    enum BlockState{
        BS_Dummy,
        BS_BlockComment,
        BS_DoubleQuota,
        BS_SingleQuota,
        BS_LongQuota,
        BS_LastLongQuata = BS_LongQuota + LONG_QUOTA_LEVEL-1,
        BS_LastState,
    };
    struct HighlightingRule
    {
        HighlightingRule():blockState(BS_Dummy){}
        QRegExp pattern;
        QTextCharFormat format;
        QRegExp endPattern;
        QString name;
        BlockState blockState;
    };
    int matchBlockEnd(const QString &text, int index, const HighlightingRule& rule);
    int matchPatten(const QString &text, int offset, HighlightingRule& rule, int& matchedLength);
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QRegExp quotationStart;
    QRegExp quotationEnd;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat userKeyword;

};

#endif // LUAHIGHLIGHTER_H
