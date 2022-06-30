#ifndef PLAYERSLIST_H
#define PLAYERSLIST_H

#include <QFile>
#include <QFileDialog>
#include <QMap>
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
    QVariant getSelectedTeamCell(const QModelIndex&, const QString&);
    void setTeamName(const QString&);
    void addToTeam(const size_t);
    void addToSelectedTeam(const size_t, const QString&);
    void deleteFromTeam(const size_t);
    void deleteFromSelectedTeam(const QString&, const size_t);
    void deleteSelectedTeam(const QString&);
    void deletePlayer(const size_t);
    void changeTeamName(const QString&);
    double countPTS();
    double countREB();
    double countAST();
    double countSelectedAST(const QString&);
    int countWinner(const QString&, const QString&);
    QStringList getHeaders();
    QStringList getTeamHeaders();
    void appendTeam(const QString);
    Player getPlayer(const size_t);
    Player getPlayerFromTeam(const QString&, const size_t);
    QString getTeamName();
    QSet<Player> getTeam();
    QSet<Player> getSelectedTeam(const QString&);
    QStringList getTeamList();
    void saveTeamsToFile();

   protected:
    QList<Player> players;
    QSet<Player> team;
    QStringList headers;
    QStringList teamHeaders;
    QString teamName;
    QString selectedTeam;
    QMap<QString, QSet<Player>> teams;
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
