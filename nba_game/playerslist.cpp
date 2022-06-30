#include "playerslist.h"

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

PlayersList::PlayersList(QObject* parent)
    : QObject{parent}, teamName{"New team"}
{
    teams["New team"];
}

QStringList PlayersList::getHeaders() { return headers; }

QStringList PlayersList::getTeamHeaders() { return teamHeaders; }

void PlayersList::appendTeam(const QString teamName) { teams[teamName]; }

Player PlayersList::getPlayer(size_t index) { return players.at(index); }

Player PlayersList::getPlayerFromTeam(QString teamName, size_t id)
{
    for (Player p : teams[teamName])
    {
        if (p.id == id)
            return p;
    }
    return Player();
}

QString PlayersList::getTeamName() { return teamName; }

QSet<Player> PlayersList::getTeam() { return team; }

QSet<Player> PlayersList::getSelectedTeam(QString teamName)
{
    return teams[teamName];
}

QStringList PlayersList::getTeamList()
{
    teams.remove("");
    return teams.keys();
}

void PlayersList::saveTeamsToFile(){

};

int PlayersList::getSize() { return players.size(); }

bool PlayersList::loadFile(QFile& file)
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
            teamHeaders.append(i);

        teamHeaders.append("is_captain");
        teamHeaders.append("in_rotation");

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
QVariant PlayersList::getCell(const QModelIndex& indx)
{
    Player p = players.at(indx.row());
    QVariant data = p.getData(indx);
    if (data.data())
        return data;
    return QVariant();
}
QVariant PlayersList::getTeamCell(const QModelIndex& indx)
{
    Player p = team.values().at(indx.row());
    QVariant data = p.getTeamData(indx);
    if (data.data())
        return data;
    return false;
}

QVariant PlayersList::getSelectedTeamCell(const QModelIndex& indx,
                                          QString teamName)
{
    Player p = teams[teamName].values().at(indx.row());
    QVariant data = p.getTeamData(indx);
    if (data.data())
        return data;
    return false;
}

void PlayersList::setTeamName(QString name) { teamName = name; }

void PlayersList::addToTeam(size_t index)
{
    if (team.size() < 15)
    {
        Player p = players.at(index);
        team.insert(p);
    }
}

void PlayersList::addToSelectedTeam(size_t index, QString teamName)
{
    if (teams[teamName].size() < 15)
    {
        Player p = players.at(index);
        teams[teamName].insert(p);
    }
}

void PlayersList::deleteFromTeam(size_t id)
{
    team.erase(team.find(getPlayer(id)));
}

void PlayersList::deleteFromSelectedTeam(QString teamName, size_t id)
{
    teams[teamName].erase(
        teams[teamName].find(getPlayerFromTeam(teamName, id)));
}

void PlayersList::deleteSelectedTeam(QString teamName)
{
    teams.remove(teamName);
}

void PlayersList::deletePlayer(size_t id)
{
    players.erase(players.begin() + id, players.begin() + id + 1);
}

void PlayersList::changeTeamName(QString& name)
{
    if (name != "")
        teamName = name;
}

double PlayersList::countPTS()
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

double PlayersList::countREB()
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

double PlayersList::countAST()
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

double PlayersList::countSelectedAST(QString& team)
{
    double ast = 0;
    size_t count = 0;
    for (const Player& p : teams[team])
    {
        ast += p.reb;
        count++;
    }
    if (count != 0)
        return ast / count;
    else
        return ast;
}

int PlayersList::countWinner(QString& team1, QString& team2)
{
    double ast1 = countSelectedAST(team1);
    double ast2 = countSelectedAST(team2);
    if (ast1 > ast2)
        return 1;
    else
    {
        if (ast1 < ast2)
            return 2;
        else
            return 3;
    }
}
