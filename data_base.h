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


class Data_Base: public QAbstractTableModel
{
    Q_OBJECT
public:

    Data_Base(QObject *parent= nullptr);
    QVector<QString> header_data;
    QVector<QVector<QString>> table_data;
    QVector<QString> type_data;
  int rows=0,cols=0;
  void read_csv(QString path_input);
  void write_csv(QString path_output);

  void clean_data();

  virtual int rowCount(const QModelIndex &parent) const override;
  virtual int columnCount(const QModelIndex &parent) const override;
  virtual QVariant data(const QModelIndex &index, int role) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override; //установить имена столбцов в отображении таблицы

};

#endif // DATA_BASE_H
