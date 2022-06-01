#include "players_list.h"

players_list::players_list(QObject* parent) : QObject{parent} {}
bool players_list::loadFile(const QString& fileName) { return true; }
