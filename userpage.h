#ifndef USERPAGE_H
#define USERPAGE_H

#include <QMainWindow>
#include <QPainter>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QFont>

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

private:
    Ui::userpage *ui;
};

#endif // USERPAGE_H
