#include "compare_window.h"

#include "ui_compare_window.h"

compare_window::compare_window(players_list *players, size_t id1, size_t id2,
                               QWidget *parent)
    : QDialog(parent), ui(new Ui::compare_window)
{
    ui->setupUi(this);
    Player p1 = players->getPlayer(id1);
    Player p2 = players->getPlayer(id2);
    ui->age_field->setText(QString::number(p1.age));
    ui->age_field_2->setText(QString::number(p2.age));
    ui->name_field->setText(p1.name);
    ui->name_field_2->setText(p2.name);
    ui->team_field->setText(p1.team);
    ui->team_field_2->setText(p2.team);
    ui->weight_field->setText(QString::number(p1.weight));
    ui->weight_field_2->setText(QString::number(p2.weight));
    ui->height_field->setText(QString::number(p1.height));
    ui->height_field_2->setText(QString::number(p2.height));
    ui->year_field->setText(p1.year);
    ui->year_field_2->setText(p2.year);
}

compare_window::~compare_window() { delete ui; }

void compare_window::on_close_button_clicked() { this->close(); }
