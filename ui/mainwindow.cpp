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
    }
}

