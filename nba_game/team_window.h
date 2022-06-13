#ifndef TEAM_WINDOW_H
#define TEAM_WINDOW_H

#include <QDialog>
#include <QList>
#include <QMenu>
#include <QSortFilterProxyModel>

#include "players_list.h"
#include "team_table.h"

namespace Ui
{
class team_window;
}

class team_window : public QDialog
{
    Q_OBJECT

   public:
    explicit team_window(players_list *players, QWidget *parent = nullptr);

    ~team_window();

   private slots:
    void on_pushButton_clicked();

    void on_update_button_clicked();

    void on_save_button_clicked();

    void deletePlayer();

    void slotCustomMenuRequested(QPoint);

    void on_team_table_customContextMenuRequested(const QPoint &pos);

   private:
    Ui::team_window *ui;
    team_table *_tTable;
    players_list *_players;
    QMenu *_menu;
};

#endif  // TEAM_WINDOW_H
