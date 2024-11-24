#include "regist.h"
#include "ui_regist.h"
#include "test.h"
#include <QString>
#include "mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

regist::regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regist)
{

    ui->setupUi(this);
    this->setWindowTitle("Окно регистрации");
    db=QSqlDatabase::addDatabase("QSQLITE");   //Подключение базы данных
}

regist::~regist()
{
    delete ui;
}

/* on_pushButton_zaregist_clicked - функция регистрации пользователей
 Локальные переменные:
 pass - пароль нового пользователя, полученный из lineEdit_password;
 log -  логин нового пользователя, полученный из lineEdit_login;
 f -  ФИО нового пользователя, полученное из lineEdit_FIO;
 db - ссылка на базу данных;
 query - объект класса QSqlQuery, SQL запрос на выборку.

*/
void regist::on_pushButton_zaregist_clicked()
{
    QString pass=ui->lineEdit_password->text();
    QString log=ui->lineEdit_login->text();
    QString f=ui->lineEdit_FIO->text();
    db.setDatabaseName("base_praktika.db");
    db.open();
    QSqlQuery query;                                    // Запрос на добавление пользователя
    QString st="INSERT INTO users (password, login, fio) VALUES (:password, :login, :fio)";
    query.prepare(st);
    query.bindValue(":password",pass);
    query.bindValue(":login",log);
    query.bindValue(":fio",f);
    query.exec();
    window()->close();
    MainWindow *window = new MainWindow;
    window->show();

}


