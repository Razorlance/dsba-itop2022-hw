#include "teamtable.h"

TeamTable::TeamTable(PlayersList* players, QObject* parent)
    : QAbstractTableModel{parent}, _players(players)
{
}
int TeamTable::rowCount(const QModelIndex& parent) const
{
    return _players->getTeam().size();
};
int TeamTable::columnCount(const QModelIndex& parent) const
{
    return _players->getTeamHeaders().size();
};

QVariant TeamTable::data(const QModelIndex& indx, int role) const
{
    if (role == Qt::DisplayRole)
        return _players->getTeamCell(indx);
    return QVariant();
};
QVariant TeamTable::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return _players->getTeamHeaders().at(section);
    return QVariant();
};
