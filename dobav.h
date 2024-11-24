/*Форма dobav.

  Данная форма позволяет добавить запись в выбранную таблицу.

  Переменная, используемые в форме:
    db - ссылка на базу данных.

  Функции, используемые в форме:
    void on_pushMagazDob_clicked() - функция добавления записи в таблицу "Магазины";
    void on_pushTovarDob_clicked() - функция добавления записи в таблицу "Товары";
    void on_pushZakazDob_clicked() - функция добавления записи в таблицу "Заказы";
    void on_pushDostDob_clicked() - функция добавления записи в таблицу "Доставки".


*/

#ifndef DOBAV_H
#define DOBAV_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class dobav;
}

class dobav : public QDialog
{
    Q_OBJECT

public:
    /*Конструктор класса dobav*/
    explicit dobav(QWidget *parent = nullptr);
    /*Деструктор класса dobav*/
    ~dobav();
    QSqlDatabase db;

private slots:
    void on_pushMagazDob_clicked();

    void on_pushTovarDob_clicked();

    void on_pushZakazDob_clicked();

    void on_pushDostDob_clicked();

private:
    Ui::dobav *ui;
};

#endif // DOBAV_H
