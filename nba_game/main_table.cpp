#include "main_table.h"

main_table::main_table(players_list* players, QObject* parent)
    : QAbstractTableModel{parent}, _players{players}
{
}
int main_table::rowCount(const QModelIndex& parent) const
{
    return _players->getSize();
};
int main_table::columnCount(const QModelIndex& parent) const
{
    return _players->getHeaders().size();
};

QVariant main_table::data(const QModelIndex& indx, int role) const
{
    if (role == Qt::DisplayRole)
        return _players->getCell(indx);
    return QVariant();
};
QVariant main_table::headerData(int section, Qt::Orientation orientation,
                                int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    if (orientation == Qt::Horizontal)
        return _players->getHeaders().at(section);
    return QVariant();
};
