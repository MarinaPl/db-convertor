#include "data_base.h"


Data_Base::Data_Base(QObject *parent): QAbstractTableModel(parent)
{

}

QVariant Data_Base::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (!index.isValid())
            return QVariant();

        return table_data.at(index.row()).at(index.column());
    }

    return QVariant();

}

int Data_Base::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return rows;
}

int Data_Base::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    if (rows == 0)
        return 0;
    return cols;
}

QVariant Data_Base::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            return header_data[section];
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

void Data_Base::clean_data()
{
    table_data.clear();
    header_data.clear();
    type_data.clear();
    cols=0; rows=0;
}
QString check_elem(QString elem){
    elem.replace("\"","\"\""); // по документации если внутри есть кавычка то -> ""
    if (elem.contains('"'))    //если есть символы ; / \ << (это тоже кавычка) , /n то оборачиваем весь элемент в одинарные кавычки
        return "\""+elem+"\"";
    if (elem.contains(';'))
        return "\""+elem+"\"";
    if(elem.contains('/'))
        return "\""+elem+"\"";
    if(elem.contains("<<"))
        return "\""+elem+"\"";
    if(elem.contains("\n"))
        return "\""+elem+"\"";
    if(elem.contains(", "))
        return "\""+elem+"\"";
    return elem;
}
void Data_Base::write_csv(QString path_output)
{
    if(table_data.empty())
    {qDebug()<<"No data ";}
    QFile file(path_output);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream text_stream(&file);  //запись в файл -- переопределяем поток вывода
        QStringList str;
        for(int k=0;k<cols;k++){
            str<<check_elem(header_data [k]);
        }
        text_stream<<str.join(';')+"\n";
        for (int i=0;i<rows;i++)
        {
            str.clear();
            for (int j =0;j<cols;j++){
                str<<check_elem(table_data[i][j]);
            }
            text_stream<<str.join(';')+"\n";
        }

        file.close();
    }
    else qDebug()<<"error open file to write";
}

// проверка на кавычки и их удаление 1й и последний символ, если кавычки внутри заменить на одинарные
//для каждого элемента

QString check_34(QString item){
    if((!item.isEmpty())&&(item[0] == QChar(34)))
        item.remove(0,1);
    if((!item.isEmpty())&&(!item.isNull())&(item[item.count()-1] == QChar(34)))
        item.remove(item.count()-1,1);
    if(!item.isEmpty())
        item = item.replace("\"\"","\"");
    return item;
}

void Data_Base::read_csv(QString path_input)
{
    emit beginResetModel(); //говорит модели о том, что будем менять данные
    clean_data();
    QFile file(path_input);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"error from open file"<<endl;;
        return;
    }

    QTextStream in(&file);     //поток чтения
    bool Quote = false;    //кавычка - проверка
    QList<QString> ItemList;
    QVector<QString> ItemVector;   //объвили вектор
    QString item = "";         //пустая строка

    //читаем заголовки
    QString line(in.readLine().simplified()); // без лишних пробелов
    int count = line.count();  //символы в строке - колво, в цикле посимвольно идем
    for (int i = 0;i<count;i++){
        if (line[i] == QChar(34)){             // если кавычка
            Quote = (Quote) ? false : true;    //меняем флаг если й=правда тогда й=ложь если й=ложь то й=правда
        }
        if ((Quote != true)&(line[i] == ";")){
            header_data.append(check_34(item));  //функция выше с кавычками
            cols++;
            item = "";
        }
        else
        {
            item += line[i];
        }
        if ((count-1 == i)&(Quote != true)){
            item = check_34(item);
            if (item != ""){
                header_data.append(item);
                cols++;}
            item = "";
        }
    }

    {
        while(!in.atEnd()){
            QString line(in.readLine().simplified());
            int count = line.count();
            rows++;
            for (int i = 0;i<count;i++){
                if (line[i] == QChar(34)){
                    Quote = (Quote) ? false : true;
                }
                if ((Quote != true)&(line[i] == ";")){
                    ItemVector.append(check_34(item));
                    item = "";
                }
                else
                {
                    item += line[i];
                }

                if ((count-1 == i)&(Quote != true)){
                    item = check_34(item);
                    if (item != "")
                        ItemVector.append(item);
                    table_data.append(ItemVector);
                    ItemVector.clear();
                    item = "";
                }
            }

        }
    }
    file.close();
    emit endResetModel();

}

//аналогичные функции чтения и записи для sql
/*
void check_type()
{

    QVariant::typeToName( elem.type());

   //но elem должен быть Qvariant

}
*/


void Data_Base::read_sql(QString path_input)
{
    emit beginResetModel(); //говорит модели о том, что будем менять данные
    clean_data();

    QFile file(path_input);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"Sorry, error from open file";
        return;
    }

    QSqlDatabase cur_db = QSqlDatabase::addDatabase("QSQLITE", "cur_db");
    cur_db.setDatabaseName(path_input);

    if (!cur_db.open())
    {
        qDebug() << "Sorry, error from open database";
        return;
    }

    //читаем заголовки и потом остальные данные
    QStringList tab_names = cur_db.tables(); //все таблицы нашей бд. тк по условию таблица одна, то рассматриваем только 1 элемент
    QString  tab_name = tab_names[0];
    //qDebug()<< tab_name;
    QSqlRecord rec = cur_db.record(tab_name); //запись бд

    //по столбцам записали заголовки
    cols = rec.count();
    qDebug()<< cols;

    for(int i = 0; i < cols; i++)
    {
           header_data.append(rec.fieldName(i));
        //   qDebug()<< header_data [i];
        //qDebug() << rec.fieldName(i);
    }
    //записываем остальные данные и считаем строки
    rows = 1;   //тк заголовки точно есть

    QSqlQuery query; //запрос и навигация по бд
    query.exec("SELECT * FROM " + tab_name); //вот тут становится плохо

  /*
    while (query.next())
    {
        QVector<QString> cur_raw;   //пустая "строка" таб. для прочтения след "строки"
        for(int i = 0; i < cols; i++)
        {
            cur_raw.append(rec.fieldName(i));
        }

        table_data.append(cur_raw);
        qDebug() << cur_raw;
        rows++;
    }

    */
    cur_db.close();
    emit endResetModel();
}





