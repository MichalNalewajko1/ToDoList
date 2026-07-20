#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QSqlTableModel>
#include "../database/databasemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class TaskModel : public QSqlTableModel {
public:
    using QSqlTableModel::QSqlTableModel;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        QVariant value = QSqlTableModel::data(index, role);

        if (role == Qt::FontRole || role == Qt::ForegroundRole) {
            QModelIndex statusIndex = this->index(index.row(), 3);
            bool isCompleted = QSqlTableModel::data(statusIndex, Qt::DisplayRole).toBool();

            if (isCompleted) {
                if (role == Qt::FontRole) {
                    QFont font;
                    font.setStrikeOut(true);
                    return font;
                }
                if (role == Qt::ForegroundRole) {
                    return QColor(Qt::gray);
                }
            }
        }
        return value;
    }
};

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

    void on_cbDarkMode_toggled(bool checked);

    void on_inputSearch_textChanged(const QString &arg1);

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    DatabaseManager m_dbManager;

    TaskModel *m_model;
    QSortFilterProxyModel *m_proxyModel;

    void updateTaskProgress();
};
#endif // MAINWINDOW_H
