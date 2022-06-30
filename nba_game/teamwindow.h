#ifndef TEAMWINDOW_H
#define TEAMWINDOW_H

#include <QDialog>
#include <QList>
#include <QMenu>
#include <QSortFilterProxyModel>

#include "playerslist.h"
#include "teamtable.h"

namespace Ui
{
class teamWindow;
}

class TeamWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit TeamWindow(PlayersList *players, TeamTable *_tTable,
                        QWidget *parent = nullptr);

    ~TeamWindow();

   private slots:
    void on_pushButton_clicked();

    void on_update_button_clicked();

    void on_save_button_clicked();

    void deletePlayer();

    void slotCustomMenuRequested(QPoint);

    void on_team_table_customContextMenuRequested(const QPoint &pos);

   private:
    void setUp();
    Ui::teamWindow *ui;
    TeamTable *_tTable;
    PlayersList *_players;
    QMenu *_menu;
};

#endif  // TEAMWINDOW_H
