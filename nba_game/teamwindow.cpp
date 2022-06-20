#include "teamwindow.h"

#include "ui_teamwindow.h"

TeamWindow::TeamWindow(PlayersList *players, TeamTable *_teamTable,
                       QWidget *parent)
    : QDialog(parent),
      ui(new Ui::teamWindow),
      _players(players),
      _tTable(_teamTable),
      _menu(new QMenu(this))
{
    ui->setupUi(this);
    _tTable->layoutAboutToBeChanged();
    ui->team_table->verticalHeader()->setVisible(true);
    ui->team_table->setContextMenuPolicy(Qt::CustomContextMenu);
    _tTable->layoutChanged();
    ui->team_name->setText(_players->getTeamName());
    ui->team_ast->setText(QString::number(_players->countAST()));
    ui->team_reb->setText(QString::number(_players->countREB()));
    ui->team_pts->setText(QString::number(_players->countPTS()));
    QAction *deletePlayer = new QAction("Delete from team", this);
    connect(deletePlayer, SIGNAL(triggered()), this, SLOT(deletePlayer()));
    connect(ui->team_table, SIGNAL(customContextMenuRequested(QPoint)), this,
            SLOT(slotCustomMenuRequested(QPoint)));
    _menu->addAction(deletePlayer);
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(_tTable);
    ui->team_table->setModel(proxyModel);
    ui->team_table->setSortingEnabled(true);
}

TeamWindow::~TeamWindow() { delete ui; }

void TeamWindow::on_pushButton_clicked()
{
    QString name = ui->team_name->text();
    _players->changeTeamName(name);
    ui->team_name->setText(_players->getTeamName());
    ui->team_ast->setText(QString::number(_players->countAST()));
    ui->team_reb->setText(QString::number(_players->countREB()));
    ui->team_pts->setText(QString::number(_players->countPTS()));
    _tTable->layoutAboutToBeChanged();
    this->close();
    _tTable->layoutChanged();
}

void TeamWindow::on_update_button_clicked()
{
    _tTable->layoutAboutToBeChanged();
    _tTable->layoutChanged();
    ui->team_ast->setText(QString::number(_players->countAST()));
    ui->team_reb->setText(QString::number(_players->countREB()));
    ui->team_pts->setText(QString::number(_players->countPTS()));
}

void TeamWindow::on_save_button_clicked()
{
    QString name = ui->team_name->text();
    _players->changeTeamName(name);
}

void TeamWindow::deletePlayer()
{
    size_t index = ui->team_table->selectionModel()->selectedRows().at(0).row();
    size_t id = ui->team_table->model()
                    ->data(ui->team_table->model()->index(index, 0))
                    .toInt();
    _tTable->layoutAboutToBeChanged();
    _players->deleteFromTeam(id);
    _tTable->layoutChanged();
}

void TeamWindow::slotCustomMenuRequested(QPoint pos)
{
    _menu->popup(ui->team_table->viewport()->mapToGlobal(pos));
}

void TeamWindow::on_team_table_customContextMenuRequested(const QPoint &pos)
{
    _menu->popup(ui->team_table->viewport()->mapToGlobal(pos));
}
