#include "adminpage.h"
#include "ui_adminpage.h"

adminpage::adminpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminpage)
{
    ui->setupUi(this);
    background_setup();
    button_setup();
}

adminpage::~adminpage()
{
    delete ui;
}

void adminpage::background_setup()
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

void adminpage::button_setup()
{

    QPixmap up("://images/add2.png");
    QIcon ButtonIcon(up);
    ui->addBtn->setIcon(ButtonIcon);
    ui->addBtn->setIconSize(QSize(65, 65));

    QPixmap up1("://images/remove3.png");
    QIcon ButtonIcon1(up1);
    ui->removeBtn->setIcon(ButtonIcon1);
    ui->removeBtn->setIconSize(QSize(65, 65));

    QPixmap up2("://images/back.png");
    QIcon ButtonIcon2(up2);
    ui->logoutBtn->setIcon(ButtonIcon2);
    ui->logoutBtn->setIconSize(QSize(50, 50));

    QPixmap up3("://images/contact_us.png");
    QIcon ButtonIcon3(up3);
    ui->enquiryBtn->setIcon(ButtonIcon3);
    ui->enquiryBtn->setIconSize(QSize(75, 75));

    QPixmap up4("://images/books_logo.png");
    QIcon ButtonIcon4(up4);
    ui->booksBtn->setIcon(ButtonIcon4);
    ui->booksBtn->setIconSize(QSize(100, 100));

    QPixmap up5("://images/your_account.png");
    QIcon ButtonIcon5(up5);
    ui->userBtn->setIcon(ButtonIcon5);
    ui->userBtn->setIconSize(QSize(65, 65));

    QPixmap up6("://images/report.png");
    QIcon ButtonIcon6(up6);
    ui->reportBtn->setIcon(ButtonIcon6);
    ui->reportBtn->setIconSize(QSize(65, 65));

    QPixmap up10("://images/return.png");
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
    ui->view->reset();
    model = new QSqlTableModel;
    model->setTable("users");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("User ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Phone"));
    model->setHeaderData(3, Qt::Horizontal, tr("Address"));
    model->setHeaderData(4, Qt::Horizontal, tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, tr("Password"));
    model->setHeaderData(6, Qt::Horizontal, tr("Role"));
    ui->view->setModel(model);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);

    //setting the style for the list items
    ui->view->setStyleSheet
            ("QListView { font-size: 12pt; }"
             "QListView::item { background-color: #FBDED8; "
             "border: 1px solid #000000; }"
             "QListView::item::selected { background-color: #FBDED8 }"
             "QListView::item::selected { color: #000000 }");
}

void adminpage::on_enquiryBtn_clicked()
{
    ui->view->reset();
    model = new QSqlTableModel;
    model->setTable("enquiry");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Enquiry ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, tr("Phone"));
    model->setHeaderData(3, Qt::Horizontal, tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, tr("Details"));
    model->setHeaderData(5, Qt::Horizontal, tr("Time"));
    model->setHeaderData(6, Qt::Horizontal, tr("Date"));
    model->setHeaderData(5, Qt::Horizontal, tr("Resolved"));
    model->setHeaderData(6, Qt::Horizontal, tr("Resolved Date"));
    ui->view->setModel(model);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->view->verticalHeader()->setVisible(false);

    //setting the style for the list items
    ui->view->setStyleSheet
            ("QListView { font-size: 12pt; }"
             "QListView::item { background-color: #FBDED8; "
             "border: 1px solid #000000; }"
             "QListView::item::selected { background-color: #FBDED8 }"
             "QListView::item::selected { color: #000000 }");
}

void adminpage::on_borrowedBtn_clicked()
{
    ui->view->reset();
    model = new QSqlTableModel;
    model->setTable("borrowed_books");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Borrowed ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("User ID"));
    model->setHeaderData(2, Qt::Horizontal, tr("Book ID"));
    model->setHeaderData(3, Qt::Horizontal, tr("Date Borrowed"));
    model->setHeaderData(4, Qt::Horizontal, tr("Time Borrowed"));
    model->setHeaderData(5, Qt::Horizontal, tr("Due Date"));
    ui->view->setModel(model);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->view->verticalHeader()->setVisible(false);

    //setting the style for the list items
    ui->view->setStyleSheet
            ("QListView { font-size: 12pt; }"
             "QListView::item { background-color: #FBDED8; "
             "border: 1px solid #000000; }"
             "QListView::item::selected { background-color: #FBDED8 }"
             "QListView::item::selected { color: #000000 }");
}

void adminpage::on_booksBtn_clicked()
{
    ui->view->reset();
    model = new QSqlTableModel;
    model->setTable("books");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Book ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Description"));
    model->setHeaderData(4, Qt::Horizontal, tr("Quantity"));
    ui->view->setModel(model);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);

    //setting the style for the list items
    ui->view->setStyleSheet
            ("QListView { font-size: 12pt; }"
             "QListView::item { background-color: #FBDED8; "
             "border: 1px solid #000000; }"
             "QListView::item::selected { background-color: #FBDED8 }"
             "QListView::item::selected { color: #000000 }");
}

void adminpage::on_addBtn_clicked()
{
    int row = model->rowCount();
    model->insertRow(row);
}

void adminpage::on_removeBtn_clicked()
{
    if (ui->view->currentIndex().isValid()) {
        qDebug() << "Row Removed";
        int row = ui->view->selectionModel()->currentIndex().row();
        model->removeRow(row);
        ui->view->hideRow(row);
    }
}

void adminpage::on_reportBtn_clicked()
{
    //perhaps show/generate some kind of report
}


