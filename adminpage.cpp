#include "adminpage.h"
#include "ui_adminpage.h"

adminpage::adminpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminpage)
{
    ui->setupUi(this);
    background_setup();
    button_setup();
    file_function();
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
    table = "user";
    ui->addLbl->setText("Add User");
    ui->removeLbl->setText("Remove User");
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
    //ui->view->setModel(model);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->view->setModel(proxyModel);

    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);
    ui->view->setSortingEnabled(true);

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
    table = "enquiry";
    ui->addLbl->setText("Add Enquiry");
    ui->removeLbl->setText("Remove Enquiry");
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
    model->setHeaderData(7, Qt::Horizontal, tr("Resolved"));
    model->setHeaderData(8, Qt::Horizontal, tr("Resolved Date"));
    //ui->view->setModel(model);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->view->setModel(proxyModel);

    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);
    ui->view->setSortingEnabled(true);

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
    table = "borrowed_books";
    ui->addLbl->setText("Add Entry");
    ui->removeLbl->setText("Remove Entry");
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
    //ui->view->setModel(model);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->view->setModel(proxyModel);

    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);
    ui->view->setSortingEnabled(true);

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
    table = "books";
    ui->addLbl->setText("Add Book");
    ui->removeLbl->setText("Remove Book");
    ui->view->reset();
    model = new QSqlTableModel;
    model->setTable("books");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, tr("Book ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Title"));
    model->setHeaderData(2, Qt::Horizontal, tr("Author"));
    model->setHeaderData(3, Qt::Horizontal, tr("Description"));
    //model->setHeaderData(4, Qt::Horizontal, tr("Quantity"));
    ui->view->setModel(model);
    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);

    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->view->setModel(proxyModel);

    ui->view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->view->verticalHeader()->setVisible(false);
    ui->view->setSortingEnabled(true);

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

        if (table == "user") {
            on_userBtn_clicked();
        }

        else if (table == "enquiry") {
            on_enquiryBtn_clicked();
        }

        else if (table == "borrowed_books") {
            on_borrowedBtn_clicked();
        }

        else if (table == "books") {
            on_booksBtn_clicked();
        }

    }
}

void adminpage::on_reportBtn_clicked()
{
    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *model =  ui->view->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream data(&file);
        QStringList strList;
        for (int i = 0; i < model->columnCount(); i++) {
            if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
            else
                strList.append("");
        }
        data << strList.join(",") << "\n";
        for (int i = 0; i < model->rowCount(); i++) {
            strList.clear();
            for (int j = 0; j < model->columnCount(); j++) {

                if (model->data(model->index(i, j)).toString().length() > 0)
                    strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                else
                    strList.append("");
            }
            data << strList.join(",") << "\n";
        }
        file.close();
    }
}

void adminpage::file_function()
{
    QString filename = "user_id.txt";
    QFile file(filename);

    qInfo() << "Exists:" << file.exists();

    if(file.open(QIODevice::ReadOnly))
    {
        adminpage::user_id = file.readAll();
        file.close();
    }
    else
    {
        qInfo() << file.errorString();
    }
    QSqlQuery query;
    QString select = "SELECT * FROM users WHERE user_id = :user_id;";
    query.prepare(select);
    query.bindValue(":user_id", user_id);
    query.exec();
    query.first();

    ui->adminpage_title->setText("Hi " + query.value(1).toString());
}


