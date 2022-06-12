#include "team_window.h"

#include "ui_team_window.h"

team_window::team_window(players_list *players, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::team_window),
      _tTable(new team_table(players, this))
{
    ui->setupUi(this);
    ui->team_table->setModel(_tTable);
    _tTable->layoutAboutToBeChanged();
    ui->team_table->verticalHeader()->setVisible(false);
    ui->team_table->setContextMenuPolicy(Qt::CustomContextMenu);
    _tTable->layoutChanged();
}

team_window::~team_window() { delete ui; }

void team_window::on_pushButton_clicked()
{
    _tTable->layoutAboutToBeChanged();
    this->close();
    _tTable->layoutChanged();
}
