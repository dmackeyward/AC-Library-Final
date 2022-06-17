#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QMainWindow>
#include <QPainter>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QTableView>
#include <QFile>
#include <QFileDialog>
#include <QSortFilterProxyModel>

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
    void on_booksBtn_clicked();
    void on_addBtn_clicked();
    void on_removeBtn_clicked();
    void on_reportBtn_clicked();

private:
    Ui::adminpage *ui;

    void background_setup();
    void button_setup();
    void file_function();

    QSqlTableModel *model;
    QString table;
    QString user_id;
};

#endif // ADMINPAGE_H
