#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include <QFileInfo>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTreeView>  //уточнить нужно или нет

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


connect(ui->exit_butt, SIGNAL(clicked()), this, SLOT(exit()));

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::exit()
{
    QApplication::quit();
}
