#include "dobav.h"
#include "ui_dobav.h"
#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDate>
#include <QTime>

dobav::dobav(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dobav)
{
    ui->setupUi(this);
    this->setWindowTitle("Окно добавления записей");

    // Добавление значений ID магазинов в выпадающий список;
    QSqlQuery query(db);
    if (query.exec("SELECT ID_magaz FROM magazini")){
       while (query.next()){
           ui->BoxIDmagaz->addItem(query.value(0).toString());
       }
    }
    // Добавление значений ID товаров в выпадающий список;
    QSqlQuery query2(db);
    if (query2.exec("SELECT ID_tovar FROM tovari")){
       while (query2.next()){
           ui->BoxIDtovar->addItem(query2.value(0).toString());
       }
    }
    // Добавление значений ID заказов в выпадающий список;
    QSqlQuery query3(db);
    if (query3.exec("SELECT ID_zakaz FROM zakazi")){
       while (query3.next()){
           ui->BoxIDzakaz->addItem(query3.value(0).toString());
       }
    }

    db=QSqlDatabase::addDatabase("QSQLITE");

}

dobav::~dobav()
{
    delete ui;
}
/*  on_pushMagazDob_clicked - функция добавления записи в таблицу "Магазины"
    Локальные переменные:
      magazin - ID магазина, полученное из lineIDmagaz;
      email - email магазина, полученное из lineEmail;
      oplDost - информация о доставке(бесплатная/нет), полученная из checkDostavka;
      db - ссылка на базу данных;
      DobMagaz - объект класса QSqlQuery, SQL запрос на выборку.
*/
void dobav::on_pushMagazDob_clicked()
{
    int magazin=ui->lineIDmagaz->text().toInt();
    QString email=ui->lineEmail->text();
    int oplDost=(ui->checkDostavka->checkState())/2;
    db.setDatabaseName("base_praktika.db");
    if(db.open()){
        QSqlQuery DobMagaz(db);
            // Выполнение SQL запроса на добавление в таблицу "magazini"
        DobMagaz.prepare("INSERT INTO magazini (ID_magaz, Email, opl_dostavka) VALUES (:ID_magaz, :Email, :opl_dostavka)");
            // Позиционная вставка значений в SQL запрос
        DobMagaz.bindValue(":ID_magaz", magazin);
        DobMagaz.bindValue(":Email", email);
        DobMagaz.bindValue(":opl_dostavka", oplDost);
        DobMagaz.exec();
        window()->close();
    }

}

/*  on_pushTovarDob_clicked - функция добавления записи в таблицу "Товары"
    Локальные переменные:
      tovar - ID товара, полученное из lineIDtovar;
      nazv - название товара, полученное из lineNazvanie;
      firma - фирма товара, полученная из lineFirma;
      model - модель товара, полученная из lineModel;
      TX - технические характеристики товара, полученные из lineTX;
      cost - стоимость товара, полученная из lineCost;
      garSrok - гарантийный срок товара, полученный из lineGarSrok;
      db - ссылка на базу данных;
      DobTovar - объект класса QSqlQuery, SQL запрос на выборку.
*/
void dobav::on_pushTovarDob_clicked()
{
    int tovar=ui->lineIDtovar->text().toInt();
    QString nazv=ui->lineNazvanie->text();
    QString firma=ui->lineFirma->text();
    QString model=ui->lineModel->text();
    QString TX=ui->lineTX->text();
    int cost=ui->lineCost->text().toInt();
    QString garSrok=ui->lineGarSrok->text();
    db.setDatabaseName("base_praktika.db");
    if(db.open()){
        QSqlQuery DobTovar(db);
            // Выполнение SQL запроса на добавление в таблицу "Товары"
        DobTovar.prepare("INSERT INTO tovari (ID_tovar, nazvanie, firma, modell, tx, cost, gar_srok) VALUES (:ID_tovar, :nazvanie, :firma, :modell, :tx, :cost, :gar_srok)");
            // Позиционная вставка значений в SQL запрос
        DobTovar.bindValue(":ID_tovar", tovar);
        DobTovar.bindValue(":nazvanie", nazv);
        DobTovar.bindValue(":firma", firma);
        DobTovar.bindValue(":modell", model);
        DobTovar.bindValue(":tx", TX);
        DobTovar.bindValue(":cost", cost);
        DobTovar.bindValue(":gar_srok", garSrok);
        DobTovar.exec();
        window()->close();
    }
}

/*  on_pushZakazDob_clicked - функция добавления записи в таблицу "Заказы"
    Локальные переменные:
      zakaz - ID заказа, полученное из lineIDzakaza;
      magazin - ID магазина, полученное из BoxIDmagaz;
      tovar - ID товара, полученное из BoxIDtovar;
      dat - дата заказа, полученная из lineDataZak;
      tim - время заказа, полученное из lineTimeZak;
      fio - ФИО клиента, полученное из lineFIOkl;
      tel - номер телефона клиента, полученный из lineTel;
      sost - состояние опалаты(оплачен/не оплачен), полученное из checkOplata;
      db - ссылка на базу данных;
      DobZakaz - объект класса QSqlQuery, SQL запрос на выборку.
*/
void dobav::on_pushZakazDob_clicked()
{
    int zakaz=ui->lineIDzakaza->text().toInt();
    int magazin=ui->BoxIDmagaz->currentText().toInt();
    int tovar=ui->BoxIDtovar->currentText().toInt();
    QString dat=ui->lineDataZak->text();
    QString tim=ui->lineTimeZak->text();
    QString fio=ui->lineFIOkl->text();
    QString tel=ui->lineTel->text();
    int sost=(ui->checkOplata->checkState())/2;
    db.setDatabaseName("base_praktika.db");
    if(db.open()){
        QSqlQuery DobZakaz(db);
            // Выполнение SQL запроса на добавление в таблицу "Заказы"
        DobZakaz.prepare("INSERT INTO zakazi (ID_zakaz, ID_magaz, ID_tovar, data_zakaza, FIO_klienta, tel, podtver_zak, time_zak) VALUES (:ID_zakaz, :ID_magaz, :ID_tovar, :data_zakaza, :FIO_klienta, :tel, :podtver_zak, :time_zak)");
            // Позиционная вставка значений в SQL запрос
        DobZakaz.bindValue(":ID_zakaz", zakaz);
        DobZakaz.bindValue(":ID_magaz", magazin);
        DobZakaz.bindValue(":ID_tovar", tovar);
        DobZakaz.bindValue(":data_zakaza", dat);
        DobZakaz.bindValue(":FIO_klienta", fio);
        DobZakaz.bindValue(":tel", tel);
        DobZakaz.bindValue(":podtver_zak", sost);
        DobZakaz.bindValue(":time_zak", tim);
        DobZakaz.exec();
        window()->close();
    }
}

/*  on_pushDostDob_clicked - функция добавления записи в таблицу "Доставки"
    Локальные переменные:
      dost - ID доставки, полученное из lineIDdost;
      zakaz - ID заказа, полученное из BoxIDzakaz;
      dataDost - дата доставки, полученная из lineDataDost;
      timeDost - время доставки, полученное из lineTimeDost;
      fioKur - ФИО курьера, полученное из lineFIOkur;
      adress - адрес доставки, полученный из lineAdress;
      db - ссылка на базу данных;
      DobDost - объект класса QSqlQuery, SQL запрос на выборку.
*/
void dobav::on_pushDostDob_clicked()
{
    int dost=ui->lineIDdost->text().toInt();
    int zakaz=ui->BoxIDzakaz->currentText().toInt();
    QString dataDost=ui->lineDataDost->text();
    QString timeDost=ui->lineTimeDost->text();
    QString fioKur=ui->lineFIOkur->text();
    QString adress=ui->lineAdress->text();
    db.setDatabaseName("base_praktika.db");
    if(db.open()){
        QSqlQuery DobDost(db);
            // Выполнение SQL запроса на добавление в таблицу "Доставки"
        DobDost.prepare("INSERT INTO dostavka (ID_dostavki, ID_zakaz, data_dostavki, time_dost, adress, FIO_kur) VALUES (:ID_dostavki, :ID_zakaz, :data_dostavki, :time_dost, :adress, :FIO_kur)");
            // Позиционная вставка значений в SQL запрос
        DobDost.bindValue(":ID_dostavki", dost);
        DobDost.bindValue(":ID_zakaz", zakaz);
        DobDost.bindValue(":data_dostavki", dataDost);
        DobDost.bindValue(":time_dost", timeDost);
        DobDost.bindValue(":adress", adress);
        DobDost.bindValue(":FIO_kur", fioKur);
        DobDost.exec();
        window()->close();
    }
}

