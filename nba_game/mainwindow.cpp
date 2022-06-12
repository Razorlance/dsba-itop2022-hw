#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "players_list.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _players(new players_list(this)),
      _mtable(new main_table(_players, this)),
      _team_window(new team_window(_players, this)),
      _menu(new QMenu(this)),
      _proxyModel(new QSortFilterProxyModel(this))
{
    ui->setupUi(this);
    //    ui->table->setModel(_mtable);
    _proxyModel->setSourceModel(_mtable);
    ui->table->setModel(_proxyModel);
    ui->table->setSortingEnabled(true);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setContextMenuPolicy(Qt::CustomContextMenu);
    QAction* addToTeam = new QAction("Add to team", this);
    QAction* editPlayer = new QAction("Edit", this);
    QAction* deletePlayer = new QAction("Delete", this);
    connect(addToTeam, SIGNAL(triggered()), this, SLOT(addToTeam()));
    connect(editPlayer, SIGNAL(triggered()), this, SLOT(editPlayer()));
    connect(deletePlayer, SIGNAL(triggered()), this, SLOT(deletePlayer()));
    _menu->addAction(addToTeam);
    _menu->addAction(editPlayer);
    _menu->addAction(deletePlayer);
    connect(ui->table, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(slotCustomMenuRequested(QPoint)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::slotCustomMenuRequested(QPoint pos) {}

void MainWindow::on_team_button_clicked() { _team_window->show(); }

void MainWindow::on_search_button_clicked()
{
    _proxyModel->layoutAboutToBeChanged();
    _proxyModel->setFilterKeyColumn(1);
    _proxyModel->setFilterRegularExpression(QRegularExpression(
        ui->search_input->text(), QRegularExpression::CaseInsensitiveOption));
    _proxyModel->layoutChanged();
}

void MainWindow::on_actionOpen_triggered()
{
    QFile file = QFileDialog::getOpenFileName(this, "Open a file", "",
                                              "Text Files (*.csv)");
    _mtable->layoutAboutToBeChanged();
    _players->loadFile(file);
    _mtable->layoutChanged();
}

void MainWindow::addToTeam()
{
    QPoint p = ui->table->mapFromGlobal(QCursor::pos());
    size_t index = ui->table->indexAt(QPoint(p.x(), p.y())).row() - 1;
    qDebug() << index;
    _players->addToTeam(index);
}

void MainWindow::editPlayer()
{
    //    size_t index =
    //    ui->table->selectionModel()->selectedRows().at(0).data(); qDebug() <<
    //    index; size_t id = _players->getPlayer(index).id;
}

void MainWindow::deletePlayer()
{
    size_t index = ui->table->selectionModel()->selectedRows().at(0).row();
    qDebug() << index;
    size_t id = _players->getPlayer(index).id;
    _players->deletePlayer(id);
}

void MainWindow::on_table_customContextMenuRequested(QPoint pos)
{
    _menu->popup(ui->table->viewport()->mapToGlobal(pos));
}

void MainWindow::on_table_doubleClicked(const QModelIndex& index) {}
