#ifndef PLAYERS_LIST_H
#define PLAYERS_LIST_H

#include <QFile>
#include <QObject>
#include <QString>
struct Player
{
    QString name;
    unsigned int year;
    QString team;
    unsigned int age;
    double height;
    double weight;
    double pts;
    double reb;
    double ast;
    void fillData(const QStringList& details);
};

class players_list : public QObject
{
    Q_OBJECT
   public:
    explicit players_list(QObject* parent = nullptr);

   public:
    bool loadFile(const QString& fileName);

   signals:
};

#endif  // PLAYERS_LIST_H
