#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H

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
    QString year;
    unsigned int age;
    double height;
    double weight;
    double pts;
    double reb;
    double ast;
    QStringList line;
    QString is_captain;
    QString in_rotation;
    void fillData(const QStringList& details);
    QVariant getData(const QModelIndex& indx);
    QVariant getTeamData(const QModelIndex& indx);
};

class PlayersList : public QObject
{
    Q_OBJECT
   public:
    explicit PlayersList(QObject* parent = nullptr);

   public:
    bool loadFile(QFile& fileName);
    int getSize();
    QVariant getCell(const QModelIndex&);
    QVariant getTeamCell(const QModelIndex&);
    void addToTeam(size_t);
    void deleteFromTeam(size_t);
    void deletePlayer(size_t);
    void changeTeamName(QString&);
    double countPTS();
    double countREB();
    double countAST();
    void toggle_captain();
    QStringList getHeaders();
    QStringList getTeamHeaders();
    Player getPlayer(size_t);
    QString getTeamName();
    QSet<Player> getTeam();

   protected:
    bool one_captain;
    QList<Player> players;
    QSet<Player> team;
    QStringList headers;
    QStringList teamHeaders;
    QString teamName;
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

#endif  // PLAYERSLIST_H
