#ifndef TEAM_TABLE_H
#define TEAM_TABLE_H

#include <QAbstractTableModel>
#include <QObject>

#include "players_list.h"
class team_table : public QAbstractTableModel
{
    Q_OBJECT
   protected:
    players_list* _players;

   public:
    explicit team_table(players_list* players, QObject* parent = nullptr);

   public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

   public:
    QVariant data(const QModelIndex& indx,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

   signals:
};

#endif  // TEAM_TABLE_H
