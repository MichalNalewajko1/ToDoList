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
}

MainWindow::~MainWindow()
{
    delete ui;
}
