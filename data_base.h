#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <QObject>
#include <QAbstractTableModel>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <QStandardItemModel>
#include <QTextStream>
#include <QItemSelectionModel>
#include <QVector>
#include <QString>
#include <QtSql>
#include <QSqlRecord>


class Data_Base: public QAbstractTableModel
{
    Q_OBJECT

public:

    Data_Base(QObject *parent= nullptr);
    QVector<QString> header_data;
    QVector<QVector<QString>> table_data;
    QString tab_name ; ///имя таблицы sql
    QVector<QString> type_data;
    int rows=0,cols=0;
    ///
    /// \brief read_csv Функция, которая читает данные из файла
    /// \param path_input Параметр на входе: путь к исходному файлу
    ///
    void read_csv(QString path_input);
    ///
    /// \brief write_csv Функция, которая записывает данные в файл
    /// \param path_output Параметр на входе: путь к результирующему файлу
    ///
    void write_csv(QString path_output);
    ///
    /// \brief read_sql Функция, которая читает данные из файла
    /// \param path_input Параметр на входе: путь к исходному файлу
    ///
    void read_sql(QString path_input);
    ///




    ///
    /// \brief clean_data Функция для очистки данных - чтобы можно было использовать приложение несколько раз
    ///
    void clean_data();
    ///
    /// \brief rowCount Число строк
    ///
    virtual int rowCount(const QModelIndex &parent) const override;
    ///
    /// \brief columnCount Число столбцов
    ///
    virtual int columnCount(const QModelIndex &parent) const override;
    ///
    /// \brief data Данные таблицы
    ///
    virtual QVariant data(const QModelIndex &index, int role) const override;
    ///
    /// \brief headerData Имена столбцов
    ///
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;


};

#endif // DATA_BASE_H
