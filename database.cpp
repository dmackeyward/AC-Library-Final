#include "database.h"

database::database()
{

}

bool database::open()
{
        QSqlDatabase db = QSqlDatabase::database();
        bool isOpen = db.isOpen();

        qInfo() << "isOpen: " << isOpen;
        return isOpen;

}
