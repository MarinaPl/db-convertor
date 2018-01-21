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
    QString table_name ; ///имя таблицы sql

public: Data_Base table1;

private slots:
    ///
    /// \brief toSQL Функция, которая записывает данные в файл базы данных
    ///
    void toSQL ();
    ///
    /// \brief toCSV Функция, которая записывает данные таблицы в файл .csv
    ///
    void toCSV ();
    ///
    /// \brief browse_csv Выбор и чтение файла .csv, отображение его в TableWiewer
    ///
    void browse_csv ();
    ///
    /// \brief browse_sql Выбор и чтение файла базы данных, отображение его в TableWiewer
    ///
    void browse_sql ();
    ///
    /// \brief exit Выход из приложения
    ///
    void exit ();

};

#endif // MAINWINDOW_H
