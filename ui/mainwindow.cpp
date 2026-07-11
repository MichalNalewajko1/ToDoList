#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if(!m_dbManager.initDatabase()){
        QMessageBox::critical(this, "Błąd krytyczny", "Nie udało się zainicjalizować bazy danych!");
    }
    connect(ui->btnAddTask, &QPushButton::clicked, this, &MainWindow::on_btnAddTask_clicked);
    connect(ui->btnDeleteTask, &QPushButton::clicked, this, &MainWindow::on_btnDeleteTask_clicked);
    connect(ui->btnCompleteTask, &QPushButton::clicked, this, &MainWindow::on_btnCompleteTask_clicked);
    refreshTaskList();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddTask_clicked()
{
    QString title = ui->inputTaskTitle->text().trimmed();

    if (title.isEmpty()) {
        return;
    }
    Task newTask(-1, title, "", false);

    if (m_dbManager.addTask(newTask)) {
        ui->inputTaskTitle->clear();

        refreshTaskList();
    }
}

void MainWindow::refreshTaskList() {
    ui->listWidget->clear();

    QVector<Task> tasks = m_dbManager.getAllTasks();
    for (const Task &task : tasks) {
        QListWidgetItem *item = new QListWidgetItem(task.title);
        item->setData(Qt::UserRole, task.id);
        if (task.isCompleted) {
            QFont font = item->font();
            font.setStrikeOut(true);
            item->setFont(font);
            item->setForeground(Qt::gray);
        }
        ui->listWidget->addItem(item);
    }
}

void MainWindow::on_btnDeleteTask_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();

    if (!selectedItem) {
        return;
    }

    int taskId = selectedItem->data(Qt::UserRole).toInt();

    if (m_dbManager.deleteTask(taskId)) {
        refreshTaskList();
    }
}


void MainWindow::on_btnCompleteTask_clicked()
{
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();

    if (!selectedItem) {
        return;
    }

    int taskId = selectedItem->data(Qt::UserRole).toInt();

    if (m_dbManager.completeTask(taskId)) {
        refreshTaskList();
    }
}

