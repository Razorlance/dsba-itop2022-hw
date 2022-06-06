#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "players_list.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _players(new players_list(this)),
      _mtable(new main_table(_players, this)),
      _team_window(new team_window(this))
{
    ui->setupUi(this);
    ui->table->setModel(_mtable);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->table, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(slotCustomMenuRequested(QPoint)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_add_button_clicked() {}

void MainWindow::on_team_button_clicked() { _team_window->show(); }

void MainWindow::on_delete_button_clicked() {}

void MainWindow::on_search_button_clicked() {}

void MainWindow::on_actionOpen_triggered()
{
    QFile file = QFileDialog::getOpenFileName(
        this,         // parent, is needed to restrict focus of the dlg
        "Open File",  // caption — is shown in the main title of the dlg
        "",           // start directory
        "Text files (*.csv);;All files (*.*)");  // mask which is used for
                                                 // filtering files by their
                                                 // extensions
    QFileDialog fd(this, "Open a file", "", "Text Files (*.csv)");
    fd.exec();
    fd.show();

    _mtable->layoutAboutToBeChanged();
    _players->loadFile(file);
    _mtable->layoutChanged();
    // qDebug() << _players->getHeaders();
}

void MainWindow::on_table_customContextMenuRequested(const QPoint& pos)
{
    QMenu* menu = new QMenu(this);
    //    menu.addAction("Add to the team");
    //    menu.addAction("Edit");
    //    menu.addAction("Delete");
    /* Create actions to the context menu */
    QAction* editDevice = new QAction("Edit", this);
    QAction* deleteDevice = new QAction("Delete", this);
    /* Connect slot handlers for Action pop-up menu */
    menu->addAction(editDevice);
    menu->addAction(deleteDevice);
    connect(editDevice, SIGNAL(triggered()), this, SLOT(slotEditRecord()));
    menu->popup(ui->table->viewport()->mapToGlobal(pos));
}
