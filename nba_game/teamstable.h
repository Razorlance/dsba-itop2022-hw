#ifndef TEAMSTABLE_H
#define TEAMSTABLE_H
#include <QObject>

#include "playerslist.h"

class TeamsTable : public QAbstractTableModel
{
    Q_OBJECT
   public:
    explicit TeamsTable(PlayersList* players, QObject* parent = nullptr);

   public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

   public:
    QVariant data(const QModelIndex& indx,
                  int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
    void setSelectedTeam(QString);

   protected:
    PlayersList* _players;
    QString _selectedTeam;
   signals:
};

#endif  // TEAMSTABLE_H
