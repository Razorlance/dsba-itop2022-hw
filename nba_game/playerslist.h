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
    QVariant getSelectedTeamCell(const QModelIndex&, QString);
    void setTeamName(QString);
    void addToTeam(size_t);
    void addToSelectedTeam(size_t, QString);
    void deleteFromTeam(size_t);
    void deleteFromSelectedTeam(QString, size_t);
    void deleteSelectedTeam(QString);
    void deletePlayer(size_t);
    void changeTeamName(QString&);
    double countPTS();
    double countREB();
    double countAST();
    double countSelectedAST(QString&);
    int countWinner(QString&, QString&);
    QStringList getHeaders();
    QStringList getTeamHeaders();
    void appendTeam(const QString);
    Player getPlayer(size_t);
    Player getPlayerFromTeam(QString, size_t);
    QString getTeamName();
    QSet<Player> getTeam();
    QSet<Player> getSelectedTeam(QString);
    QStringList getTeamList();
    void saveTeamsToFile();

   protected:
    bool one_captain;
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
