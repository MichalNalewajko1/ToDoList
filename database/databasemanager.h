#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QVector>
#include <QDebug>
#include "../models/task.h"

class DatabaseManager {
public:
    DatabaseManager(const QString &path = "todolist.db");

    ~DatabaseManager();

    bool initDatabase();

    bool addTask(const Task &task);

    bool deleteTask(int id);

    bool completeTask(int id);

    QVector<Task> getAllTasks();

private:
    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H