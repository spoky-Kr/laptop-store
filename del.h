/*Форма del.

  Данная форма позволяет удалить запись из выбранной таблицы,
  в соответствии с ID записи.

  Переменные, используемые в форме:
    db - ссылка на базу данных;
    tab - контейнер, хранящий пары (ключ, значение), названий таблиц на русском языке и
    соответствующие названия таблиц из базы данных;
    keys - контейнер, хранящий пары (ключ, значение), названий первичных ключей таблиц
    на русском и соответствующих названий из базы данных.

  Функции, используемые в форме:
    void on_BoxTable_activated(int index) - функция, реализующая выбор из выпадающего списка
    с названиями таблиц;
    void id_Table(QString nameTab, QString id) - функция, реализующая добавление
    ID записей, выбранной таблицы, в выпадающий список;
    void DelTab(QString Name_t, QString field) - функция, реализующая удаление
    выбранной записи из базы данных;
    void on_deleteButton_clicked() - функция, принимающая название таблицы и
    и ID записи с формы, и вызывающая функцию DelTaD().
*/

#ifndef DEL_H
#define DEL_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMap>

namespace Ui {
class Del;
}

class Del : public QDialog
{
    Q_OBJECT

public:
    /*Конструктор класса Del*/
    explicit Del(QWidget *parent = nullptr);
    /*Деструктор класса Del*/
    ~Del();
    QSqlDatabase db;

private slots:
    void on_BoxTable_activated(int index);
    void id_Table(QString nameTab, QString id);
    void DelTab(QString Name_t, QString field);
    void on_deleteButton_clicked();

private:
    Ui::Del *ui;
    std::map<QString, QString> tab = {{"Магазины", "magazini"}, {"Товары", "tovari"}, {"Заказы", "zakazi"}, {"Доставки", "dostavka"}};
    std::map<QString, QString> keys = {{"magazini", "ID_magaz"}, {"tovari", "ID_tovar"}, {"zakazi", "ID_zakaz"}, {"dostavka", "ID_dostavki"}};
};

#endif // DEL_H
