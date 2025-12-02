#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    enum Language {
        None,
        Cpp,
        Python,
        JavaScript,
        Html,
        Css,
        Xml
    };

    SyntaxHighlighter(QTextDocument *parent = nullptr);
    void setLanguage(Language language);
    Language currentLanguage() const { return m_currentLanguage; }

protected:
    void highlightBlock(const QString &text) override;

private:
    void initializeFormats();
    void setupCppRules();
    void setupPythonRules();
    void setupJavaScriptRules();
    void setupHtmlRules();
    void setupCssRules();
    void setupXmlRules();

    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;
    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat tagFormat;
    QTextCharFormat attributeFormat;

    Language m_currentLanguage;
};

#endif // SYNTAXHIGHLIGHTER_H
