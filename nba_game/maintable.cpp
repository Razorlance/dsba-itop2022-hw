#include "maintable.h"

MainTable::MainTable(PlayersList* players, QObject* parent)
    : QAbstractTableModel{parent}, _players{players}
{
}
int MainTable::rowCount(const QModelIndex& parent) const
{
    return _players->getSize();
};
int MainTable::columnCount(const QModelIndex& parent) const
{
    return _players->getHeaders().size();
};

QVariant MainTable::data(const QModelIndex& indx, int role) const
{
    if (role == Qt::DisplayRole)
        return _players->getCell(indx);
    return QVariant();
};
QVariant MainTable::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return _players->getHeaders().at(section);
    return QVariant();
};
