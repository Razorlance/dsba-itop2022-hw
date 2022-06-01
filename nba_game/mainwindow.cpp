#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "players_list.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      _players(new players_list(this)),
      _team_window(new team_window(this))
{
    ui->setupUi(this);
    ui->table->verticalHeader()->setVisible(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_add_button_clicked() {}

void MainWindow::on_team_button_clicked() { _team_window->show(); }

void MainWindow::on_delete_button_clicked() {}

void MainWindow::on_search_button_clicked() {}

void MainWindow::on_actionOpen_triggered()
{
    QStandardItemModel *model = new QStandardItemModel;
    ui->table->setModel(model);
    //_players->loadFile("D:/Projects/dsba-itop2022-hw/all_seasons.csv");
    QFile file = QFileDialog::getOpenFileName(
        this,         // parent, is needed to restrict focus of the dlg
        "Open File",  // caption — is shown in the main title of the dlg
        "",           // start directory
        "Text files (*.csv);;All files (*.*)");  // mask which is used for
                                                 // filtering files by their
                                                 // extensions

    QFileDialog fd(this, "Open a file", "", "Text Files (*.csv)");
    fd.show();
    fd.exec();
    // QFile file("D:/Projects/dsba-itop2022-hw/all_seasons.csv");
    if (file.open(QIODevice::ReadOnly))
    {
        size_t lineindex = 0;
        QTextStream in(&file);
        QString fileLine = in.readLine();
        QStringList lineToken = fileLine.split(",", Qt::SkipEmptyParts);
        model->setHorizontalHeaderLabels(lineToken);
        while (!in.atEnd())
        {
            fileLine = in.readLine();
            lineToken = fileLine.split(",", Qt::SkipEmptyParts);
            for (int j = 0; j < lineToken.size(); j++)
            {
                QString value = lineToken.at(j);
                QStandardItem *item = new QStandardItem(value);
                model->setItem(lineindex, j, item);
            }
            lineindex++;
        }
        file.close();
    }
}

void MainWindow::on_table_customContextMenuRequested(const QPoint &pos) {}
