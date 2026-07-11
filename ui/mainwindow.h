#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../database/databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_btnAddTask_clicked();

    void on_btnDeleteTask_clicked();

    void on_btnCompleteTask_clicked();

private:
    Ui::MainWindow *ui;
    DatabaseManager m_dbManager;
    void refreshTaskList();
};
#endif // MAINWINDOW_H
