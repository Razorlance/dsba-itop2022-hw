#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpressionMatch>
#include <QStandardItemModel>
#include <QTableView>

#include "comparewindow.h"
#include "helpwindow.h"
#include "maintable.h"
#include "playerslist.h"
#include "playerwindow.h"
#include "teamlist.h"
#include "teamstable.h"
#include "teamtable.h"
#include "teamwindow.h"

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

    void addToSelectedTeam();

    void deletePlayer();

    void slotCustomMenuRequested(QPoint);

    void on_team_button_clicked();

    void on_search_button_clicked();

    void on_actionOpen_triggered();

    void on_table_customContextMenuRequested(QPoint pos);

    void on_table_doubleClicked(const QModelIndex &index);

    void on_pushButton_2_clicked();

    void on_compare_button_clicked();

    void on_help_button_clicked();

    void on_teamsButton_clicked();

   protected:
    PlayersList *_players;
    MainTable *_mtable;
    TeamTable *_teamTable;

    TeamWindow *_teamWindow;
    TeamsTable *_teamsTable;
    PlayerWindow *_playerWindow;
    HelpWindow *_helpWindow;
    CompareWindow *_compareWindow;
    TeamList *_teamsWindow;
    QMenu *_menu;
    QSortFilterProxyModel *_proxyModel;

   private:
    Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
