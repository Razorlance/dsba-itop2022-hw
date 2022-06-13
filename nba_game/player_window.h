#ifndef PLAYER_WINDOW_H
#define PLAYER_WINDOW_H

#include <QWidget>

#include "players_list.h"

namespace Ui
{
class player_window;
}

class player_window : public QDialog
{
    Q_OBJECT

   public:
    explicit player_window(players_list *players, size_t id,
                           QWidget *parent = nullptr);
    ~player_window();

   private slots:

    void on_close_button1_clicked();

   private:
    Ui::player_window *ui;
    players_list *_players;
    size_t id;
};

#endif  // PLAYER_WINDOW_H
