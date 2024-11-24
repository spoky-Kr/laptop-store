/*Форма mainwindow.

  Форма авторизации пользователей.

  Переменная, используемые в форме:
    db - ссылка на базу данных.

  Функции, используемые в форме:
    void on_pushButton_regist_clicked() - функция перехода на форму для регистрации;
    void on_pushButton_entry_clicked() - функция перехода на форму для работы с БД.

*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*Конструктор класса MainWindow*/
    MainWindow(QWidget *parent = nullptr);
    /*Деструктор класса MainWindow*/
    ~MainWindow();
        QSqlDatabase db;


private slots:

    void on_pushButton_regist_clicked();

    void on_pushButton_entry_clicked();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
