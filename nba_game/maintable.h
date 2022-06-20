#ifndef MAINTABLE_H
#define MAINTABLE_H

#include <QAbstractTableModel>
#include <QObject>

#include "playerslist.h"

class MainTable : public QAbstractTableModel
{
    Q_OBJECT
   protected:
    PlayersList* _players;

   public:
    explicit MainTable(PlayersList* players, QObject* parent = nullptr);

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

#endif  // MAINTABLE_H
