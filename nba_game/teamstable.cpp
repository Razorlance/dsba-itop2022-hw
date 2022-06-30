#include "teamstable.h"

TeamsTable::TeamsTable(PlayersList* players, QObject* parent)
    : QAbstractTableModel{parent}, _players{players}
{
}
int TeamsTable::rowCount(const QModelIndex& parent) const
{
    return _players->getSelectedTeam(_selectedTeam).size();
};
int TeamsTable::columnCount(const QModelIndex& parent) const
{
    return _players->getTeamHeaders().size();
};

QVariant TeamsTable::data(const QModelIndex& indx, int role) const
{
    if (role == Qt::DisplayRole)
        return _players->getSelectedTeamCell(indx, _selectedTeam);
    return QVariant();
};
QVariant TeamsTable::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return _players->getTeamHeaders().at(section);
    return QVariant();
}

void TeamsTable::setSelectedTeam(QString teamName)
{
    _selectedTeam = teamName;
};
