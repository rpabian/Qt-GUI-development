#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionnew_triggered()
{
    //clear the screen
    currentFile.clear();
    //create a new text window
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Can NOT open file: " +
                             file.errorString());
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionsave_triggered()
{
    //Open window to save a file
    QString fileName = QFileDialog::getSaveFileName(this, "Save the file");
    //Create object to hold the file
    QFile file(fileName);

    //Open the file notify user if problem
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Can NOT save file: " +
                             file.errorString());
    }

    //Store current file
    currentFile = fileName;
    //Set window title to name of file
    setWindowTitle(fileName);
    //When writing to out we are actually writing to file on line 68 below
    QTextStream out(&file);

    //Copy text in textEdit widget convert to plain text
    QString text = ui->textEdit->toPlainText();

    //Write to File then close file
    out << text;
    file.close();
}

void MainWindow::on_actionexit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();
}
