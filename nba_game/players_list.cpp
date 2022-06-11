#include "players_list.h"

#include <QDebug>
void Player::fillData(const QStringList& details)
{
    if (details.size() < 9)
        throw std::invalid_argument("Invalid player description");
    id = details[0].toInt();
    name = details[1];
    team = details[2];
    year = details[21].toInt();
    age = details[3].toInt();
    height = details[4].toDouble();
    weight = details[5].toDouble();
    pts = details[12].toDouble();
    reb = details[13].toDouble();
    ast = details[14].toDouble();
    line = details;
}

QVariant Player::getData(const QModelIndex& indx) { return true; }

players_list::players_list(QObject* parent) : QObject{parent} {}
QStringList players_list::getHeaders() { return headers; }

Player players_list::getPlayer(size_t index) { return players.at(index); };
int players_list::getSize() { return players.size(); }

bool players_list::loadFile(QFile& file)
{
    if (file.open(QIODevice::ReadOnly))
    {
        size_t lineindex = 0;
        QTextStream in(&file);
        QString fileLine = in.readLine();
        headers = fileLine.split(",", Qt::SkipEmptyParts);
        // model->setHorizontalHeaderLabels(lineToken);
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
    return players.at(indx.row()).line.at(indx.column());
}

void players_list::addToTeam(size_t index)
{
    if (team.size() < 15)
    {
        team.append(players.at(index));
        // qDebug() << players.at(index).name;
    }
}

void players_list::deleteFromTeam(Player*) {}

void players_list::deletePlayer(size_t id)
{
    for (Player& p : players)
    {
        if (p.id == id)
            players.erase(&p);
    }
    //    players.removeAt(pos);
};
