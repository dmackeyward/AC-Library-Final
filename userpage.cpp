#include "userpage.h"
#include "ui_userpage.h"

userpage::userpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userpage)
{
    ui->setupUi(this);
    background_setup();
    button_setup();
    file_function();
    size_of_lists();
    populate_booktable();
    populate_details();
    populate_existingbooks();
    list_setup();
}

userpage::~userpage()
{
    delete ui;
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

    ui->userpage_title->setText("Hi " + ui->details_name->text());
}

void userpage::on_submitBtn_clicked()
{
    if (!ui->enquiryBox->document()->isEmpty()) {
        QString name = ui->details_name->text();
        QString phone = ui->details_phone->text();
        QString email = ui->details_email->text();
        QString details = ui->enquiryBox->toPlainText();
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

        QString enquiry = "Enquiry Submitted";
        QMessageBox::information(this,"Enquiry", enquiry);
        ui->enquiryBox->clear();
    }
}

void userpage::on_checkoutBtn_clicked()
{
    int row = 0;
    int total = ui->list2->rowCount();

    QString insert_borrowed = "INSERT INTO borrowed_books (user_id, book_id, date_borrowed, time_borrowed, due_date, returned_status) VALUES (:user_id, :book_id, CURRENT_DATE, CURRENT_TIME, DATE(CURRENT_DATE, '+30 days'), 'no');";
    QString update_books = "UPDATE books SET quantity = quantity - 1 WHERE book_id = :book_id;";
    QSqlQuery query;
    QSqlQuery update;

    query.prepare(insert_borrowed);
    update.prepare(update_books);
    query.bindValue(":user_id", user_id);

    ui->list2->showRow(0);

    while (row < total) {
        QString book_id = ui->list2->item(row, 0)->text();
        query.bindValue(":book_id", book_id);
        update.bindValue(":book_id", book_id);
        query.exec();
        update.exec();
        row++;
    }

    ui->list2->hideRow(0);

    QString book = "Book Successfully Checked Out";
    QString books = "Books Successfully Checked Out";

    if (total == 1) {
        QMessageBox::information(this,"Check-Out", book);
    }

    else if (total > 1) {
        QMessageBox::information(this,"Check-Out", books);
    }

    ui->list2->setRowCount(0);
    populate_existingbooks();

    QSqlQuery query_size;
    query_size.exec("SELECT COUNT (*) FROM books WHERE quantity > 0;");
    query_size.first();
    int count = query_size.value(0).toInt();
    ui->list1->setRowCount(count);
    ui->list1->setColumnCount(4);
    populate_booktable();
}

void userpage::background_setup()
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
}

void userpage::button_setup()
{
    ui->details_name->setEnabled(false);
    ui->details_phone->setEnabled(false);
    ui->details_address->setEnabled(false);
    ui->details_email->setEnabled(false);
    ui->details_password->setEnabled(false);

    //button style
    QPixmap up("://images/add2.png");
    QIcon ButtonIcon(up);
    ui->addBookBtn->setIcon(ButtonIcon);
    ui->addBookBtn->setIconSize(QSize(65, 65));

    QPixmap up1("://images/remove3.png");
    QIcon ButtonIcon1(up1);
    ui->removeBookBtn->setIcon(ButtonIcon1);
    ui->removeBookBtn->setIconSize(QSize(65, 65));

    QPixmap up2("://images/back.png");
    QIcon ButtonIcon2(up2);
    ui->logoutBtn->setIcon(ButtonIcon2);
    ui->logoutBtn->setIconSize(QSize(50, 50));

    QPixmap up3("://images/contact_us.png");
    QIcon ButtonIcon3(up3);
    ui->contactBtn->setIcon(ButtonIcon3);
    ui->contactBtn->setIconSize(QSize(75, 75));

    QPixmap up4("://images/books_logo.png");
    QIcon ButtonIcon4(up4);
    ui->booksBtn->setIcon(ButtonIcon4);
    ui->booksBtn->setIconSize(QSize(100, 100));

    QPixmap up5("://images/your_account.png");
    QIcon ButtonIcon5(up5);
    ui->accountBtn->setIcon(ButtonIcon5);
    ui->accountBtn->setIconSize(QSize(65, 65));

    QPixmap up6("://images/submit.png");
    QIcon ButtonIcon6(up6);
    ui->submitBtn->setIcon(ButtonIcon6);
    ui->submitBtn->setIconSize(QSize(100, 100));

    QPixmap up7("://images/checkout.png");
    QIcon ButtonIcon7(up7);
    ui->checkoutBtn->setIcon(ButtonIcon7);
    ui->checkoutBtn->setIconSize(QSize(80, 80));

    QPixmap up8("://images/edit.png");
    QIcon ButtonIcon8(up8);
    ui->editBtn->setIcon(ButtonIcon8);
    ui->editBtn->setIconSize(QSize(50, 50));

    QPixmap up9("://images/save.png");
    QIcon ButtonIcon9(up9);
    ui->saveBtn->setIcon(ButtonIcon9);
    ui->saveBtn->setIconSize(QSize(50, 50));

    QPixmap up10("://images/return.png");
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
    borrowed_header << "Book ID" << "Title" << "Author" << "Due Date";
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

    ui->list1->setSortingEnabled(true);
    ui->list2->setSortingEnabled(true);
    ui->existing_books->setSortingEnabled(true);
}

void userpage::file_function()
{
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
    file.resize(0);
}

void userpage::size_of_lists()
{
    QSqlQuery query_size;
    query_size.exec("SELECT COUNT (*) FROM books WHERE quantity > 0;");
    query_size.first();
    int count = query_size.value(0).toInt();
    ui->list1->setRowCount(count);
    ui->list1->setColumnCount(4);
    ui->list2->setRowCount(0);
    ui->list2->setColumnCount(4);
}

void userpage::populate_booktable()
{
    int row = 0;
    QSqlQuery query;
    query.exec("SELECT * FROM books WHERE quantity > 0;");
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

void userpage::populate_details()
{
    QSqlQuery query;
    QString select = "SELECT * FROM users WHERE user_id = :user_id;";
    query.prepare(select);
    query.bindValue(":user_id", user_id);
    query.exec();
    query.first();

    ui->details_name->setText(query.value(1).toString());
    ui->userpage_title->setText("Hi " + query.value(1).toString());
    ui->details_phone->setText(query.value(2).toString());
    ui->details_address->setText(query.value(3).toString());
    ui->details_email->setText(query.value(4).toString());
    ui->details_password->setText(query.value(5).toString());
}

void userpage::populate_existingbooks()
{
    ui->existing_books->setRowCount(0);
    QSqlQuery query;
    QString borrowed_count = "SELECT COUNT (*) FROM borrowed_books WHERE user_id = :user_id AND returned_status = 'no';";
    query.prepare(borrowed_count);
    query.bindValue(":user_id", user_id);
    query.exec();
    query.first();
    int count1 = query.value(0).toInt();

    int row1 = 0;
    ui->existing_books->setRowCount(count1);
    ui->existing_books->setColumnCount(4);

    QString borrowed_query = "SELECT books.book_id, books.title, books.author, strftime('%d/%m/%Y',due_date) from borrowed_books JOIN books where user_id = :user_id AND borrowed_books.book_id = books.book_id AND returned_status = 'no';";
    query.prepare(borrowed_query);
    query.bindValue(":user_id", user_id);
    query.exec();

    while (query.next()) {
        QTableWidgetItem *book_id = new QTableWidgetItem();
        QTableWidgetItem *title = new QTableWidgetItem();
        QTableWidgetItem *author = new QTableWidgetItem();
        QTableWidgetItem *due_date = new QTableWidgetItem();

        book_id->setText(query.value(0).toString());
        ui->existing_books->setItem(row1, 0, book_id);
        title->setText(query.value(1).toString());
        ui->existing_books->setItem(row1, 1, title);
        author->setText(query.value(2).toString());
        ui->existing_books->setItem(row1, 2, author);
        due_date->setText(query.value(3).toString());
        ui->existing_books->setItem(row1, 3, due_date);
        row1++;
    }
}

void userpage::on_returnBtn_clicked()
{
    //1 check to make sure an item is selected
    if (!ui->existing_books->selectedItems().empty()) {
        //2 remove book from borrowed_book table
        ui->existing_books->showRow(0);
        QString book_id = ui->existing_books->item(ui->existing_books->currentRow(), 0)->text();
        ui->existing_books->hideRow(0);

        //then SQL query to remove the borrowed_books entry
//        QSqlQuery query;
//        QString remove = "DELETE FROM borrowed_books WHERE user_id = :user_id AND book_id = :book_id;";
//        query.prepare(remove);
//        query.bindValue(":user_id", user_id);
//        query.bindValue(":book_id", book_id);
//        query.exec();

        //instead of remove the borrowed book i need to update the status
        QSqlQuery query;
        QString remove = "UPDATE borrowed_books SET returned_status = 'yes', returned_date = CURRENT_DATE WHERE user_id = :user_id AND book_id = :book_id;";
        query.prepare(remove);
        query.bindValue(":user_id", user_id);
        query.bindValue(":book_id", book_id);
        query.exec();

        //SQL query to increase quantity in books table
        QString update_books = "UPDATE books SET quantity = quantity + 1 WHERE book_id = :book_id;";
        query.prepare(update_books);
        query.bindValue(":book_id", book_id);
        query.exec();
        size_of_lists();
        populate_booktable();

        //4 call populate_existingbooks to refresh
        populate_existingbooks();

        QString book = "Book Successfully Returned";
        QMessageBox::information(this,"Return", book);
    }
}

void userpage::on_addBookBtn_clicked()
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

        ui->list1->removeRow(ui->list1->currentRow());

        //quantity check
        QSqlQuery query_size;
        query_size.exec("SELECT COUNT (*) FROM books WHERE quantity > 0;");
        query_size.first();
        int count = query_size.value(0).toInt();
        ui->list1->setRowCount(count);

        int row = 0;
        QSqlQuery query;
        query.exec("SELECT * FROM books WHERE quantity > 0;");
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
}

void userpage::on_removeBookBtn_clicked()
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

