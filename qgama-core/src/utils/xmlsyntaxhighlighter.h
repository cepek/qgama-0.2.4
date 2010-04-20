#ifndef QGAMACORE__XMLSYNTAXHIGHLIGHTER_H
#define QGAMACORE__XMLSYNTAXHIGHLIGHTER_H

#include <QtGui/QSyntaxHighlighter>

class XmlSyntaxHighlighter : public QSyntaxHighlighter
{
    public:
        XmlSyntaxHighlighter(QTextDocument *parent = 0);
        void setDocument(QTextDocument *doc);

    protected:
        virtual void highlightBlock(const QString &text);

    private:
        struct HighlightingRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };
        QVector<HighlightingRule> highlightingRules;

        QRegExp commentStartExpression;
        QRegExp commentEndExpression;

        QTextCharFormat tagFormat;
        QTextCharFormat attributeFormat;
        QTextCharFormat attributeContentFormat;
        QTextCharFormat commentFormat;
};

#endif // QGAMACORE__XMLSYNTAXHIGHLIGHTER_H
