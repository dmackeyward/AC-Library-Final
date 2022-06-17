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
#include <QKeyEvent>
#include "adminpage.h"
#include "userpage.h"

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

    void background_setup();
    void on_pushButton_clicked();
    void on_cancel_clicked();
    void on_submitBtn_clicked();
    void on_loginBtn_clicked();
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::login *ui;

    bool isChar(char c);
    bool isDigit(const char c);
    bool is_valid(std::string email);
};

#endif // LOGIN_H
