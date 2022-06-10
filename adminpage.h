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

private:
    Ui::adminpage *ui;
};

#endif // ADMINPAGE_H
