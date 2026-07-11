#include "databasemanager.h"

DatabaseManager::DatabaseManager(const QString &path) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);
}

DatabaseManager::~DatabaseManager() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::initDatabase() {
    if (!m_db.open()) {
        qDebug() << "Błąd: " << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString createTableSQL = "CREATE TABLE IF NOT EXISTS tasks ("
                             "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                             "title TEXT NOT NULL, "
                             "description TEXT, "
                             "is_completed INTEGER DEFAULT 0"
                             ")";

    if (!query.exec(createTableSQL)) {
        qDebug() << "Błąd podczas tworzenia tabeli:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::addTask(const Task &task) {
    QSqlQuery query;
    query.prepare("INSERT INTO tasks (title, is_completed) VALUES (:title, :completed)");

    query.bindValue(":title", task.title);
    query.bindValue(":completed", task.isCompleted ? 1 : 0);

    if (!query.exec()) {
        qDebug() << "Błąd podczas dodawania zadania do bazy:" << query.lastError().text();
        return false;
    }

    return true;
}

QVector<Task> DatabaseManager::getAllTasks() {
    QVector<Task> tasks;

    QSqlQuery query("SELECT id, title, description, is_completed FROM tasks");

    while (query.next()) {
        int id = query.value("id").toInt();
        QString title = query.value("title").toString();
        QString description = query.value("description").toString();
        bool isCompleted = query.value("is_completed").toInt() == 1;

        tasks.append(Task(id, title, description, isCompleted));
    }

    return tasks;
}

bool DatabaseManager::deleteTask(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug()<<"Błąd: "<<query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::completeTask(int id){
    QSqlQuery query;
    query.prepare("UPDATE tasks SET is_completed = 1 WHERE id = :id");
    query.bindValue(":id", id);

    if(!query.exec()){
        qDebug()<<"Blad: "<<query.lastError().text();
        return false;
    }
    return true;
}