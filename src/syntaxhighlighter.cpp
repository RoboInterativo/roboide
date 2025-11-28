#include "syntaxhighlighter.h"
#include <QTextDocument>

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
    , m_currentLanguage(None)
{
    initializeFormats();
    setLanguage(Cpp); // По умолчанию C++
}

void SyntaxHighlighter::initializeFormats()
{
    // Базовые форматы
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    classFormat.setForeground(Qt::darkMagenta);
    classFormat.setFontWeight(QFont::Bold);

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    multiLineCommentFormat.setForeground(Qt::darkGreen);

    quotationFormat.setForeground(Qt::darkRed);

    functionFormat.setForeground(Qt::blue);

    numberFormat.setForeground(Qt::darkCyan);

    tagFormat.setForeground(Qt::darkBlue);
    tagFormat.setFontWeight(QFont::Bold);

    attributeFormat.setForeground(Qt::darkRed);
}

void SyntaxHighlighter::setLanguage(Language language)
{
    highlightingRules.clear();
    m_currentLanguage = language;

    switch (language) {
    case Cpp:
        setupCppRules();
        break;
    case Python:
        setupPythonRules();
        break;
    case JavaScript:
        setupJavaScriptRules();
        break;
    case Html:
        setupHtmlRules();
        break;
    case Css:
        setupCssRules();
        break;
    case Xml:
        setupXmlRules();
        break;
    case None:
        // Без подсветки
        break;
    }

    rehighlight();
}




void SyntaxHighlighter::setupCppRules()
{
    // Существующие правила C++...
    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b"
                    << "\\bif\\b" << "\\belse\\b" << "\\bfor\\b" << "\\bwhile\\b"
                    << "\\breturn\\b" << "\\bbreak\\b" << "\\bcontinue\\b"
                    << "\\bswitch\\b" << "\\bcase\\b" << "\\bdefault\\b";

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Qt классы
    HighlightingRule classRule;
    classRule.pattern = QRegularExpression("\\bQ[A-Za-z]+\\b");
    classRule.format = classFormat;
    highlightingRules.append(classRule);

    // Функции
    HighlightingRule functionRule;
    functionRule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    functionRule.format = functionFormat;  // ← ИСПРАВИТЬ: было rule.format
    highlightingRules.append(functionRule);



    // Числа
    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b[0-9]+(\\.[0-9]+)?\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);

    // Строки
    HighlightingRule quotationRule;
    quotationRule.pattern = QRegularExpression("\".*\"");
    quotationRule.format = quotationFormat;
    highlightingRules.append(quotationRule);

    // Однострочные комментарии
    HighlightingRule singleLineCommentRule;
    singleLineCommentRule.pattern = QRegularExpression("//[^\n]*");
    singleLineCommentRule.format = singleLineCommentFormat;
    highlightingRules.append(singleLineCommentRule);

    // Многострочные комментарии
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void SyntaxHighlighter::setupPythonRules()
{
    // Ключевые слова Python
    QStringList keywordPatterns;
    keywordPatterns << "\\bFalse\\b" << "\\bNone\\b" << "\\bTrue\\b"
                   << "\\band\\b" << "\\bas\\b" << "\\bassert\\b"
                   << "\\bbreak\\b" << "\\bclass\\b" << "\\bcontinue\\b"
                   << "\\bdef\\b" << "\\bdel\\b" << "\\belif\\b"
                   << "\\belse\\b" << "\\bexcept\\b" << "\\bfinally\\b"
                   << "\\bfor\\b" << "\\bfrom\\b" << "\\bglobal\\b"
                   << "\\bif\\b" << "\\bimport\\b" << "\\bin\\b"
                   << "\\bis\\b" << "\\blambda\\b" << "\\bnonlocal\\b"
                   << "\\bnot\\b" << "\\bor\\b" << "\\bpass\\b"
                   << "\\braise\\b" << "\\breturn\\b" << "\\btry\\b"
                   << "\\bwhile\\b" << "\\bwith\\b" << "\\byield\\b";

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Декораторы
    HighlightingRule decoratorRule;
    decoratorRule.pattern = QRegularExpression("@\\w+");
    decoratorRule.format = classFormat;
    highlightingRules.append(decoratorRule);

    // УПРОЩЕННЫЕ строки Python - убираем проблемные многострочные шаблоны
    HighlightingRule stringRule;

    // Обычные строки в двойных кавычках
    stringRule.pattern = QRegularExpression("\"[^\"]*\"");
    stringRule.format = quotationFormat;
    highlightingRules.append(stringRule);

    // Обычные строки в одинарных кавычках
    stringRule.pattern = QRegularExpression("'[^']*'");
    stringRule.format = quotationFormat;
    highlightingRules.append(stringRule);

    // Комментарии Python
    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("#[^\n]*");
    commentRule.format = singleLineCommentFormat;
    highlightingRules.append(commentRule);

    // Числа
    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b[0-9]+(\\.[0-9]+)?\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);

    // В Python нет многострочных комментариев /* */
    commentStartExpression = QRegularExpression();
    commentEndExpression = QRegularExpression();
}

void SyntaxHighlighter::setupJavaScriptRules()
{
    // Ключевые слова JavaScript
    QStringList keywordPatterns;
    keywordPatterns << "\\bfunction\\b" << "\\bvar\\b" << "\\blet\\b"
                   << "\\bconst\\b" << "\\bif\\b" << "\\belse\\b"
                   << "\\bfor\\b" << "\\bwhile\\b" << "\\breturn\\b"
                   << "\\bbreak\\b" << "\\bcontinue\\b" << "\\bswitch\\b"
                   << "\\bcase\\b" << "\\bdefault\\b" << "\\btry\\b"
                   << "\\bcatch\\b" << "\\bfinally\\b" << "\\bthrow\\b"
                   << "\\bnew\\b" << "\\bdelete\\b" << "\\btypeof\\b"
                   << "\\binstanceof\\b" << "\\bvoid\\b" << "\\bthis\\b"
                   << "\\btrue\\b" << "\\bfalse\\b" << "\\bnull\\b"
                   << "\\bundefined\\b";

    for (const QString &pattern : keywordPatterns) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // Функции
    HighlightingRule functionRule;
    functionRule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    functionRule.format = functionFormat;
    highlightingRules.append(functionRule);

    // Строки
    HighlightingRule stringRule;
    stringRule.pattern = QRegularExpression("\".*?\"");
    stringRule.format = quotationFormat;
    highlightingRules.append(stringRule);

    stringRule.pattern = QRegularExpression("'.*?'");
    highlightingRules.append(stringRule);

    stringRule.pattern = QRegularExpression("`.*?`");
    highlightingRules.append(stringRule);

    // Комментарии
    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("//[^\n]*");
    commentRule.format = singleLineCommentFormat;
    highlightingRules.append(commentRule);

    // Многострочные комментарии
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");

    // Числа
    HighlightingRule numberRule;
    numberRule.pattern = QRegularExpression("\\b[0-9]+(\\.[0-9]+)?\\b");
    numberRule.format = numberFormat;
    highlightingRules.append(numberRule);
}

void SyntaxHighlighter::setupHtmlRules()
{
    // HTML теги
    HighlightingRule tagRule;
    tagRule.pattern = QRegularExpression("<[^>]*>");
    tagRule.format = tagFormat;
    highlightingRules.append(tagRule);

    // Атрибуты
    HighlightingRule attributeRule;
    attributeRule.pattern = QRegularExpression("\\b\\w+\\s*=");
    attributeRule.format = attributeFormat;
    highlightingRules.append(attributeRule);

    // Комментарии HTML
    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("<!--.*-->");
    commentRule.format = singleLineCommentFormat;
    highlightingRules.append(commentRule);

    // Многострочные комментарии HTML
    commentStartExpression = QRegularExpression("<!--");
    commentEndExpression = QRegularExpression("-->");
}

void SyntaxHighlighter::setupCssRules()
{
    // CSS свойства
    QStringList cssProperties;
    cssProperties << "\\bcolor\\b" << "\\bbackground\\b" << "\\bmargin\\b"
                  << "\\bpadding\\b" << "\\bwidth\\b" << "\\bheight\\b"
                  << "\\bfont\\b" << "\\bdisplay\\b" << "\\bposition\\b"
                  << "\\bborder\\b" << "\\btext\\b" << "\\balign\\b";

    for (const QString &pattern : cssProperties) {
        HighlightingRule rule;
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    // CSS значения
    HighlightingRule valueRule;
    valueRule.pattern = QRegularExpression("#[0-9a-fA-F]+");
    valueRule.format = numberFormat;
    highlightingRules.append(valueRule);

    // Комментарии CSS
    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("/\\*[^*]*\\*+(?:[^/*][^*]*\\*+)*/");
    commentRule.format = singleLineCommentFormat;
    highlightingRules.append(commentRule);
}

void SyntaxHighlighter::setupXmlRules()
{
    // XML теги
    HighlightingRule tagRule;
    tagRule.pattern = QRegularExpression("<[^>]*>");
    tagRule.format = tagFormat;
    highlightingRules.append(tagRule);

    // Атрибуты
    HighlightingRule attributeRule;
    attributeRule.pattern = QRegularExpression("\\b\\w+\\s*=");
    attributeRule.format = attributeFormat;
    highlightingRules.append(attributeRule);

    // Комментарии XML
    HighlightingRule commentRule;
    commentRule.pattern = QRegularExpression("<!--.*-->");
    commentRule.format = singleLineCommentFormat;
    highlightingRules.append(commentRule);

    // Многострочные комментарии XML
    commentStartExpression = QRegularExpression("<!--");
    commentEndExpression = QRegularExpression("-->");
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    // Применяем правила подсветки
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // Обрабатываем многострочные комментарии только если они определены
    if (commentStartExpression.isValid() && commentEndExpression.isValid()) {
        setCurrentBlockState(0);
        int startIndex = 0;
        if (previousBlockState() != 1) {
            startIndex = text.indexOf(commentStartExpression);
        }

        // Защита от бесконечного цикла
        int safetyCounter = 0;
        const int MAX_ITERATIONS = 100;

        while (startIndex >= 0 && safetyCounter < MAX_ITERATIONS) {
            QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
            int endIndex = match.capturedStart();
            int commentLength = 0;

            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex + match.capturedLength();
            }

            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
            safetyCounter++;
        }
    }
}
