#ifndef TOURNAMENTWINDOW_H
#define TOURNAMENTWINDOW_H

#include <QDialog>

#include "playerslist.h"
#include "teamstable.h"

namespace Ui
{
class TournamentWindow;
}

class TournamentWindow : public QDialog
{
    Q_OBJECT

   public:
    explicit TournamentWindow(PlayersList *_players, QString team1,
                              QString team2, QWidget *parent = nullptr);
    ~TournamentWindow();
    void setTeam1(QString);
    void setTeam2(QString);
    void update();

   private slots:
    void on_playButton_clicked();

   private:
    Ui::TournamentWindow *ui;
    TeamsTable *teamTable1Model;
    TeamsTable *teamTable2Model;
    PlayersList *_players;
    QString team1;
    QString team2;
};

#endif  // TOURNAMENTWINDOW_H
