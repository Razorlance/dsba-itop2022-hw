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
    void changeTeamName(QString&);
    double countPTS();
    double countREB();
    double countAST();
    QStringList getHeaders();
    Player getPlayer(size_t);
    QString getTeamName();
    QSet<Player> getTeam();

   protected:
    QList<Player> players;
    QSet<Player> team;
    QStringList headers;
    QString team_name;
   signals:
};
inline bool operator==(const Player& e1, const Player& e2)
{
    return e1.id == e2.id;
}

inline uint qHash(const Player& key, uint seed)
{
    return qHash(key.id, seed) ^ key.age;
}

#endif  // PLAYERS_LIST_H
