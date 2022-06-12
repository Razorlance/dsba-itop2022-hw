#include "team_window.h"

#include "ui_team_window.h"

team_window::team_window(players_list *players, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::team_window),
      _players(players),
      _tTable(new team_table(players, this))
{
    ui->setupUi(this);
    ui->team_table->setModel(_tTable);
    _tTable->layoutAboutToBeChanged();
    ui->team_table->verticalHeader()->setVisible(false);
    ui->team_table->setContextMenuPolicy(Qt::CustomContextMenu);
    _tTable->layoutChanged();
    ui->team_name->setText(_players->getTeamName());
    ui->team_ast->setText(QString::number(_players->countAST()));
    ui->team_reb->setText(QString::number(_players->countREB()));
    ui->team_pts->setText(QString::number(_players->countPTS()));
}

team_window::~team_window() { delete ui; }

void team_window::on_pushButton_clicked()
{
    QString name = ui->team_name->text();
    _players->changeTeamName(name);
    _tTable->layoutAboutToBeChanged();
    this->close();
    _tTable->layoutChanged();
}

void team_window::on_update_button_clicked()
{
    _tTable->layoutAboutToBeChanged();
    _tTable->layoutChanged();
    ui->team_ast->setText(QString::number(_players->countAST()));
    ui->team_reb->setText(QString::number(_players->countREB()));
    ui->team_pts->setText(QString::number(_players->countPTS()));
}

void team_window::on_save_button_clicked()
{
    QString name = ui->team_name->text();
    _players->changeTeamName(name);
}
