#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "playerslist.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _players(new PlayersList(this)),
      _teamTable(new TeamTable(_players, this)),
      _mtable(new MainTable(_players, this)),
      _teamWindow(new TeamWindow(_players, _teamTable, this)),
      _menu(new QMenu(this)),
      _proxyModel(new QSortFilterProxyModel(this)),
      _helpWindow(new HelpWindow(this))
{
    ui->setupUi(this);
    _proxyModel->setSourceModel(_mtable);
    ui->table->setModel(_proxyModel);
    ui->table->setSortingEnabled(true);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setContextMenuPolicy(Qt::CustomContextMenu);
    QAction* addToTeam = new QAction("Add to team", this);
    connect(addToTeam, SIGNAL(triggered()), this, SLOT(addToTeam()));
    _menu->addAction(addToTeam);
    connect(ui->table, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(slotCustomMenuRequested(QPoint)));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::slotCustomMenuRequested(QPoint pos) {}

void MainWindow::on_team_button_clicked() { _teamWindow->show(); }

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
    _teamTable->layoutAboutToBeChanged();
    _players->addToTeam(id);
    _teamTable->layoutChanged();
    if (_players->getTeam().size() == 15)
    {
        QMessageBox msgBox;
        msgBox.setText("Maximum players in the team");
        msgBox.exec();
    }
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
    if (ui->table->selectionModel()->selectedRows().size() > 0)
        _menu->popup(ui->table->viewport()->mapToGlobal(pos));
}

void MainWindow::on_table_doubleClicked(const QModelIndex& indx)
{
    size_t index = ui->table->selectionModel()->selectedRows().at(0).row();
    size_t id =
        ui->table->model()->data(ui->table->model()->index(index, 0)).toInt();
    PlayerWindow* pWindow = new PlayerWindow(_players, id, this);
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
        CompareWindow* cWindow = new CompareWindow(_players, id1, id2, this);
        cWindow->show();
    }
}

void MainWindow::on_help_button_clicked() { _helpWindow->show(); }
