#include <QApplication>
#include <QApplication>
#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include "login.h"

bool openDB(QSqlDatabase &db)
{
    qInfo() << "Opening Database";
    db.setDatabaseName("C:\\Users\\biggi\\Documents\\GitHub\\AC-Library-Final/library-database.db");

    bool ok = db.open();
    if(ok)
    {
        qInfo() << "Opened database connection!";
        return true;
    }

    qInfo() << "Failed to open connection!";
    qInfo() << db.lastError().text();

    return false;
}

bool open()
{
        QSqlDatabase db = QSqlDatabase::database();
        bool isOpen = db.isOpen();

        qInfo() << "isOpen: " << isOpen;
        return isOpen;

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    if (openDB(db)) {
        w.show();
    }

    QSqlDatabase::database("QSQLITE").close();
    QSqlDatabase::removeDatabase("QSQLITE");

    return a.exec();
}
