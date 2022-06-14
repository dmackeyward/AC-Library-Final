#ifndef USERPAGE_H
#define USERPAGE_H

#include <QMainWindow>
#include <QPainter>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QMessageBox>


namespace Ui {
class userpage;
}

class userpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit userpage(QWidget *parent = nullptr);
    ~userpage();

private slots:

    void on_button1_clicked();

    void on_button2_clicked();

    void on_booksBtn_clicked();

    void on_contactBtn_clicked();

    void on_accountBtn_clicked();

    void on_logoutBtn_clicked();

    void on_editBtn_clicked();

    void on_saveBtn_clicked();

    void on_submitBtn_clicked();

    void on_checkoutBtn_clicked();

    void button_setup();

    void list_setup();

private:
    Ui::userpage *ui;

    QString user_id;
    QString user_name;
};

#endif // USERPAGE_H
