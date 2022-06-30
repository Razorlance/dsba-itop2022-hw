#ifndef TEAMLIST_H
#define TEAMLIST_H

#include <QAction>
#include <QDialog>
#include <QInputDialog>
#include <QMenu>
#include <QStringListModel>
#include <QWidget>

#include "playerslist.h"
#include "teamstable.h"
#include "tournamentwindow.h"

namespace Ui
{
class TeamList;
}

class TeamList : public QDialog
{
    Q_OBJECT

   public:
    explicit TeamList(PlayersList *players, TeamsTable *_teamsTableModel,
                      QMenu *_menu, QWidget *parent = nullptr);
    ~TeamList();

   private slots:

    void newTeam();

    void deleteTeam();

    void deleteFromTeam();

    void on_okButton_clicked();

    void on_teamlist_customContextMenuRequested(const QPoint &pos);

    void on_teamlist_clicked(const QModelIndex &index);

    void on_saveButton_clicked();

    void on_tournamentButton_clicked();

    void on_playersTable_customContextMenuRequested(const QPoint &pos);

   private:
    Ui::TeamList *ui;
    PlayersList *_players;
    QStringListModel *_teamsListModel;
    TeamsTable *_teamsTableModel;
    TournamentWindow *_tournamentWindow;
    QMenu *_menu;
    QMenu *_tableMenu;
    QMenu *_teamsMenu;
};

#endif  // TEAMLIST_H
