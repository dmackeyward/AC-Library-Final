#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QPainter>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFile>
#include "adminpage.h"
#include "userpage.h"
#include <QKeyEvent>

namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_clicked();

    void on_cancel_clicked();

    void on_submitBtn_clicked();

    void on_loginBtn_clicked();

    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::login *ui;
};

#endif // LOGIN_H
