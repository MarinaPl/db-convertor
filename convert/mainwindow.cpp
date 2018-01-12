#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>
#include <QTextStream>
#include <QItemSelectionModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


connect(ui->exit_butt, SIGNAL(clicked()), this, SLOT(exit()));
connect(ui->brows_butt, SIGNAL(clicked()), this, SLOT(browse()));


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::exit()
{
    QApplication::quit();
}


void MainWindow::browse()
 {
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"","*.csv *.sqlite");
    //поработать над отображением таблицы

    if(!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Sorry, Could not open "));
            return;
        }
        file.close();
    }
    file_name_imp=filename; //путь выбранного файла
    ui->statusBar->showMessage(file_name_imp, 5000);

}

