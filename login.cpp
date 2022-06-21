#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{

    ui->setupUi(this);
    background_setup();
    ui->email->setFocus();

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
    QString name = ui->register_name->text();
    QString phone = ui->register_phone->text();
    QString address = ui->register_address->text();
    QString email = ui->register_email->text();
    QString password = ui->register_password->text();
    QSqlQuery query;
    QString insert = "INSERT INTO users (name, phone, address, email, password, role) VALUES (:name, :phone, :address, :email, :password, 'user')";
    query.prepare(insert);
    query.bindValue(":name", name);
    query.bindValue(":phone", phone);
    query.bindValue(":address", address);
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    //front end not null validation
    if (ui->register_name->text().isEmpty() || ui->register_phone->text().isEmpty() || ui->register_address->text().isEmpty() || ui->register_email->text().isEmpty() || ui->register_password->text().isEmpty())
    {
        QString empty;
        empty = "Please ensure all details are filled correctly";
        QMessageBox::information(this,"Registration", empty);
    }

    else {
        bool ans = is_valid(email.toStdString());

        if (ans) {
            //check to see if the email already exists in the database
            if (checkIfExists(email)) {
                if (query.exec()) {
                    qInfo() << "Query Successful";
                }

                else {
                    qDebug() << query.lastError();
                }

                QString message;
                message = "Registration successful";
                QMessageBox::information(this,"Registration", message);

                //need to clear fields after submit
                ui->register_name->clear();
                ui->register_phone->clear();
                ui->register_address->clear();
                ui->register_email->clear();
                ui->register_password->clear();
                ui->stackedWidget->setCurrentIndex(0);
                ui->email->setFocus();
            }

            else {
                QString email_already_taken;
                email_already_taken = "Email Already Taken";
                QMessageBox::information(this,"Registration", email_already_taken);
            }
        }

        else {
            QString invalid_email;
            invalid_email = "Invalid Email";
            QMessageBox::information(this,"Registration", invalid_email);
        }
    }
}

void login::on_loginBtn_clicked()
{
    QSqlQuery query;

    QString email = ui->email->text();
    QString password = ui->password->text();
    QString select = "SELECT DISTINCT user_id, role FROM users WHERE email = (:email) AND password = (:password)";
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
        message = "Login successful";
        QMessageBox::information(this,"Login", message);
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
    }

    ui->email->clear();
    ui->password->clear();
    ui->email->setFocus();
}

void login::keyPressEvent(QKeyEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 0) {
        if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
        {
            on_loginBtn_clicked();
        }
    }
}

login::~login()
{
    delete ui;
}

void login::background_setup()
{
    QMainWindow::showFullScreen();
    QPixmap background("://images/bookcase-bg.jpg");
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

bool login::isChar(char c)
{
    return ((c >= 'a' && c <= 'z')
            || (c >= 'A' && c <= 'Z'));
}

bool login::isDigit(const char c)
{
    return (c >= '0' && c <= '9');
}

bool login::is_valid(std::string email)
{
    if (!isChar(email[0])) {
        return 0;
    }

    int At = -1, Dot = -1;

    for (int i = 0;
         i < email.length(); i++) {

        if (email[i] == '@') {

            At = i;
        }

        else if (email[i] == '.') {

            Dot = i;
        }
    }

    if (At == -1 || Dot == -1)
        return 0;

    if (At > Dot)
        return 0;

    return !(Dot >= (email.length() - 1));
}

bool login::checkIfExists(QString email) {
    QSqlQuery query;
    QString select = "SELECT COUNT (*) FROM users WHERE email = (:email);";
    query.prepare(select);
    query.bindValue(":email", email);
    query.exec();
    query.first();
    int value = query.value(0).toInt();

    qDebug() << value;

    if (value == 0) {
        return true;
    }

    else {
        return false;
    }
}



