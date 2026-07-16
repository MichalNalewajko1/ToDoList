#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

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
    connect(ui->cbDarkMode, &QCheckBox::toggled, this, &MainWindow::on_cbDarkMode_toggled);
    connect(ui->listView, &QListWidget::itemDoubleClicked, this, &MainWindow::onTaskDoubleClicked);
    on_cbDarkMode_toggled(false);
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
    ui->listView->clear();

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
        ui->listView->addItem(item);
    }
}

void MainWindow::on_btnDeleteTask_clicked()
{
    QListWidgetItem *selectedItem = ui->listView->currentItem();

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
    QListWidgetItem *selectedItem = ui->listView->currentItem();

    if (!selectedItem) {
        return;
    }

    int taskId = selectedItem->data(Qt::UserRole).toInt();

    if (m_dbManager.completeTask(taskId)) {
        refreshTaskList();
    }
}


void MainWindow::on_cbDarkMode_toggled(bool checked)
{
    if (checked) {
        this->setStyleSheet(
            "QMainWindow { background-color: #1e1e2e; }"
            "#cbDarkMode { color: #cdd6f4; }"
            "#inputTaskTitle {"
            "   padding: 8px; border: 1px solid #45475a; border-radius: 4px;"
            "   background-color: #313244; color: #cdd6f4; font-size: 14px;"
            "}"

            // Stylizuje TYLKO trzy główne przyciski aplikacji
            "#btnAddTask, #btnDeleteTask, #btnCompleteTask {"
            "   background-color: #89b4fa; color: #1e1e2e; border: none;"
            "   border-radius: 4px; padding: 8px 16px; font-weight: bold;"
            "}"
            "#btnAddTask:hover, #btnDeleteTask:hover, #btnCompleteTask:hover {"
            "   background-color: #b4befe;"
            "}"
            "#listWidget {"
            "   background-color: #313244; border: 1px solid #45475a;"
            "   border-radius: 4px; padding: 4px; font-size: 14px; color: #cdd6f4;"
            "}"
            "QListWidget::item { padding: 8px; border-bottom: 1px solid #45475a; }"
            "QListWidget::item:selected { background-color: #45475a; color: #ffffff; }"
            );
    } else {
        this->setStyleSheet(
            "QMainWindow { background-color: #f4f5f7; }"
            "#cbDarkMode { color: #333333; }"

            "#inputTaskTitle {"
            "   padding: 8px; border: 1px solid #ced4da; border-radius: 4px;"
            "   background-color: white; color: black; font-size: 14px;"
            "}"

            "#btnAddTask, #btnDeleteTask, #btnCompleteTask {"
            "   background-color: #007bff; color: white; border: none;"
            "   border-radius: 4px; padding: 8px 16px; font-weight: bold;"
            "}"
            "#btnAddTask:hover, #btnDeleteTask:hover, #btnCompleteTask:hover {"
            "   background-color: #0056b3;"
            "}"

            "#listWidget {"
            "   background-color: white; border: 1px solid #ced4da;"
            "   border-radius: 4px; padding: 4px; font-size: 14px; color: black;"
            "}"
            "QListWidget::item { padding: 8px; border-bottom: 1px solid #eee; }"
            "QListWidget::item:selected { background-color: #e2e6ea; color: black; }"
            );
    }

}

void MainWindow::onTaskDoubleClicked(QListWidgetItem *item) {
    if (!item) {
        return;
    }

    int taskId = item->data(Qt::UserRole).toInt();
    QString currentTitle = item->text();
    bool ok;
    QString newTitle = QInputDialog::getText(this,
                                             "Edycja zadania",
                                             "Wprowadź nową treść zadania:",
                                             QLineEdit::Normal,
                                             currentTitle,
                                             &ok);

    if (ok && !newTitle.trimmed().isEmpty()) {
        if (m_dbManager.updateTaskTitle(taskId, newTitle.trimmed())) {
            refreshTaskList();
        }
    }
}
