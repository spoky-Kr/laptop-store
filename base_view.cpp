#include "base_view.h"
#include "ui_base_view.h"
#include "mainwindow.h"
#include "dobav.h"
#include "del.h"
#include "obnova.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QIODevice>
#include <QFile>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QTextDocument>
#include <QVector>
#include <QList>
#include <QMessageBox>
base_view::base_view(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::base_view)
{
    ui->setupUi(this);
    this->setWindowTitle("Окно работы с БД");

    // Заполнение выпадающего списка названиями таблиц из базы данных
    ui->comboBox->addItem("Магазины");
    ui->comboBox->addItem("Товары");
    ui->comboBox->addItem("Заказы");
    ui->comboBox->addItem("Доставки");

}

base_view::~base_view()
{
    delete ui;
}
/*viewTab - функция отображения таблиц базы данных на форме.
 Формальный параметр:
   nameTab - название выводимой таблицы.
 Локальные переменные:
    query - объект класса QSqlQuery, SQL запрос к базе данных;
    names - контейнер с названиями столбцов в выбранной таблице;
    i, index - счетчики циклов.

*/
void base_view::viewTab(QString nameTab){
    QSqlQuery query(db);
    if(query.exec("SELECT * FROM "+nameTab)){  // Выполнение запроса
        ui->tableWidget->clear();              // Очищение виджета таблицы
        ui->tableWidget->setShowGrid(true);    // Отображение сетки на виджете
        ui->tableWidget->verticalHeader()->setVisible(false); // Отключение нулевого столбца с автоматической нумерацией строк
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); // Установка ширины столбцов по содержимому
        ui->tableWidget->setRowCount(query.size()); // Установка количества столбцов
        ui->tableWidget->setColumnCount(query.record().count()); // Установка количества строк

        // Обращение к базе данных для замены названия столбцов
        QStringList names;
        for(int i=0;i<query.record().count();i++)
            names.push_back(query.record().fieldName(i));
        ui->tableWidget->setHorizontalHeaderLabels(names);

        int index=0;
        while (query.next()){            //Пока запроса содержит запись, передавать запись в виджет
            ui->tableWidget->insertRow(index);
            for(int i=0;i<query.record().count();i++){
                ui->tableWidget->setItem(index,i,new QTableWidgetItem(query.value(i).toString()));
            }
            index++;
        }

    }
}

/* sortTab - функция, реализующая сортироку записей в таблице,
   по выбранному параметру.
   Формальные параметры:
     nameTab - название таблицы, выбранной для сортировки;
     field - название столбца, по которому производится,
     сортировка.
   Локальные переменные:
    query - объект класса QSqlQuery, SQL запрос к базе данных;
    names - контейнер с названиями столбцов в выбранной таблице;
    i, index - счетчики циклов.

*/
void base_view::sortTab(QString nameTab,QString field){
    ui->tableWidget->clear();              // Очищение виджета вывода таблиц
    QSqlQuery query(db);                   // Объявление SQL запроса к базе данных

    if(query.exec("SELECT * FROM " + nameTab + " ORDER BY " + field)){ //выполнение запроса

        // Обращение к базе данных для замены названия столбцов
        QStringList names;
        for(int i=0;i<query.record().count();i++)
            names.push_back(query.record().fieldName(i));
        ui->tableWidget->setHorizontalHeaderLabels(names);

        int index=0;
        while (query.next()){              //Пока запроса содержит запись, добавлять ее в виджет
            ui->tableWidget->insertRow(index);
            for(int i=0; i<query.record().count(); i++){
                ui->tableWidget->setItem(index,i,new QTableWidgetItem(query.value(i).toString()));
            }
            index++;
        }
    }
}

/*  on_comboBox_activated - функция, реализующая вывод выбранной
из выпадающего списка таблицы в виджет.
Локальные переменные:
    i - индекс выбранной пользователем таблицы из выпадающего списка.
Используемые подпрограммы в функции:
    viewTab - процедура вывода таблицы в виджет на рабочем
пространстве.
*/
void base_view::on_comboBox_activated(int index)
{
    // Получение индекса выбранной пользователем записи из выпадающего списка
    int i =  ui->comboBox->currentIndex();

    switch (i){     // Вывод таблиц в зависимости от выбранного пункта в ComboBox
    case 0:         // Вывод таблицы "Магазины"
    {
        ui->sort_pick->clear();
        ui->sort_pick->addItem("ID магазина");
        ui->sort_pick->addItem("Email");
        ui->sort_pick->addItem("Оплата доставки");

        viewTab("magazini");
        break;
    }

    case 1:   // Вывод таблицы "Товары"
    {
        ui->sort_pick->clear();
        ui->sort_pick->addItem("ID товара");
        ui->sort_pick->addItem("Название");
        ui->sort_pick->addItem("Фирма");
        ui->sort_pick->addItem("Модель");
        ui->sort_pick->addItem("Тех. хар-ки");
        ui->sort_pick->addItem("Цена");
        ui->sort_pick->addItem("Гар. срок");

        viewTab("tovari");
        break;

    }
    case 2:   // Вывод таблицы "Заказы"
    {
        ui->sort_pick->clear();
        ui->sort_pick->addItem("ID заказа");
        ui->sort_pick->addItem("ID магазина");
        ui->sort_pick->addItem("ID товара");
        ui->sort_pick->addItem("Дата заказа");
        ui->sort_pick->addItem("ФИО клиента");
        ui->sort_pick->addItem("Тел. клиента");
        ui->sort_pick->addItem("Время заказа");

        viewTab("zakazi");
        break;
    }


    case 3:   // Вывод таблицы "Доставки"
    {
        ui->sort_pick->clear();
        ui->sort_pick->addItem("ID доставки");
        ui->sort_pick->addItem("ID заказа");
        ui->sort_pick->addItem("Дата доставки");
        ui->sort_pick->addItem("Время доставки");
        ui->sort_pick->addItem("Адрес доставки");
        ui->sort_pick->addItem("ФИО курьера");

        viewTab("dostavka");
        break;
    }
    }

}

/*  on_sortButton_clicked - процедура, реализующая вывод результатов сортировки
таблиц базы данных по нажатию кнопки.
Локальные переменные:
    Table - название таблицы, полученное из выпадающего списка;
    Field - название столбца для сортировки, полученное из выпадающего списка;
Процедура, используемая в подпрограмме:
    sortTab - процедура сортировки таблиц.
*/
void base_view::on_sortButton_clicked()
{
    QString Table=ui->comboBox->currentText();
    QString Field=ui->sort_pick->currentText();

    if(Table=="Магазины"){sortTab("magazini", magazini[Field]);}
    else if (Table=="Товары"){sortTab("tovari",tovari[Field]);}
    else if (Table=="Заказы"){sortTab("zakazi",zakazi[Field]);}
    else if (Table=="Доставки"){sortTab("dostavka",dostavka[Field]);}
}


/*  on_dobavButton_clicked - переход на форму добавления.
Локальная переменная:
    dobav - объект класса dobav;
Метод, используемый в подпрограмме:
    show - метод открытия формы.
*/
void base_view::on_dobavButton_clicked()
{
    dobav *window = new dobav;
    window->show();
}

/*  on_udalButton_2_clicked - переход на форму удаления.
Локальная переменная:
    Del - объект класса Del;
Метод, используемый в подпрограмме:
    show - метод открытия формы.
*/
void base_view::on_udalButton_2_clicked()
{
    Del *window=new Del;
    window->show();
}

/*  on_izmenButton_3_clicked - переход на форму удаления.
Локальная переменная:
    obnova - объект класса obnova;
Метод, используемый в подпрограмме:
    show - метод открытия формы.
*/
void base_view::on_izmenButton_3_clicked()
{
    obnova *window=new obnova;
    window->show();
}

/*  on_vigruzka_clicked - процедура, реализующая запись данных таблиц базы
в текстовый файл.
Локальные переменные:
    table - название таблицы, полученное из выпадающего списка;
    query - объект класса QSqlQuery, SQL запрос к базе данных;
    f - текстовый файл для записи;
    inF - объект класса QTextStream, текстовый поток;
    i - счетчик цикла.
*/
void base_view::on_vigruzka_clicked()
{
    QString table = tab[ui->comboBox->currentText()];   // Получение названия таблицы БД
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("base_praktika.db");
    if (db.open()) {
    QSqlQuery query(db);
    query.exec("SELECT * FROM " + table);  // Выполнение SQL запроса к БД
    QFile f("table.txt");   // Создание файла по указанному пути
    if (f.open(QIODevice::WriteOnly)) {         // Открытие файла для записи
        QTextStream inF(&f);
        while (query.next()) {                  // Пока в запросе есть запись, записывать ее в файл
        for (int i = 0; i < query.record().count(); i++) {
        inF << query.value(i).toByteArray() << "; ";    // Установка разделителей
        }
        inF << "\n";                        // Переход потока на следующую строку
        }

        f.close();      // Закрытие файла
        QMessageBox b;
        b.setText("Файл успешно создан записан");
        b.exec();
        }
        db.close();     // Закрытие БД
    }

}

/*  on_vivod_clicked - процедура, реализующая запись данных таблиц базы
    в pdf файл.
Локальные переменные:
    pr - объект класса QPrinter, для отправки вывода PDF на принтер;
    dlg - объект класса, предоставляющий диалоговое окно для указания
    конфигурации принтера;
    name_table - название таблицы, выводимой на печать;
    th - строка кода HTML, заполняющаяя заголовки таблицы;
    Print - запрос SQL к базе данных на выборку из таблицы;
    Col - вектор, хранящий названия столбцов таблицы;
    i - счетсик цикла;
    html - строка, содержащая код HTML таблицы;
    doc - документ, в который записывается код HTML таблицы.
*/
void base_view::on_vivod_clicked()
{
    QPrinter * pr = new QPrinter();
    QPrintDialog dlg(pr, this);
    QString name_table = tab[ui->comboBox->currentText()];

    QString th = "";

    db.open();
    QSqlQuery Print(db);            // Создание запроса на выборку из таблицы базы
    if (Print.exec("SELECT * FROM " + name_table)){
        QVector<QString> Col;       // Создание вектора названий столбцов таблицы
        for (int i = 0; i < Print.record().count(); i++)
            Col.push_back(Print.record().fieldName(i));
                                    // Формирование HTML кода для заголовков столбцов
        for (int i = 0; i < Col.size(); i++){
            th += "<td>" + Col[i] + "</td>";
        }

    };
                                    // Формирование HTML кода таблицы
    QString html ="<table border='1'> "
                                    // Запись заголовка таблицы в HTML код
                  "<caption>" + name_table + "</caption>"
                  "<tr>" + th + "</tr>";
                                    // Добавление записей в HTML код таблицы
    while (Print.next()){
        html+="<tr>";
        for (int i = 0; i < Print.record().count(); i++){
            html += "<td>" + Print.value(i).toString() + "</td>";
        }
        html += "</tr> \n";
    }
    html += "</table>";

    if(dlg.exec() == QDialog::Accepted){
        QTextDocument doc;          // Формирование документа PDF для
        doc.setHtml(html);          // для отправки на печать
        doc.print(pr);
    }

}


/*  on_zagruzka_clicked - процедура, реализующая запись данных таблиц базы
из текстового файла.
Локальные переменные:
    db - ссылка на базу данных;
    f - файл по указанному пути, из которого реализуется запись в БД;
    query - объект класса QSqlQuery, SQL запрос;
    outF - объект класса QTextStream, тектовый поток;
    list - контейнер, содержащий данные для записи;
    str - строка, содержащая записи таблицы.
*/
void base_view::on_zagruzka_clicked()
{

    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("base_praktika.db");
    db.open();
    QFile f("table.txt");
    QSqlQuery query;
                            // Открытие файла только для чтения
    if (f.open(QIODevice::ReadOnly)) {
                            // Создание текстового потока
    QTextStream outF(&f);
    QList<QString>list;
                            // Пока не конец файла добавлять записи
    while (!outF.atEnd()) {
    QString str = outF.readLine();
    list = str.split(";");


                                // Добавление данных из файла в таблицу
    switch(ui->comboBox->currentIndex()){
    case 0:
    {                       // Добавление в таблицу "Магазины"
       if (db.open()) {
       QSqlQuery query;
       query.prepare("INSERT INTO magazini (ID_magaz, Email, opl_dostavka) " "VALUES (:ID_magaz, :Email, :opl_dostavka)");
       query.bindValue(0, list[0]);
       query.bindValue(1, list[1]);
       query.bindValue(2, list[2]);
       }
       break;
    }
    case 1:
    {                       // Добавление в таблицу "Товары"
       if (db.open()) {
       QSqlQuery query;
       query.prepare("INSERT INTO tovari (ID_tovar, nazvanie, firma, modell, tx, cost, gar_srok) "
       "VALUES (:ID_tovar, :nazvanie, :firma, :modell, :tx, :cost, :gar_srok)");
       query.bindValue(0, list[0]);
       query.bindValue(1, list[1]);
       query.bindValue(2, list[2]);
       query.bindValue(3, list[3]);
       query.bindValue(4, list[4]);
       query.bindValue(5, list[5]);
       query.bindValue(6, list[6]);
       }
       break;
    }
    case 2:
    {                       // Добавление в таблицу "Заказы"
       if (db.open()) {
       QSqlQuery query;
       query.prepare("INSERT INTO zakazi (ID_zakaz, ID_magaz, ID_tovar, data_zakaza, FIO_klienta, tel, podtver_zak, time_zak) "
       "VALUES (:ID_zakaz, :ID_magaz, :ID_tovar, :data_zakaza, :FIO_klienta, :tel, :podtver_zak, :time_zak)");
       query.bindValue(0, list[0]);
       query.bindValue(1, list[1]);
       query.bindValue(2, list[2]);
       query.bindValue(3, list[3]);
       query.bindValue(4, list[4]);
       query.bindValue(5, list[5]);
       query.bindValue(6, list[6]);
       query.bindValue(7, list[7]);
       }
       break;
    }
    case 3:
    {                       // Добавление в таблицу "Доставки"
       if (db.open()) {
       QSqlQuery query;
       query.prepare("INSERT INTO dostavka (ID_dostavki, ID_zakaz, data_dostavki, time_dost, adress, FIO_kur) "
       "VALUES (:ID_dostavki, :ID_zakaz, :data_dostavki, :time_dost, :adress, :FIO_kur)");
       query.bindValue(0, list[0]);
       query.bindValue(1, list[1]);
       query.bindValue(2, list[2]);
       query.bindValue(3, list[3]);
       query.bindValue(4, list[4]);
       query.bindValue(5, list[5]);
       }
       break;
    }
}
}
f.close();              // Закрытие файла
}
}

