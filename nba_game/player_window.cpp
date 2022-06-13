#include "player_window.h"

#include "ui_player_window.h"

player_window::player_window(players_list* players, size_t id, QWidget* parent)
    : QDialog(parent), ui(new Ui::player_window), _players(players)
{
    ui->setupUi(this);
    Player p = players->getPlayer(id);
    ui->name_field->setText(p.name);
    ui->team_field->setText(p.team);
    ui->age_field->setText(QString::number(p.age));
    ui->year_field->setText(p.year);
    ui->height_field->setText(QString::number(p.height));
    ui->weight_field->setText(QString::number(p.weight));
}

player_window::~player_window() { delete ui; }

void player_window::on_pushButton_clicked() {}

void player_window::on_pushButton_2_clicked() {}
