#include "team_window.h"

#include "ui_team_window.h"

team_window::team_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::team_window)
{
    ui->setupUi(this);
}

team_window::~team_window() { delete ui; }

void team_window::on_pushButton_clicked() { this->close(); }
