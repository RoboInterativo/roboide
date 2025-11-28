#include "mainwindow.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , textEdit(new QPlainTextEdit(this))
    , highlighter(new SyntaxHighlighter(textEdit->document()))  // ← ДОБАВИТЬ
    , currentFile("")
{
    setupUI();
    setupMenu();
    setupStatusBar();
}

void MainWindow::setupUI()
{
    setCentralWidget(textEdit);
    textEdit->setFont(QFont("Monospace", 11));
    setWindowTitle("MyCodeEditor - Untitled");
    resize(1000, 700);
}

void MainWindow::setupMenu()
{
    // Меню File
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction("&New", this, &MainWindow::newFile, QKeySequence::New);
    fileMenu->addAction("&Open...", this, &MainWindow::openFile, QKeySequence::Open);
    fileMenu->addAction("&Save", this, &MainWindow::saveFile, QKeySequence::Save);
    fileMenu->addAction("Save &As...", this, &MainWindow::saveAs, QKeySequence::SaveAs);
    fileMenu->addSeparator();
    fileMenu->addAction("E&xit", this, &QWidget::close, QKeySequence::Quit);

    // В mainwindow.cpp в setupMenu()
    QMenu *viewMenu = menuBar()->addMenu("&View");
    QMenu *languageMenu = viewMenu->addMenu("&Syntax");

    languageMenu->addAction("C++", [this]() { highlighter->setLanguage(SyntaxHighlighter::Cpp); });
    languageMenu->addAction("Python", [this]() { highlighter->setLanguage(SyntaxHighlighter::Python); });
    languageMenu->addAction("JavaScript", [this]() { highlighter->setLanguage(SyntaxHighlighter::JavaScript); });
    languageMenu->addAction("None", [this]() { highlighter->setLanguage(SyntaxHighlighter::None); });

    // Меню Help
    QMenu *helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction("&About", this, &MainWindow::about);
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage("Ready");
}

void MainWindow::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
        statusBar()->showMessage("New file created");
    }
}

void MainWindow::openFile()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this, "Open File");
        if (!fileName.isEmpty()) {
            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                textEdit->setPlainText(file.readAll());
                setCurrentFile(fileName);
                statusBar()->showMessage("Opened: " + fileName);
            } else {
                QMessageBox::warning(this, "Error", "Cannot open file: " + fileName);
            }
        }
    }
}

void MainWindow::saveFile()
{
    if (currentFile.isEmpty()) {
        saveAs();
    } else {
        QFile file(currentFile);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream stream(&file);
            stream << textEdit->toPlainText();
            statusBar()->showMessage("Saved: " + currentFile);
        } else {
            QMessageBox::warning(this, "Error", "Cannot save file: " + currentFile);
        }
    }
}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File");
    if (!fileName.isEmpty()) {
        setCurrentFile(fileName);
        saveFile();
    }
}

bool MainWindow::maybeSave()
{
    if (!textEdit->document()->isModified()) {
        return true;
    }

    QMessageBox::StandardButton ret = QMessageBox::warning(this, "MyCodeEditor",
        "The document has been modified.\nDo you want to save your changes?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (ret == QMessageBox::Save) {
        saveFile();
        return true;
    } else if (ret == QMessageBox::Cancel) {
        return false;
    }

    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    textEdit->document()->setModified(false);

    // Автоматическое определение языка по расширению
    QFileInfo fileInfo(fileName);
    QString ext = fileInfo.suffix().toLower();

    // if (highlighter) {
    //     if (ext == "cpp" || ext == "h" || ext == "hpp" || ext == "c" || ext == "cc") {
    //         highlighter->setLanguage(SyntaxHighlighter::Cpp);
    //     } else if (ext == "py") {
    //         highlighter->setLanguage(SyntaxHighlighter::Python);
    //     } else if (ext == "js") {
    //         highlighter->setLanguage(SyntaxHighlighter::JavaScript);
    //     } else if (ext == "html" || ext == "htm") {
    //         highlighter->setLanguage(SyntaxHighlighter::Html);
    //     } else if (ext == "css") {
    //         highlighter->setLanguage(SyntaxHighlighter::Css);
    //     } else if (ext == "xml") {
    //         highlighter->setLanguage(SyntaxHighlighter::Xml);
    //     } else {
    //         highlighter->setLanguage(SyntaxHighlighter::None);
    //     }
    // }

    QString shownName = "Untitled";
    if (!currentFile.isEmpty()) {
        shownName = QFileInfo(currentFile).fileName();
    }

    setWindowTitle(shownName + "[*] - MyCodeEditor");
    setWindowModified(false);
}

void MainWindow::about()
{
    QMessageBox::about(this, "About MyCodeEditor",
        "<h3>MyCodeEditor</h3>"
        "A simple code editor built with Qt5<br>"
        "Version 1.0<br><br>"
        "Compatible with Ubuntu 20.04, 22.04, 24.04");
}
