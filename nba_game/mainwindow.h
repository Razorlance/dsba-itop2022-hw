#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>

#include "players_list.h"
#include "team_window.h"
QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

   private slots:
    void on_add_button_clicked();

    void on_team_button_clicked();

    void on_delete_button_clicked();

    void on_search_button_clicked();

    void on_actionOpen_triggered();

   protected:
    players_list *_players;
    team_window *_team_window;

   private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
