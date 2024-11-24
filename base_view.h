/*Форма base_view.

 Описание:
    Данная форма позвозволяет обращаться к базе данных с помощью SQL-запросов для просмотра,
    добавления, изменения и удаления данных.
    Посредством кнопок, есть возможность осуществить сортировку выбранной таблицы,
    выбранному параметру, а также выгрузку данных в текстовый файл,
    загрузку данных из файла, и вывод на печать таблиц базы данных.

 Переменные, используемые в форме:
    db - ссылка на базу данных;
    tab - контейнер, хранящий пары (ключ, значение), названия таблиц";
    magazini - контейнер, хранящий пары (ключ, значение), названия столбцов таблицы "Магазины";
    tovari - контейнер, хранящий пары (ключ, значение), названия столбцов таблицы "Товары";
    zakazi - контейнер, хранящий пары (ключ, значение), названия столбцов таблицы "Заказы";
    dostavka - контейнер, хранящий пары (ключ, значение), названия столбцов таблицы "Доставки".

 Функции, используемые в форме:
    void viewTab(QString nameTab) - функция вывода таблицы из базы данных в форму;
    void on_comboBox_activated(int index) - функция, реализующая заполнение выпадающего списка
    названиями столбцов выбранной таблицы;
    void sortTab(QString nameTab,QString field) - функция, реализующая сортировку
    выбранной таблицы;
    void on_sortButton_clicked() - функция сортировки данных выбранной таблицы, по
    по выбранному параметру;
    void on_dobavButton_clicked() - функция перехода на форму добавления;
    void on_udalButton_2_clicked() - функция перехода на форму удаления;
    void on_izmenButton_3_clicked() - функция перехода на форму изменения;
    void on_vigruzka_clicked() - фукция выгрузки данных из таблицы базы данных в файл;
    void on_vivod_clicked() - функция, реализующая отправку файла на печать;
    void on_zagruzka_clicked() - функция загрузки данных из файла в таблицу базы данных.

*/

#ifndef BASE_VIEW_H
#define BASE_VIEW_H

#include <QDialog>
#include <QSqlDatabase>
#include <QString>
#include <QMap>

namespace Ui {
class base_view;
}

class base_view : public QDialog
{
    Q_OBJECT

public:
    /*Конструктор класса base_view*/
    explicit base_view(QWidget *parent = nullptr);
    /*Деструктор класс base_view*/
    ~base_view();
    QSqlDatabase db;
private slots:
    void viewTab(QString nameTab);
    void on_comboBox_activated(int index);
    void sortTab(QString nameTab,QString field);


    void on_sortButton_clicked();

    void on_dobavButton_clicked();

    void on_udalButton_2_clicked();

    void on_izmenButton_3_clicked();

    void on_vigruzka_clicked();

    void on_vivod_clicked();

    void on_zagruzka_clicked();

private:
    Ui::base_view *ui;
    std::map<QString, QString> tab = {{"Магазины", "magazini"}, {"Товары", "tovari"}, {"Заказы", "zakazi"}, {"Доставки", "dostavka"}};
    std::map<QString, QString> magazini = {{"ID магазина", "ID_magaz"},{"Email", "Email"}, {"Оплата доставки", "opl_dostavka"}};
    std::map<QString, QString> tovari = {{"ID товара", "ID_tovar"},{"Название", "nazvanie"}, {"Фирма", "firma"},{"Модель","modell"},{"Тех. хар-ки","tx"},{"Цена","cost"},{"Гар. срок","gar_srok"}};
    std::map<QString, QString> zakazi= {{"ID заказа", "ID_zakaz"},{"ID магазина", "ID_magaz"}, {"ID товара", "ID_tovar"},{"Дата заказа","data_zakaza"},{"ФИО клиента","FIO_klienta"},{"Тел. клиента","tel"},{"Время заказа","time_zak"}};
    std::map<QString, QString> dostavka = {{"ID доставки", "ID_dostavki"}, {"ID заказа", "ID_zakaz"}, {"Дата доставки", "data_dostavki"}, {"Время доставки", "time_dost"}, {"Адрес доставки", "adress"}, {"ФИО курьера", "FIO_kur"}};
};

#endif // BASE_VIEW_H
