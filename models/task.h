#ifndef TASK_H
#define TASK_H

#include <QString>

struct Task {
    int id;
    QString title;
    QString description;
    bool isCompleted;
    Task(int id, const QString &title, const QString &description, bool isCompleted)
        : id(id), title(title), description(description), isCompleted(isCompleted) {}
};

#endif // TASK_H