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
      _proxyModel(new QSortFilterProxyModel(this)),
      _help_window(new help_window(this))
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
    //    QAction* deletePlayer = new QAction("Delete", this);
    connect(addToTeam, SIGNAL(triggered()), this, SLOT(addToTeam()));
    connect(editPlayer, SIGNAL(triggered()), this, SLOT(editPlayer()));
    //    connect(deletePlayer, SIGNAL(triggered()), this,
    //    SLOT(deletePlayer()));
    _menu->addAction(addToTeam);
    _menu->addAction(editPlayer);
    //    _menu->addAction(deletePlayer);
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
    size_t index = ui->table->selectionModel()->selectedRows().at(0).row();
    size_t id =
        ui->table->model()->data(ui->table->model()->index(index, 0)).toInt();
    _players->addToTeam(id);
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
    size_t id =
        ui->table->model()->data(ui->table->model()->index(index, 0)).toInt();
    _proxyModel->layoutAboutToBeChanged();
    _players->deletePlayer(id);
    _proxyModel->layoutChanged();
}

void MainWindow::on_table_customContextMenuRequested(QPoint pos)
{
    _menu->popup(ui->table->viewport()->mapToGlobal(pos));
}

void MainWindow::on_table_doubleClicked(const QModelIndex& indx)
{
    size_t index = ui->table->selectionModel()->selectedRows().at(0).row();
    size_t id =
        ui->table->model()->data(ui->table->model()->index(index, 0)).toInt();
    player_window* pWindow = new player_window(_players, id, this);
    pWindow->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->search_input->setText("");
    _proxyModel->layoutAboutToBeChanged();
    _proxyModel->setFilterKeyColumn(1);
    _proxyModel->setFilterRegularExpression(QRegularExpression(
        ui->search_input->text(), QRegularExpression::CaseInsensitiveOption));
    _proxyModel->layoutChanged();
}

void MainWindow::on_compare_button_clicked()
{
    if (ui->table->selectionModel()->selectedRows().size() == 2)
    {
        size_t index1 = ui->table->selectionModel()->selectedRows().at(0).row();
        size_t id1 = ui->table->model()
                         ->data(ui->table->model()->index(index1, 0))
                         .toInt();
        size_t index2 = ui->table->selectionModel()->selectedRows().at(1).row();
        size_t id2 = ui->table->model()
                         ->data(ui->table->model()->index(index2, 0))
                         .toInt();
        compare_window* cWindow = new compare_window(_players, id1, id2, this);
        cWindow->show();
    }
}

void MainWindow::on_help_button_clicked() { _help_window->show(); }
