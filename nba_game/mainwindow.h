#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QRegularExpressionMatch>
#include <QStandardItemModel>
#include <QTableView>

#include "main_table.h"
#include "player_window.h"
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
    void addToTeam();

    void editPlayer();

    void deletePlayer();

    void slotCustomMenuRequested(QPoint);

    void on_team_button_clicked();

    void on_search_button_clicked();

    void on_actionOpen_triggered();

    void on_table_customContextMenuRequested(QPoint pos);

    void on_table_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

   protected:
    players_list *_players;
    main_table *_mtable;

    team_window *_team_window;
    player_window *_player_window;

    QMenu *_menu;
    QSortFilterProxyModel *_proxyModel;

   private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
