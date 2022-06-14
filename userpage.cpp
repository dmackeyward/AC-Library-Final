#include "userpage.h"
#include "ui_userpage.h"

userpage::userpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userpage)
{
    //setting the background
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

    button_setup();

    //getting user_id
    QString filename = "user_id.txt";
    QFile file(filename);

    qInfo() << "Exists:" << file.exists();

    if(file.open(QIODevice::ReadOnly))
    {
        userpage::user_id = file.readAll();
        file.close();
    }
    else
    {
        qInfo() << file.errorString();
    }

    //Opening the database:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/library-database.db");
    db.open();

    if (db.open()) {

        QSqlQuery query_size;
        query_size.exec("SELECT COUNT (*) FROM books");
        query_size.first();
        int count = query_size.value(0).toInt();
        qDebug() << "Count: " << count;

        int row = 0;
        QSqlQuery query;
        query.exec("SELECT * FROM books");

        ui->list1->setRowCount(count);
        ui->list1->setColumnCount(4);
        ui->list2->setRowCount(0);
        ui->list2->setColumnCount(4);

        while(query.next()) {

            QTableWidgetItem *book_id = new QTableWidgetItem();
            QTableWidgetItem *title = new QTableWidgetItem();
            QTableWidgetItem *author = new QTableWidgetItem();
            QTableWidgetItem *description = new QTableWidgetItem();

            book_id->setText(query.value(0).toString());
            ui->list1->setItem(row, 0, book_id);
            title->setText(query.value(1).toString());
            ui->list1->setItem(row, 1, title);
            author->setText(query.value(2).toString());
            ui->list1->setItem(row, 2, author);
            description->setText(query.value(3).toString());
            ui->list1->setItem(row, 3, description);
            row++;
        }
    }

    ui->details_name->setEnabled(false);
    ui->details_phone->setEnabled(false);
    ui->details_address->setEnabled(false);
    ui->details_email->setEnabled(false);
    ui->details_password->setEnabled(false);

    QSqlQuery query1;
    query1.exec("SELECT * FROM users");

    while(query1.next()) {
        ui->details_name->setText(query1.value(1).toString());
        ui->userpage_title->setText("Hi " + query1.value(1).toString());
        ui->details_phone->setText(query1.value(2).toString());
        ui->details_address->setText(query1.value(3).toString());
        ui->details_email->setText(query1.value(4).toString());
        ui->details_password->setText(query1.value(5).toString());
    }

    QSqlQuery query;
    QString borrowed_count = "SELECT COUNT (*) FROM borrowed_books WHERE user_id = :user_id;";
    query.prepare(borrowed_count);
    query.bindValue(":user_id", user_id);
    query.exec();
    query.first();
    int count = query.value(0).toInt();

    qDebug() << "Count: " << count;

    int row1 = 0;
    ui->existing_books->setRowCount(count);
    ui->existing_books->setColumnCount(3);

    QString borrowed_query = "SELECT books.book_id, books.title, books.author from borrowed_books JOIN books where user_id = :user_id AND borrowed_books.book_id = books.book_id;";
    query.prepare(borrowed_query);
    query.bindValue(":user_id", user_id);
    query.exec();

    while (query.next()) {
        QTableWidgetItem *book_id = new QTableWidgetItem();
        QTableWidgetItem *title = new QTableWidgetItem();
        QTableWidgetItem *author = new QTableWidgetItem();

        book_id->setText(query.value(0).toString());
        ui->existing_books->setItem(row1, 0, book_id);
        title->setText(query.value(1).toString());
        ui->existing_books->setItem(row1, 1, title);
        author->setText(query.value(2).toString());
        ui->existing_books->setItem(row1, 2, author);
        row1++;
    }

    db.close();

    list_setup();


}

userpage::~userpage()
{
    delete ui;
}

void userpage::on_button1_clicked()
{
    if (!ui->list1->selectedItems().empty()) {
        //target list > row count
        int targetRow = ui->list2->rowCount();

        //target list > insert
        ui->list2->insertRow(targetRow);

        //take and set items
        ui->list2->setItem(targetRow, 0, ui->list1->takeItem(ui->list1->currentRow(), 0));
        ui->list2->setItem(targetRow, 1, ui->list1->takeItem(ui->list1->currentRow(), 1));
        ui->list2->setItem(targetRow, 2, ui->list1->takeItem(ui->list1->currentRow(), 2));
        ui->list2->setItem(targetRow, 3, ui->list1->takeItem(ui->list1->currentRow(), 3));

        //remove row from list1
        ui->list1->removeRow(ui->list1->currentRow());
    }
}

void userpage::on_button2_clicked()
{
    if (!ui->list2->selectedItems().empty()) {

        //target list > row count
        int targetRow = ui->list1->rowCount();

        //target list > insert
        ui->list1->insertRow(targetRow);

        //take and set items
        ui->list1->setItem(targetRow, 0, ui->list2->takeItem(ui->list2->currentRow(), 0));
        ui->list1->setItem(targetRow, 1, ui->list2->takeItem(ui->list2->currentRow(), 1));
        ui->list1->setItem(targetRow, 2, ui->list2->takeItem(ui->list2->currentRow(), 2));
        ui->list1->setItem(targetRow, 3, ui->list2->takeItem(ui->list2->currentRow(), 3));

        //remove row from list1
        ui->list2->removeRow(ui->list2->currentRow());
    }
}

void userpage::on_booksBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void userpage::on_contactBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void userpage::on_accountBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void userpage::on_logoutBtn_clicked()
{
    this->close();
}

void userpage::on_editBtn_clicked()
{
    ui->details_name->setEnabled(true);
    ui->details_phone->setEnabled(true);
    ui->details_address->setEnabled(true);
    ui->details_email->setEnabled(true);
    ui->details_password->setEnabled(true);
}

void userpage::on_saveBtn_clicked()
{

    QString name = ui->details_name->text();
    QString phone = ui->details_phone->text();
    QString address = ui->details_address->text();
    QString email = ui->details_email->text();
    QString password = ui->details_password->text();

    //Opening the database:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/library-database.db");
    db.open();

    if (db.open()) {


        QString update = "UPDATE users SET name = :name, phone = :phone, address = :address, email = :email, password = :password WHERE user_id = :user_id;";

        QSqlQuery query;

        query.prepare(update);

        query.bindValue(":name", name);
        query.bindValue(":phone", phone);
        query.bindValue(":address", address);
        query.bindValue(":email", email);
        query.bindValue(":password", password);
        query.bindValue(":user_id", user_id);


        query.exec();

        ui->details_name->setEnabled(false);
        ui->details_phone->setEnabled(false);
        ui->details_address->setEnabled(false);
        ui->details_email->setEnabled(false);
        ui->details_password->setEnabled(false);
    }

    db.close();
    ui->userpage_title->setText("Hi " + ui->details_name->text());
}

void userpage::on_submitBtn_clicked()
{
    QString name = ui->details_name->text();
    QString phone = ui->details_phone->text();
    QString email = ui->details_email->text();
    QString details = ui->enquiryBox->toPlainText();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/library-database.db");
    db.open();

    if (db.open()) {

        QString insert_query = "INSERT INTO enquiry (name, phone, email, details, time, date) VALUES (:name, :phone, :email, :details, CURRENT_TIME, CURRENT_DATE);";

        QSqlQuery query;

        query.prepare(insert_query);

        query.bindValue(":name", name);
        query.bindValue(":phone", phone);
        query.bindValue(":email", email);
        query.bindValue(":details", details);

        query.exec();

        ui->details_name->setEnabled(false);
        ui->details_phone->setEnabled(false);
        ui->details_address->setEnabled(false);
        ui->details_email->setEnabled(false);
        ui->details_password->setEnabled(false);
    }

    db.close();

    QString enquiry = "Enquiry Submitted";
    QMessageBox::information(this,"Enquiry", enquiry);
    ui->enquiryBox->clear();
}



void userpage::on_checkoutBtn_clicked()
{
    int row = 0;
    int total = ui->list2->rowCount();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/library-database.db");
    db.open();

    if (db.isOpen()) {

        QString insert_borrowed = "INSERT INTO borrowed_books (user_id, book_id, date_borrowed, time_borrowed) VALUES (:user_id, :book_id, CURRENT_DATE, CURRENT_TIME);";
        QString update_books = "UPDATE books SET quantity = quantity - 1 WHERE book_id = :book_id;";
        QSqlQuery query;
        query.prepare(insert_borrowed);
        query.bindValue(":user_id", user_id);
        ui->list2->showRow(0);
        while (row < total) {
            QString book_id = ui->list2->item(row, 0)->text();
            query.bindValue(":book_id", book_id);
            query.exec();
            row++;
        }
    }
    ui->list2->hideRow(0);
    db.close();

    QString book = "Book Successfully Checked Out";
    QString books = "Books Successfully Checked Out";

    if (total == 1) {
        QMessageBox::information(this,"Check-Out", book);
    }

    else if (total > 1) {
        QMessageBox::information(this,"Check-Out", books);
    }

    ui->list2->setRowCount(0);

    //update quantity in books_database


    //update MyAccount ui


}

void userpage::button_setup()
{
    //button style
    QPixmap up("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/add2.png");
    QIcon ButtonIcon(up);
    ui->button1->setIcon(ButtonIcon);
    ui->button1->setIconSize(QSize(65, 65));

    QPixmap up1("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/remove3.png");
    QIcon ButtonIcon1(up1);
    ui->button2->setIcon(ButtonIcon1);
    ui->button2->setIconSize(QSize(65, 65));

    QPixmap up2("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/back.png");
    QIcon ButtonIcon2(up2);
    ui->logoutBtn->setIcon(ButtonIcon2);
    ui->logoutBtn->setIconSize(QSize(50, 50));

    QPixmap up3("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/contact_us.png");
    QIcon ButtonIcon3(up3);
    ui->contactBtn->setIcon(ButtonIcon3);
    ui->contactBtn->setIconSize(QSize(75, 75));

    QPixmap up4("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/books_logo.png");
    QIcon ButtonIcon4(up4);
    ui->booksBtn->setIcon(ButtonIcon4);
    ui->booksBtn->setIconSize(QSize(100, 100));

    QPixmap up5("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/your_account.png");
    QIcon ButtonIcon5(up5);
    ui->accountBtn->setIcon(ButtonIcon5);
    ui->accountBtn->setIconSize(QSize(65, 65));

    QPixmap up6("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/submit.png");
    QIcon ButtonIcon6(up6);
    ui->submitBtn->setIcon(ButtonIcon6);
    ui->submitBtn->setIconSize(QSize(100, 100));

    QPixmap up7("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/checkout.png");
    QIcon ButtonIcon7(up7);
    ui->checkoutBtn->setIcon(ButtonIcon7);
    ui->checkoutBtn->setIconSize(QSize(80, 80));

    QPixmap up8("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/edit.png");
    QIcon ButtonIcon8(up8);
    ui->editBtn->setIcon(ButtonIcon8);
    ui->editBtn->setIconSize(QSize(50, 50));

    QPixmap up9("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/save.png");
    QIcon ButtonIcon9(up9);
    ui->saveBtn->setIcon(ButtonIcon9);
    ui->saveBtn->setIconSize(QSize(50, 50));

    QPixmap up10("C:\\Users\\270163842\\OneDrive - UP Education\\Desktop\\Qt\\AC-Library-Final/return.png");
    QIcon ButtonIcon10(up10);
    ui->returnBtn->setIcon(ButtonIcon10);
    ui->returnBtn->setIconSize(QSize(75, 75));
}

void userpage::list_setup()
{
    //setting header titles and stretch
    QStringList header;
    header << "Book ID" << "Title" << "Author" << "Description";
    ui->list1->setHorizontalHeaderLabels(header);
    ui->list2->setHorizontalHeaderLabels(header);
    ui->list1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->list2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->list1->setColumnHidden(0, true);
    ui->list2->setColumnHidden(0, true);
    ui->list2->setColumnHidden(3, true);
    ui->list1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->list2->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList borrowed_header;
    borrowed_header << "Book ID" << "Title" << "Author";
    ui->existing_books->setHorizontalHeaderLabels(borrowed_header);
    ui->existing_books->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->existing_books->setColumnHidden(0, true);
    ui->existing_books->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //setting select all behavior
    ui->list1->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->list1->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->list2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->list2->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->existing_books->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->existing_books->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //setting the style for the list items
    ui->list1->setStyleSheet
            ("QListView { font-size: 12pt; }"
             "QListView::item { background-color: #FBDED8; "
             "border: 1px solid #000000; }"
             "QListView::item::selected { background-color: #FBDED8 }"
             "QListView::item::selected { color: #000000 }");

    ui->list2->setStyleSheet
            ("QListView { font-size: 12pt; }"
             "QListView::item { background-color: #D4FFCC; "
             "border: 1px solid #000000; }"
             "QListView::item::selected { background-color: #D4FFCC }"
             "QListView::item::selected { color: #000000 }");

    ui->existing_books->setStyleSheet
            ("QListView { font-size: 12pt; }"
             "QListView::item { background-color: #D4FFCC; "
             "border: 1px solid #000000; }"
             "QListView::item::selected { background-color: #D4FFCC }"
             "QListView::item::selected { color: #000000 }");
    //can also include hover - QListView::item::hover


    ui->contactus_label->setText("Central City Library<br>");
    ui->contactus_label_2->setText("Tāmaki Pātaka Kōrero<br><br>");
    ui->contactus_label_3->setText("Address: 44-46 Lorne Street<br><br>"
                                   "Phone: 09 377 0209<br><br>"
                                   "Email: aucklandlibrary@aucklandcouncil.govt.nz<br><br>"
                                   "Opening hours:<br>"
                                   "   Monday 9am - 8pm<br>"
                                   "   Tuesday 9am - 8pm<br>"
                                   "   Wednesday 9am - 8pm<br>"
                                   "   Thursday 9am - 8pm<br>"
                                   "   Friday 9am - 8pm<br>"
                                   "   Saturday 10am - 5pm<br>"
                                   "   Sunday 10am - 5pm");

    ui->list1->verticalHeader()->setVisible(false);
    ui->list2->verticalHeader()->setVisible(false);
    ui->existing_books->verticalHeader()->setVisible(false);


}



