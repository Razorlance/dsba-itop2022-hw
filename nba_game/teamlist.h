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

    void on_okButton_clicked();

    void on_teamlist_customContextMenuRequested(const QPoint &pos);

    void on_teamlist_clicked(const QModelIndex &index);

    void on_saveButton_clicked();

    void on_tournamentButton_clicked();

   private:
    Ui::TeamList *ui;
    PlayersList *_players;
    QStringListModel *_teamsListModel;
    TeamsTable *_teamsTableModel;
    QMenu *_menu;
    QMenu *_teamsMenu;
};

#endif  // TEAMLIST_H
