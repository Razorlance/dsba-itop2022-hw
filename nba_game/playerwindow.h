#ifndef PLAYERWINDOW_H
#define PLAYERWINDOW_H

#include <QWidget>

#include "playerslist.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class playerWindow;
}
QT_END_NAMESPACE

class PlayerWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit PlayerWindow(PlayersList *players, size_t id,
                          QWidget *parent = nullptr);
    ~PlayerWindow();

   private slots:

    void on_close_button1_clicked();

   private:
    Ui::playerWindow *ui;
    PlayersList *_players;
    size_t id;
};

#endif  // PLAYERWINDOW_H
