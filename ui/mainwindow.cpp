#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_dbManager.initDatabase();

    m_model = new TaskModel(this);
    m_model->setTable("tasks");
    m_model->select();

    m_proxyModel = new QSortFilterProxyModel(this);
    m_proxyModel->setSourceModel(m_model);
    m_proxyModel->setFilterKeyColumn(1);
    m_proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    ui->listView->setModel(m_proxyModel);
    ui->listView->setModelColumn(1);

    on_cbDarkMode_toggled(ui->cbDarkMode->isChecked());

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
        m_model->select();
    }
}


void MainWindow::on_btnCompleteTask_clicked() {
    QModelIndex proxyIndex = ui->listView->currentIndex();
    if (!proxyIndex.isValid()) return;

    QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);

    QModelIndex idIndex = m_model->index(sourceIndex.row(), 0);
    int taskId = m_model->data(idIndex).toInt();

    if (m_dbManager.completeTask(taskId)) {
        m_model->select();
    }
}

void MainWindow::on_btnDeleteTask_clicked() {
    QModelIndex proxyIndex = ui->listView->currentIndex();
    if (!proxyIndex.isValid()) return;

    QModelIndex sourceIndex = m_proxyModel->mapToSource(proxyIndex);

    QModelIndex idIndex = m_model->index(sourceIndex.row(), 0);
    int taskId = m_model->data(idIndex).toInt();

    if (m_dbManager.deleteTask(taskId)) {
        m_model->select();
    }
}

void MainWindow::on_cbDarkMode_toggled(bool checked)
{
    if (checked) {
        this->setStyleSheet(
            "QMainWindow { background-color: #1e1e2e; }"
            "#cbDarkMode { color: #cdd6f4; }"
            "#inputTaskTitle, #inputSearch {"
            "   padding: 8px; border: 1px solid #45475a; border-radius: 4px;"
            "   background-color: #313244; color: #cdd6f4; font-size: 14px;"
            "}"
            "#btnAddTask, #btnDeleteTask, #btnCompleteTask {"
            "   background-color: #89b4fa; color: #1e1e2e; border: none;"
            "   border-radius: 4px; padding: 8px 16px; font-weight: bold;"
            "}"
            "#btnAddTask:hover, #btnDeleteTask:hover, #btnCompleteTask:hover {"
            "   background-color: #b4befe;"
            "}"
            "#listView {"
            "   background-color: #313244; border: 1px solid #45475a;"
            "   border-radius: 4px; padding: 4px; font-size: 14px; color: #cdd6f4;"
            "}"
            "QListView::item { padding: 8px; border-bottom: 1px solid #45475a; }"
            "QListView::item:selected { background-color: #45475a; color: #ffffff; }"
            );
    } else {
        this->setStyleSheet(
            "QMainWindow { background-color: #f4f5f7; }"
            "#cbDarkMode { color: #333333; }"

            "#inputTaskTitle, #inputSearch {"
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

            "#listView {"
            "   background-color: white; border: 1px solid #ced4da;"
            "   border-radius: 4px; padding: 4px; font-size: 14px; color: black;"
            "}"
            "QListView::item { padding: 8px; border-bottom: 1px solid #eee; }"
            "QListView::item:selected { background-color: #e2e6ea; color: black; }"
            );
    }

}

void MainWindow::on_inputSearch_textChanged(const QString &arg1) {
    m_proxyModel->setFilterFixedString(arg1);
}

void MainWindow::on_listView_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    QModelIndex sourceIndex = m_proxyModel->mapToSource(index);


    QModelIndex idIndex = m_model->index(sourceIndex.row(), 0);
    QModelIndex titleIndex = m_model->index(sourceIndex.row(), 1);

    int taskId = m_model->data(idIndex).toInt();
    QString currentTitle = m_model->data(titleIndex).toString();

    bool ok;
    QString newTitle = QInputDialog::getText(this, "Edycja zadania",
                                             "Wprowadź nową treść zadania:",
                                             QLineEdit::Normal, currentTitle, &ok);

    if (ok && !newTitle.trimmed().isEmpty()) {
        if (m_dbManager.updateTaskTitle(taskId, newTitle.trimmed())) {
            m_model->select();
        }
    }
}

