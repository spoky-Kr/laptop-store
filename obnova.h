/*Форма obnova.

  Форма для изменения записи в выбранной таблицы,
  в соответствии с ID записи.

  Переменные, используемые в форме:
    db - ссылка на базу данных;
    magazini - контейнер, хранящий пары (ключ, значение), названия столбцов таблицы "Магазины"
    на русском и их соотвественные названия из БД;
    tovari - контейнер, хранящий пары (ключ, значение), названия столбцов таблицы "Товары"
    на русском и их соотвественные названия из БД;
    zakazi - контейнер, хранящий пары (ключ, значение), названия столбцов таблицы "Заказы"
    на русском и их соотвественные названия из БД;
    dostavka - контейнер, хранящий пары (ключ, значение), названия столбцов таблицы "Доставки"
    на русском и их соотвественные названия из БД.

  Функции, используемые в форме:
    void on_pushObMagaz_clicked() - функция изменения записи в таблице "Магазины",
    в соответствии с ID записи;
    void on_pushObTovar_clicked() - функция изменения записи в таблице "Товары",
    в соответствии с ID записи;;
    void on_pushObZakaz_clicked() - функция изменения записи в таблице "Заказы",
    в соответствии с ID записи;;
    void on_pushObDost_clicked() - функция изменения записи в таблице "Доставки",
    в соответствии с ID записи;;

*/
#ifndef OBNOVA_H
#define OBNOVA_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMap>

namespace Ui {
class obnova;
}

class obnova : public QDialog
{
    Q_OBJECT

public:
    /*Конструктор класса obnova*/
    explicit obnova(QWidget *parent = nullptr);
    /*Деструктор класса obnova*/
    ~obnova();
    QSqlDatabase db;

private slots:
    void on_pushObMagaz_clicked();

    void on_pushObTovar_clicked();

    void on_pushObZakaz_clicked();

    void on_pushObDost_clicked();

private:
    Ui::obnova *ui;
    std::map<QString, QString> magazini = {{"ID магазина", "ID_magaz"},{"Email", "Email"}, {"Оплата доставки", "opl_dostavka"}};
    std::map<QString, QString> tovari = {{"ID товара", "ID_tovar"},{"Название", "nazvanie"}, {"Фирма", "firma"},{"Модель","modell"},{"Тех. хар-ки","tx"},{"Цена","cost"},{"Гар. срок","gar_srok"}};
    std::map<QString, QString> zakazi= {{"ID заказа", "ID_zakaz"},{"ID магазина", "ID_magaz"}, {"ID товара", "ID_tovar"},{"Дата заказа","data_zakaza"},{"ФИО клиента","FIO_klienta"},{"Тел. клиента","tel"},{"Время заказа","time_zak"}};
    std::map<QString, QString> dostavka = {{"ID доставки", "ID_dostavki"}, {"ID заказа", "ID_zakaz"}, {"Дата доставки", "data_dostavki"}, {"Время доставки", "time_dost"}, {"Адрес доставки", "adress"}, {"ФИО курьера", "FIO_kur"}};
};

#endif // OBNOVA_H
