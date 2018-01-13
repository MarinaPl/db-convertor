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
connect(ui->brows_butt, SIGNAL(clicked()), this, SLOT(browse_csv()));
connect(ui->brows_butt_2, SIGNAL(clicked()), this, SLOT(browse_sql()));
connect(ui->toSQL_butt, SIGNAL(clicked()), this, SLOT(toSQL()));
connect(ui->tocsv_butt, SIGNAL(clicked()), this, SLOT(toCSV()));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::exit()
{
    QApplication::quit();
}

//открываем файл csv
void MainWindow::browse_csv()
 {
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"","*.csv");

    if(!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QFile::ReadOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Sorry, Could not open "));
            return;
        }
        file.close();
    }

    file_name_imp=filename; //путь выбранного файла
    ui->statusBar->showMessage(file_name_imp, 5000);

    //отображение таблицы
    QFile file(file_name_imp);
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    int i,j;
    i=-1; j=0;

    if ( !file.open(QFile::ReadOnly | QFile::Text) )
    {
        QMessageBox::critical(this,tr("Error"),tr("Sorry, Could not open "));
        return;
    }
  else{
  QStringList::const_iterator it;
  QTextStream in(&file);
  // Считываем данные до конца файла по строкам
  int flag = 0;
  while (!in.atEnd())
  {
  QString line = in.readLine();

     for (QString record : line.split(";"))
     {
        if (flag == 0)
        {
         horizontalHeader.append(record);
         model->setHorizontalHeaderLabels(horizontalHeader);
         qDebug()<<record; //записываем данные в ячейку таблицы
         }
        else{
            item = new QStandardItem(record);
             model->setItem(i, j, item);
             j++;
            }
     }
     j=0;
     i++;
     flag++;

   file.close();
   ui->tableView->setModel(model);
   ui->tableView->resizeRowsToContents();
   ui->tableView->resizeColumnsToContents();
   }}
}

//открываем файл sql
void MainWindow::browse_sql()
 {
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"","*.sqlite *db");
    //поработать над отображением таблицы

    if(!filename.isEmpty())
    {
        QFile file(filename);
        if (!file.open(QFile::ReadOnly))
        {
            QMessageBox::critical(this,tr("Error"),tr("Sorry, Could not open "));
            return;
        }
        file.close();
    }
    file_name_imp=filename; //путь выбранного файла
    ui->statusBar->showMessage(file_name_imp, 5000);
    //отображение


}

//сохранение в файл csv или sql происходит после нажатия соответствующей кнопнки
void MainWindow :: toSQL()
{
    //вызов функции из csvsql
    ui->statusBar->showMessage("Success!", 5000);

}

void MainWindow :: toCSV()
{

    //вызов функции из sqlcsv
  ui->statusBar->showMessage("Success!", 5000);
}

