#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_add_button_clicked() {}

void MainWindow::on_team_button_clicked() {}

void MainWindow::on_delete_button_clicked() {}

void MainWindow::on_search_button_clicked() {}
