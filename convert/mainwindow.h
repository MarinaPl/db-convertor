#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <database.h>
#include <QtSql>

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


private slots:

   // void toSQL ();
   // void toCSV ();
    void browse ();
    void exit ();

};

#endif // MAINWINDOW_H
