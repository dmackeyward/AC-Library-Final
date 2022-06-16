#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>
#include <QPainter>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class adminpage;
}

class adminpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminpage(QWidget *parent = nullptr);
    ~adminpage();

private slots:
    void on_logoutBtn_clicked();

    void on_userBtn_clicked();

    void on_enquiryBtn_clicked();

    void on_borrowedBtn_clicked();

    void on_addBtn_clicked();

    void on_removeBtn_clicked();

    void on_reportBtn_clicked();

    void on_booksBtn_clicked();

    void on_updateBtn_clicked();

private:
    Ui::adminpage *ui;

    void background_setup();
    void button_setup();
};

#endif // ADMINPAGE_H
