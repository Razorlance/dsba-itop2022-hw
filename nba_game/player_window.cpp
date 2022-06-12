#include "player_window.h"

#include "ui_player_window.h"

player_window::player_window(QWidget *parent)
    : QWidget(parent), ui(new Ui::player_window)
{
    ui->setupUi(this);
}

player_window::~player_window() { delete ui; }

void player_window::on_pushButton_clicked() {}

void player_window::on_pushButton_2_clicked() {}
