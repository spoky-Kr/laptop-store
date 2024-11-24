#include "del.h"
#include "ui_del.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QTime>

/*  id_Table - процедура заполнения выпадающего списка идентификаторами
выбранной таблицы.
Формальные параметры:
    nameTab - название таблицы;
    id - значение идентификатора таблицы.
Локальные переменные:
    query - объект класса QSqlQuery, SQL запрос на выборку.
*/
void Del::id_Table(QString nameTab, QString id){
    ui->BoxIDtable->clear();
db.open();
    QSqlQuery query(db);
        // SQL запрос на выборку из таблицы базы данных
    if (query.exec("SELECT " + QString(id) + " FROM " + QString(nameTab))){
            // Пока в запросе есть запись добавить ее в выпадающий список
       while (query.next()){
           ui->BoxIDtable->addItem(query.value(0).toString());
       }
    }
}

/*  DelTab - процедура удаления записи из таблицы базы данных.
Формальные параметры:
    Name_t - название таблицы;
    field - значение идентификатора таблицы.
Локальные переменные:
    Id - значение идентификатора, полученное из поля формы;
    DelTab - объект класса QSqlQuery, SQL запрос на выборку.
*/
void Del::DelTab(QString Name_t, QString field){

    QString Id = ui->BoxIDtable->currentText();
    if(db.open()){
        QSqlQuery DelTab(db);
            // Выполнение SQL запроса на удаление записи
        DelTab.exec("DELETE FROM " + QString(Name_t) +" WHERE " + QString(field) + " = " + Id);

    }
}


Del::Del(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Del)
{
    ui->setupUi(this);
    this->setWindowTitle("Окно удаления записей");
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("base_praktika.db");

    ui->BoxTable->addItem("Магазины");
    ui->BoxTable->addItem("Товары");
    ui->BoxTable->addItem("Заказы");
    ui->BoxTable->addItem("Доставки");
}

Del::~Del()
{
    delete ui;
}
/*  on_BoxTable_activated - процедура заполнения выпадающего списка
идентификаторами в соответствии с выбранной таблицей.
Локальные переменные:
    t - название таблицы;
    key - название первичного ключа таблицы.
    keys - контейнер с названиями таблиц и первичными ключами.
    tab - контейнер с названиями таблиц, как в базе данных и на русском;
Подпрограмма, используемая в процедуре:
    id_Table - процедура заполнения выпадающего списка идентификаторами таблицы.
*/
void Del::on_BoxTable_activated(int index)
{
    // Возврат значения из контейнера tab с названием таблицы из БД
    QString t = tab[ui->BoxTable->currentText()];
     // Возрат значения из контейнера key с названием первичного ключа из БД
    QString key = keys[t];
    id_Table(t, key);
}

/*  on_deleteButton_clicked - процедура, получающая названия таблиц с формы
    и вызывающая функцию DelTab;
  Локальные переменные:
    table - название таблицы;.
    id - название первичного ключа таблицы.
  Подпрограмма, используемая в процедуре:
    DelTab - процедура удаления записи из таблицы базы данных.
*/
void Del::on_deleteButton_clicked()
{
    QString table = tab[ui->BoxTable->currentText()];
        // Возрат значения из контейнера key с названием первичного ключа из БД
    QString id = keys[table];
    DelTab(table, id);
    window()->close();
}

