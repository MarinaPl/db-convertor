#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
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
    ui->tableView->setModel(&table1);
      ui->tableView->resizeColumnsToContents();
      ui->tableView->resizeRowsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    QApplication::quit();
}

void MainWindow::browse_csv()
 {
    QString filename=QFileDialog::getOpenFileName(this, tr("Open File"),"","");

        if(!filename.isEmpty())
        {
            QFile file(filename);
            if (!file.open(QIODevice::ReadOnly))
            {
                QMessageBox::critical(this,tr("Error"),tr("Could not open file"));
                return;
            }
            file.close();
        }

        file_name_imp=filename;

        if(file_name_imp!=""){

                    table1.read_csv(filename);
                }
                else  QMessageBox::critical(this,tr("Error"),tr("Not a file name to open"));

        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
}

void MainWindow::browse_sql()
 {
}

void MainWindow :: toSQL()
{

    //    table_name_from=  ui->sql_tab_name->text();
        //       if(table_name_from==""){QMessageBox::critical(this,tr("Error"),tr("Not a table name")); break;}
}

void MainWindow :: toCSV()
{
    QString filename=
               QFileDialog::getSaveFileName(this,
                                            "Save",
                                            QDir::currentPath(),
                                            "Fiels ( *.csv *.*);;All files (*.*)");
       if (filename!=""){

               if(!filename.contains(".csv"))

                   filename+=".csv";

           file_name_exp=filename;

                  table1.write_csv(file_name_exp);


}
}
