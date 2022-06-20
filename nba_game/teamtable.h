#ifndef TEAMTABLE_H
#define TEAMTABLE_H

#include <QAbstractTableModel>
#include <QObject>

#include "playerslist.h"
class TeamTable : public QAbstractTableModel
{
    Q_OBJECT
   protected:
    PlayersList* _players;

   public:
    explicit TeamTable(PlayersList* players, QObject* parent = nullptr);

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

#endif  // TEAMTABLE_H
