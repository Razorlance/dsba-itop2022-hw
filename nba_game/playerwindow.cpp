#include "playerwindow.h"

#include "ui_playerwindow.h"

PlayerWindow::PlayerWindow(PlayersList* players, size_t id, QWidget* parent)
    : QDialog(parent), ui(new Ui::playerWindow), _players(players)
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

PlayerWindow::~PlayerWindow() { delete ui; }

void PlayerWindow::on_close_button1_clicked() { this->close(); }
