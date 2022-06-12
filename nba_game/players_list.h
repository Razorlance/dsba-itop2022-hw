#ifndef PLAYERS_LIST_H
#define PLAYERS_LIST_H

#include <QFile>
#include <QFileDialog>
#include <QObject>
#include <QStandardItem>
#include <QString>
#include <QTextStream>
struct Player
{
    size_t id;
    QString name;
    QString team;
    unsigned int year;
    unsigned int age;
    double height;
    double weight;
    double pts;
    double reb;
    double ast;
    QStringList line;
    void fillData(const QStringList& details);
    QVariant getData(const QModelIndex& indx);
};

class players_list : public QObject
{
    Q_OBJECT
   public:
    explicit players_list(QObject* parent = nullptr);

   public:
    bool loadFile(QFile& fileName);
    int getSize();
    QVariant getCell(const QModelIndex&);
    QVariant getTeamCell(const QModelIndex&);
    void addToTeam(size_t);
    void deleteFromTeam(Player*);
    void deletePlayer(size_t);
    QStringList getHeaders();
    Player getPlayer(size_t);
    QList<Player> getTeam();

   protected:
    QList<Player> players;
    QList<Player> team;
    QStringList headers;
   signals:
};

#endif  // PLAYERS_LIST_H
