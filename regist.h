/*Форма regist.

  Форма регистрации пользователей.

  Переменная, используемые в форме:
    db - ссылка на базу данных.

  Функция, используемые в форме:
    void on_pushButton_zaregist_clicked() - функция реализующая регистрацию
    пользователя;


*/
#ifndef REGIST_H
#define REGIST_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class regist;
}

class regist : public QDialog
{
    Q_OBJECT

public:
    /*Конструктор класса regist*/
    explicit regist(QWidget *parent = nullptr);
    /*Деструктор класса regist*/
    ~regist();
    QSqlDatabase db;
private slots:
    void on_pushButton_zaregist_clicked();

private:
    Ui::regist *ui;

};

#endif // REGIST_H
