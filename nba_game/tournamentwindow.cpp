#include "tournamentwindow.h"

#include "ui_tournamentwindow.h"

TournamentWindow::TournamentWindow(PlayersList *players, QString team1,
                                   QString team2, QWidget *parent)
    : QDialog(parent), _players(players), ui(new Ui::TournamentWindow)
{
    ui->setupUi(this);
    teamTable1Model = new TeamsTable(_players, this);
    teamTable2Model = new TeamsTable(_players, this);

    ui->teamTable1->setModel(teamTable1Model);
    teamTable1Model->setSelectedTeam(team1);
    ui->teamTable2->setModel(teamTable2Model);
    teamTable2Model->setSelectedTeam(team2);
}

TournamentWindow::~TournamentWindow() { delete ui; }

void TournamentWindow::setTeam1(QString teamName) { team1 = teamName; }

void TournamentWindow::setTeam2(QString teamName) { team2 = teamName; }

void TournamentWindow::update()
{
    ui->team1Name->setText(team1);
    ui->team2Name->setText(team2);
    teamTable1Model->layoutAboutToBeChanged();
    teamTable1Model->setSelectedTeam(team1);
    teamTable1Model->layoutChanged();
    teamTable2Model->layoutAboutToBeChanged();
    teamTable2Model->setSelectedTeam(team2);
    teamTable2Model->layoutChanged();
}

void TournamentWindow::on_playButton_clicked()
{
    ui->teamScore1->setText(QString::number(_players->countSelectedAST(team1)));
    ui->teamScore2->setText(QString::number(_players->countSelectedAST(team2)));
    int win = _players->countWinner(team1, team2);
    if (win == 1)
    {
        ui->winnerIs->setText("Team №1");
    }
    if (win == 2)
    {
        ui->winnerIs->setText("Team №2");
    }
    if (win == 3)
    {
        ui->winnerIs->setText("DRAW");
    }
}
