#include "obnova.h"
#include "ui_obnova.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

obnova::obnova(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::obnova)
{
    ui->setupUi(this);
    this->setWindowTitle("Окно изменения записей");       // Изменение заголовка окна
    db=QSqlDatabase::addDatabase("QSQLITE");              // Подключение базы данных
    db.setDatabaseName("base_praktika.db");
    db.open();

    QSqlQuery query1(db);                                 // Заполнение выпадающего списка
    if (query1.exec("SELECT ID_magaz FROM magazini")){    // ID магазинов
       while (query1.next()){
           ui->ObnovaIDmagaz->addItem(query1.value(0).toString());
       }
    }

    QSqlQuery query2(db);                                 // Заполнение выпадающего списка
    if (query2.exec("SELECT ID_tovar FROM tovari")){      // ID товаров
       while (query2.next()){
           ui->ObnovaIDtovar->addItem(query2.value(0).toString());
       }
    }

    QSqlQuery query3(db);                                 // Заполнение выпадающего списка
    if (query3.exec("SELECT ID_zakaz FROM zakazi")){      // ID заказов
       while (query3.next()){
           ui->ObnovaIDzakaz->addItem(query3.value(0).toString());
       }
    }

    QSqlQuery query4(db);                                  // Заполнение выпадающего списка
    if (query4.exec("SELECT ID_dostavki FROM dostavka")){  // ID доставок
       while (query4.next()){
           ui->ObnovaIDdost->addItem(query4.value(0).toString());
       }
    }
                                                     // Заполнение выпадающего списка
    ui->ObnovaPoleMagaz->addItem("ID магазина");     // названиями столбцов таблицы "Магазины"
    ui->ObnovaPoleMagaz->addItem("Email");
    ui->ObnovaPoleMagaz->addItem("Оплата доставки");

    ui->ObnovaPoleTovar->addItem("ID товара");      // Заполнение выпадающего списка
    ui->ObnovaPoleTovar->addItem("Название");       // названиями столбцов таблицы "Товары"
    ui->ObnovaPoleTovar->addItem("Фирма");
    ui->ObnovaPoleTovar->addItem("Модель");
    ui->ObnovaPoleTovar->addItem("Тех. хар-ки");
    ui->ObnovaPoleTovar->addItem("Цена");
    ui->ObnovaPoleTovar->addItem("Гар. срок");

    ui->ObnovaPolezakaz->addItem("ID заказа");      // Заполнение выпадающего списка
    ui->ObnovaPolezakaz->addItem("ID магазина");    // названиями столбцов таблицы "Заказы"
    ui->ObnovaPolezakaz->addItem("ID товара");
    ui->ObnovaPolezakaz->addItem("Дата заказа");
    ui->ObnovaPolezakaz->addItem("ФИО клиента");
    ui->ObnovaPolezakaz->addItem("Телефон клиента");
    ui->ObnovaPolezakaz->addItem("Подтверждение оплаты");
    ui->ObnovaPolezakaz->addItem("Время заказа");

    ui->ObnovaPoleDost->addItem("ID доставки");      // Заполнение выпадающего списка
    ui->ObnovaPoleDost->addItem("ID заказа");        // названиями столбцов таблицы "Доставки"
    ui->ObnovaPoleDost->addItem("Дата доставки");
    ui->ObnovaPoleDost->addItem("Время доставки");
    ui->ObnovaPoleDost->addItem("Адрес");
    ui->ObnovaPoleDost->addItem("ФИО курьера");
}

obnova::~obnova()
{
    delete ui;
}
/*on_pushObMagaz_clicked - функция изменения записи
 в таблице "Магазины"
 Локальные переменные:
 field - название столбца изменяемой записи;
 id - ID изменяемой записи;
 newField - новое значение изменяемой записи;
 obMagaz - объект класса QSqlQuery, SQL запрос на выборку.

*/
void obnova::on_pushObMagaz_clicked()
{
    QString field=ui->ObnovaPoleMagaz->currentText();
    QString id=ui->ObnovaIDmagaz->currentText();
    QString newField=ui->lineNewMagaz->text();

    QSqlQuery obMagaz(db);
    obMagaz.prepare("UPDATE magazini SET " + magazini[field] + " = :new WHERE ID_magaz = " + id);
    obMagaz.bindValue(0,newField);
    obMagaz.exec();
    window()->close();
}

/*on_pushObTovar_clicked - функция изменения записи
 в таблице "Товары"
 Локальные переменные:
 field - название столбца изменяемой записи;
 id - ID изменяемой записи;
 newField - новое значение изменяемой записи;
 obTovar - объект класса QSqlQuery, SQL запрос на выборку.

*/
void obnova::on_pushObTovar_clicked()
{
    QString field=ui->ObnovaPoleTovar->currentText();
    QString id=ui->ObnovaIDtovar->currentText();
    QString newField=ui->lineNewTovar->text();

    QSqlQuery obTovar(db);
    obTovar.prepare("UPDATE tovari SET " + tovari[field] + " = :new WHERE ID_tovar = " + id);
    obTovar.bindValue(0,newField);
    obTovar.exec();
    window()->close();
}


/*on_pushObZakaz_clicked - функция изменения записи
 в таблице "Заказы"
 Локальные переменные:
 field - название столбца изменяемой записи;
 id - ID изменяемой записи;
 newField - новое значение изменяемой записи;
 obZakaz - объект класса QSqlQuery, SQL запрос на выборку.

*/
void obnova::on_pushObZakaz_clicked()
{
    QString field=ui->ObnovaPolezakaz->currentText();
    QString id=ui->ObnovaIDzakaz->currentText();
    QString newField=ui->lineNewZakaz->text();

    QSqlQuery obZakaz(db);
    obZakaz.prepare("UPDATE zakazi SET " + zakazi[field] + " = :new WHERE ID_zakaz = " + id);
    obZakaz.bindValue(0,newField);
    obZakaz.exec();
    window()->close();
}

/*on_pushObDost_clicked - функция изменения записи
 в таблице "Доставки"
 Локальные переменные:
 field - название столбца изменяемой записи;
 id - ID изменяемой записи;
 newField - новое значение изменяемой записи;
 obDjst - объект класса QSqlQuery, SQL запрос на выборку.

*/
void obnova::on_pushObDost_clicked()
{
    QString field=ui->ObnovaPoleDost->currentText();
    QString id=ui->ObnovaIDdost->currentText();
    QString newField=ui->lineNewDost->text();

    QSqlQuery obDost(db);
    obDost.prepare("UPDATE dostavka SET " + dostavka[field] + " = :new WHERE ID_dostavki = " + id);
    obDost.bindValue(0,newField);
    obDost.exec();
    window()->close();
}

