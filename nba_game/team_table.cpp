#include "team_table.h"

team_table::team_table(players_list* players, QObject* parent)
    : QAbstractTableModel{parent}, _players(players)
{
}
int team_table::rowCount(const QModelIndex& parent) const
{
    return _players->getTeam().size();
};
int team_table::columnCount(const QModelIndex& parent) const
{
    return _players->getTeamHeaders().size();
};

QVariant team_table::data(const QModelIndex& indx, int role) const
{
    if (role == Qt::DisplayRole)
        return _players->getTeamCell(indx);
    return QVariant();
};
QVariant team_table::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return _players->getTeamHeaders().at(section);
    return QVariant();
};
