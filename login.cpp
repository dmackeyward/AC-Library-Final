#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QMainWindow::showFullScreen();
    QPixmap background("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/bookcase-bg.jpg");
    QImage image(background.size(), QImage::Format_ARGB32_Premultiplied); //Image with given size and format.
    image.fill(Qt::transparent); //fills with transparent
    QPainter p(&image);
    p.setOpacity(0.5); // set opacity from 0.0 to 1.0, where 0.0 is fully transparent and 1.0 is fully opaque.
    p.drawPixmap(0, 0, background); // given pixmap into the paint device.
    p.end();
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, image);
    this->setPalette(palette);
    ui->stackedWidget->setCurrentIndex(0);
}

void login::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void login::on_cancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void login::on_submitBtn_clicked()
{
    qInfo() << "Opening Database for Registration";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/library-database.db");

    if(!db.open())
    {
        qInfo() << "Failed to connect to database";
        qInfo() << db.lastError().text();
        return;
    }

    QString name = ui->register_name->text();
    QString phone = ui->register_phone->text();
    QString address = ui->register_address->text();
    QString email = ui->register_email->text();
    QString password = ui->register_password->text();

    //sql code
    QSqlQuery query;
    QString insert = "INSERT INTO users (name, phone, address, email, password, role) VALUES (:name, :phone, :address, :email, :password, 'user')";
    query.prepare(insert);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":address", address);
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec()) {
        qInfo() << "Query Successful";
    }

    else {
        qDebug() << query.lastError();
    }

    QString message;
    message = "Registration successful";
    QMessageBox::information(this,"Registration", message);
    db.close();
    ui->stackedWidget->setCurrentIndex(0);
}


void login::on_loginBtn_clicked()
{
    qInfo() << "Opening Database for Login";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/library-database.db");

    if(!db.open())
    {
        qInfo() << "Failed to connect to database";
        qInfo() << db.lastError().text();
        return;
    }

    QString email = ui->email->text();
    QString password = ui->password->text();
    QSqlQuery query;
    QString select = "SELECT DISTINCT user_id, name, role FROM users WHERE email = (:email) AND password = (:password)";

    //if email = email && password = password && role = admin
    query.prepare(select);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.exec();
    query.first();

    std::string user_id = query.value(0).toString().toStdString();
    QString role = query.value(1).toString();
    qInfo() << role;
    QString message;  

    if (role != "") {
        db.close();
        message = "Login successful";
        QMessageBox::information(this,"Login", message);

        //write user_id to file
        QString filename = "user_id.txt";
        QFile file(filename);
        if(file.open(QIODevice::WriteOnly))
        {
            file.write(user_id.c_str());
            file.close();
            qInfo() << "Wrote to the file";
        }
        else
        {
            qInfo() << file.errorString();
        }

        if (role == "admin") {
            adminpage *w = new adminpage;
            w->show();

        }

        else {
            userpage *w = new userpage;
            w->show();
        }
    }

    else {
        message = "Login failed";
        QMessageBox::information(this,"Login", message);
        db.close();
    }
}

void login::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
             {
                 on_loginBtn_clicked();
             }
}

login::~login()
{
    delete ui;
}
