#include "players_list.h"

#include <QDebug>
void Player::fillData(const QStringList& details)
{
    id = details[0].toInt();
    name = details[1];
    team = details[2];
    year = details[21];
    age = details[3].toDouble();
    height = details[4].toDouble();
    weight = details[5].toDouble();
    pts = details[12].toDouble();
    reb = details[13].toDouble();
    ast = details[14].toDouble();
    in_rotation = "NO";
    is_captain = "NO";
}

QVariant Player::getData(const QModelIndex& indx)
{
    switch (indx.column())
    {
        case 0:
            return id;
        case 1:
            return name;
        case 2:
            return team;
        case 3:
            return age;
        case 4:
            return height;
        case 5:
            return weight;
        case 6:
            return pts;
        case 7:
            return reb;
        case 8:
            return ast;
        case 9:
            return year;
        default:
            return "";
    }
}
QVariant Player::getTeamData(const QModelIndex& indx)
{
    switch (indx.column())
    {
        case 0:
            return id;
        case 1:
            return name;
        case 2:
            return team;
        case 3:
            return age;
        case 4:
            return height;
        case 5:
            return weight;
        case 6:
            return pts;
        case 7:
            return reb;
        case 8:
            return ast;
        case 9:
            return year;
        case 10:
            return is_captain;
        case 11:
            return in_rotation;
        default:
            return "";
    }
}

players_list::players_list(QObject* parent)
    : QObject{parent}, team_name{"New team"}
{
}

QStringList players_list::getHeaders() { return headers; }

QStringList players_list::getTeamHeaders() { return team_headers; }

Player players_list::getPlayer(size_t index) { return players.at(index); }

QString players_list::getTeamName() { return team_name; }

QSet<Player> players_list::getTeam() { return team; };
int players_list::getSize() { return players.size(); }

bool players_list::loadFile(QFile& file)
{
    if (file.open(QIODevice::ReadOnly))
    {
        size_t lineindex = 0;
        QTextStream in(&file);
        QString fileLine = in.readLine();
        QStringList h = fileLine.split(",", Qt::SkipEmptyParts);

        headers.append(h[0]);
        headers.append(h[1]);
        headers.append(h[2]);
        headers.append(h[3]);
        headers.append(h[4]);
        headers.append(h[5]);
        headers.append(h[12]);
        headers.append(h[13]);
        headers.append(h[14]);
        headers.append(h[21]);
        for (QString i : headers)
            team_headers.append(i);

        team_headers.append("is_captain");
        team_headers.append("in_rotation");

        while (!in.atEnd())
        {
            fileLine = in.readLine();
            QStringList lineToken = fileLine.split(",", Qt::SkipEmptyParts);
            Player p;
            p.fillData(lineToken);
            players.append(p);
            lineindex++;
        }
        file.close();
        return true;
    }
    return false;
}
QVariant players_list::getCell(const QModelIndex& indx)
{
    Player p = players.at(indx.row());
    QVariant data = p.getData(indx);
    if (data.data())
        return data;
    return QVariant();
}
QVariant players_list::getTeamCell(const QModelIndex& indx)
{
    Player p = team.values().at(indx.row());
    QVariant data = p.getTeamData(indx);
    if (data.data())
        return data;
    return false;
}

void players_list::addToTeam(size_t index)
{
    if (team.size() < 15)
    {
        Player p = players.at(index);
        team.insert(p);
        // qDebug() << players.at(index).name;
    }
}

void players_list::deleteFromTeam(size_t id)
{
    team.erase(team.find(getPlayer(id)));
}

void players_list::deletePlayer(size_t id)
{
    players.erase(players.begin() + id, players.begin() + id + 1);
    //    for (size_t i = 0; i < players.size(); i++)
    //    {
    //        if (players[i].id == id)
    //        {
    //            players.removeAt(i);
    //        }
    //    }
    //    players.removeAt(pos);
}

void players_list::changeTeamName(QString& name)
{
    if (name != "")
        team_name = name;
}

double players_list::countPTS()
{
    double pts = 0;
    size_t count = 0;
    for (const Player& p : team)
    {
        pts += p.pts;
        count++;
    }
    if (count != 0)
        return pts / count;
    else
        return pts;
}

double players_list::countREB()
{
    double reb = 0;
    size_t count = 0;
    for (const Player& p : team)
    {
        reb += p.reb;
        count++;
    }
    if (count != 0)
        return reb / count;
    return reb;
}

double players_list::countAST()
{
    double ast = 0;
    size_t count = 0;
    for (const Player& p : team)
    {
        ast += p.reb;
        count++;
    }
    if (count != 0)
        return ast / count;
    else
        return ast;
}

void players_list::toggle_captain(){

};
