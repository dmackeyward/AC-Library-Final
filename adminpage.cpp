#include "adminpage.h"
#include "ui_adminpage.h"

adminpage::adminpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminpage)
{
    ui->setupUi(this);
    background_setup();
    button_setup();

    //ui->database->
}

adminpage::~adminpage()
{
    delete ui;
}

void adminpage::background_setup()
{
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
}

void adminpage::button_setup()
{

    QPixmap up("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/add2.png");
    QIcon ButtonIcon(up);
    ui->addBtn->setIcon(ButtonIcon);
    ui->addBtn->setIconSize(QSize(65, 65));

    QPixmap up1("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/remove3.png");
    QIcon ButtonIcon1(up1);
    ui->removeBtn->setIcon(ButtonIcon1);
    ui->removeBtn->setIconSize(QSize(65, 65));

    QPixmap up2("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/back.png");
    QIcon ButtonIcon2(up2);
    ui->logoutBtn->setIcon(ButtonIcon2);
    ui->logoutBtn->setIconSize(QSize(50, 50));

    QPixmap up3("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/contact_us.png");
    QIcon ButtonIcon3(up3);
    ui->enquiryBtn->setIcon(ButtonIcon3);
    ui->enquiryBtn->setIconSize(QSize(75, 75));

    QPixmap up4("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/books_logo.png");
    QIcon ButtonIcon4(up4);
    ui->booksBtn->setIcon(ButtonIcon4);
    ui->booksBtn->setIconSize(QSize(100, 100));

    QPixmap up5("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/your_account.png");
    QIcon ButtonIcon5(up5);
    ui->userBtn->setIcon(ButtonIcon5);
    ui->userBtn->setIconSize(QSize(65, 65));

    QPixmap up6("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/report.png");
    QIcon ButtonIcon6(up6);
    ui->reportBtn->setIcon(ButtonIcon6);
    ui->reportBtn->setIconSize(QSize(65, 65));

    QPixmap up7("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/save.png");
    QIcon ButtonIcon7(up7);
    ui->updateBtn->setIcon(ButtonIcon7);
    ui->updateBtn->setIconSize(QSize(65, 65));

    QPixmap up10("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/return.png");
    QIcon ButtonIcon10(up10);
    ui->borrowedBtn->setIcon(ButtonIcon10);
    ui->borrowedBtn->setIconSize(QSize(75, 75));
}

void adminpage::on_logoutBtn_clicked()
{
    this->close();
}

void adminpage::on_userBtn_clicked()
{
    ui->database->setRowCount(0);

    QSqlQuery query_size;
    query_size.exec("SELECT COUNT (*) FROM users;");
    query_size.first();
    int count = query_size.value(0).toInt();
    ui->database->setRowCount(count);
    ui->database->setColumnCount(7);

    QStringList header;
    header << "User ID" << "Name" << "Phone" << "Address" << "Email" << "Password" << "Role";
    ui->database->setHorizontalHeaderLabels(header);
    ui->database->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->database->verticalHeader()->setVisible(false);

    int row = 0;
    QSqlQuery query;
    query.exec("SELECT * FROM users;");
    while(query.next()) {

        QTableWidgetItem *user_id = new QTableWidgetItem();
        QTableWidgetItem *name = new QTableWidgetItem();
        QTableWidgetItem *phone = new QTableWidgetItem();
        QTableWidgetItem *address = new QTableWidgetItem();
        QTableWidgetItem *email = new QTableWidgetItem();
        QTableWidgetItem *password = new QTableWidgetItem();
        QTableWidgetItem *role = new QTableWidgetItem();

        user_id->setText(query.value(0).toString());
        ui->database->setItem(row, 0, user_id);
        name->setText(query.value(1).toString());
        ui->database->setItem(row, 1, name);
        phone->setText(query.value(2).toString());
        ui->database->setItem(row, 2, phone);
        address->setText(query.value(3).toString());
        ui->database->setItem(row, 3, address);
        email->setText(query.value(4).toString());
        ui->database->setItem(row, 4, email);
        password->setText(query.value(5).toString());
        ui->database->setItem(row, 5, password);
        role->setText(query.value(6).toString());
        ui->database->setItem(row, 6, role);
        row++;
    }
}

void adminpage::on_enquiryBtn_clicked()
{
    ui->database->setRowCount(0);

    QSqlQuery query_size;
    query_size.exec("SELECT COUNT (*) FROM enquiry;");
    query_size.first();
    int count = query_size.value(0).toInt();
    ui->database->setRowCount(count);
    ui->database->setColumnCount(9);

    QStringList header;
    header << "Enquiry ID" << "Name" << "Phone" << "Email" << "Details" << "Time" << "Date" << "Resolved" << "Resolved Date";
    ui->database->setHorizontalHeaderLabels(header);
    ui->database->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->database->verticalHeader()->setVisible(false);

    int row = 0;
    QSqlQuery query;
    query.exec("SELECT * FROM enquiry;");
    while(query.next()) {

        QTableWidgetItem *enquiry_id = new QTableWidgetItem();
        QTableWidgetItem *name = new QTableWidgetItem();
        QTableWidgetItem *phone = new QTableWidgetItem();
        QTableWidgetItem *email = new QTableWidgetItem();
        QTableWidgetItem *details = new QTableWidgetItem();
        QTableWidgetItem *time = new QTableWidgetItem();
        QTableWidgetItem *date = new QTableWidgetItem();
        QTableWidgetItem *resolved = new QTableWidgetItem();
        QTableWidgetItem *resolved_date = new QTableWidgetItem();

        enquiry_id->setText(query.value(0).toString());
        ui->database->setItem(row, 0, enquiry_id);
        name->setText(query.value(1).toString());
        ui->database->setItem(row, 1, name);
        phone->setText(query.value(2).toString());
        ui->database->setItem(row, 2, phone);
        email->setText(query.value(3).toString());
        ui->database->setItem(row, 3, email);
        details->setText(query.value(4).toString());
        ui->database->setItem(row, 4, details);
        time->setText(query.value(5).toString());
        ui->database->setItem(row, 5, time);
        date->setText(query.value(6).toString());
        ui->database->setItem(row, 6, date);
        resolved->setText(query.value(7).toString());
        ui->database->setItem(row, 7, resolved);
        resolved_date->setText(query.value(8).toString());
        ui->database->setItem(row, 8, resolved_date);
        row++;
    }
}

void adminpage::on_borrowedBtn_clicked()
{
    ui->database->setRowCount(0);

    QSqlQuery query_size;
    query_size.exec("SELECT COUNT (*) FROM borrowed_books;");
    query_size.first();
    int count = query_size.value(0).toInt();
    ui->database->setRowCount(count);
    ui->database->setColumnCount(7);

    QStringList header;
    header << "Borrowed ID" << "User ID" << "Book ID" << "Date Borrowed" << "Time Borrowed" << "Due Date";
    ui->database->setHorizontalHeaderLabels(header);
    ui->database->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->database->verticalHeader()->setVisible(false);

    int row = 0;
    QSqlQuery query;
    query.exec("SELECT * FROM borrowed_books;");
    while(query.next()) {

        QTableWidgetItem *borrowed_id = new QTableWidgetItem();
        QTableWidgetItem *user_id = new QTableWidgetItem();
        QTableWidgetItem *book_id = new QTableWidgetItem();
        QTableWidgetItem *date_borrowed = new QTableWidgetItem();
        QTableWidgetItem *time_borrowed = new QTableWidgetItem();
        QTableWidgetItem *due_date = new QTableWidgetItem();

        borrowed_id->setText(query.value(0).toString());
        ui->database->setItem(row, 0, borrowed_id);
        user_id->setText(query.value(1).toString());
        ui->database->setItem(row, 1, user_id);
        book_id->setText(query.value(2).toString());
        ui->database->setItem(row, 2, book_id);
        date_borrowed->setText(query.value(3).toString());
        ui->database->setItem(row, 3, date_borrowed);
        time_borrowed->setText(query.value(4).toString());
        ui->database->setItem(row, 4, time_borrowed);
        due_date->setText(query.value(5).toString());
        ui->database->setItem(row, 5, due_date);
        row++;
    }
}

void adminpage::on_addBtn_clicked()
{

}

void adminpage::on_removeBtn_clicked()
{

}

void adminpage::on_reportBtn_clicked()
{

}

void adminpage::on_booksBtn_clicked()
{
    ui->database->setRowCount(0);

    QSqlQuery query_size;
    query_size.exec("SELECT COUNT (*) FROM books WHERE quantity > 0;");
    query_size.first();
    int count = query_size.value(0).toInt();
    ui->database->setRowCount(count);
    ui->database->setColumnCount(4);

    QStringList header;
    header << "Book ID" << "Title" << "Author" << "Description";
    ui->database->setHorizontalHeaderLabels(header);
    ui->database->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->database->verticalHeader()->setVisible(false);

    int row = 0;
    QSqlQuery query;
    query.exec("SELECT * FROM books WHERE quantity > 0;");
    while(query.next()) {

        QTableWidgetItem *book_id = new QTableWidgetItem();
        QTableWidgetItem *title = new QTableWidgetItem();
        QTableWidgetItem *author = new QTableWidgetItem();
        QTableWidgetItem *description = new QTableWidgetItem();

        book_id->setText(query.value(0).toString());
        ui->database->setItem(row, 0, book_id);
        title->setText(query.value(1).toString());
        ui->database->setItem(row, 1, title);
        author->setText(query.value(2).toString());
        ui->database->setItem(row, 2, author);
        description->setText(query.value(3).toString());
        ui->database->setItem(row, 3, description);
        row++;
    }
}

void adminpage::on_updateBtn_clicked()
{

}

