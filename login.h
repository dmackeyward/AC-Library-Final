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

    void on_cancel_clicked();
    void on_submitBtn_clicked();
    void on_loginBtn_clicked();
    void on_registerBtn_clicked();

private:
    Ui::login *ui;

    void background_setup();
    bool isChar(char c);
    bool isDigit(const char c);
    bool is_valid(std::string email);
    bool checkIfExists(QString email);
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // LOGIN_H
