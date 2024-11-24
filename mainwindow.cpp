#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regist.h"
#include "base_view.h"
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Окно авторизации");       //Изменение заголовка окна
    db=QSqlDatabase::addDatabase("QSQLITE");        //Подключение базы данных
}

MainWindow::~MainWindow()
{
    delete ui;
}


/*  on_pushButton_regist_clicked - переход на форму регистрации.
Локальная переменная:
    regist - объект класса regist;
Метод, используемый в подпрограмме:
    show - метод открытия формы.
*/

void MainWindow::on_pushButton_regist_clicked()
{
    regist *window = new regist;
    window->show();
    this->window()->close();
}

/*on_pushButton_entry_clicked - процедура входа.
 Локальные переменные:
   db - ссылка на базу данных;
   query - объект класса QSqlQuery, SQL запрос на выборку.

*/
void MainWindow::on_pushButton_entry_clicked()
{
    db.setDatabaseName("base_praktika.db");    //Открытие базы данных
    db.open();
    ui->label_4->setText("");
    QSqlQuery query;
    query.exec("SELECT password,login FROM users"); //Запрос на выборку и таблицы Пользователи
    while(query.next()){                           //Пока запрос содержит запись, выполнять
        if((query.value(0)==(ui->lineEdit_password->text()))&&(query.value(1)==(ui->lineEdit_login->text()))){
        base_view *view=new base_view;
        view->show();
        this->window()->close();
        }
        else
        {
        ui->label_4->setText("Неправильный логин или пароль");
         }
  }

}

