#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QString>
#include "syntaxhighlighter.h"  // ← ДОБАВИТЬ

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveAs();
    void about();

private:
    void setupUI();
    void setupMenu();
    void setupStatusBar();
    bool maybeSave();
    void setCurrentFile(const QString &fileName);

    QPlainTextEdit *textEdit;
    SyntaxHighlighter *highlighter;  // ← ДОБАВИТЬ
    QString currentFile;
};

#endif // MAINWINDOW_H
