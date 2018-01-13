#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <data_base.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QString file_name_imp; ///путь к файлу импорта
       QString file_name_exp; ///путь к файлу экспорта
       QString table_name; ///имя таблицы sql
   public: Data_Base table1;

   private slots:
   ///
   /// \brief toSQL
   ///
       void toSQL ();
       void toCSV ();
       void browse_csv ();
       void browse_sql ();
       void exit ();

};

#endif // MAINWINDOW_H
