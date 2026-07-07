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
        qDebug() << "Błąd: Nie można otworzyć bazy danych!" << m_db.lastError().text();
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

    qDebug() << "Baza danych i tabela tasks zostały pomyślnie zainicjalizowane!";
    return true;
}