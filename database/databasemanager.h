#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "../models/task.h"

class DatabaseManager {
public:
    DatabaseManager(const QString &path = "todolist.db");

    ~DatabaseManager();

    bool initDatabase();

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H