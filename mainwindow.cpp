#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QLabel>
#include "utilities.h"
#include "aithread.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);








;}

MainWindow::~MainWindow()
{
    worker.quit();
    worker.wait();
    delete ui;
}

void MainWindow::updateButton(QString text)
{
    ui->pushButton->setText(text);
    qDebug() << "Signal Received";
}

void MainWindow::drawTrans(bool status)
{
    if ( ui->r != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->r->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        //delete ui->l1;
    }

    qDebug() << "Transitioning...";
    if (status)
    {
        QWidget *newWidget = new QWidget();
        newWidget->setStyleSheet("background-color: red");
        ui->r->addWidget(newWidget);
    }
    else
    {
        ui->r->addWidget(new QWidget());
    }
}

void MainWindow::drawStateL1(QStringList labels)
{
    if ( ui->l1 != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->l1->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        //delete ui->l1;
    }

    for(QString label : labels)
    {
        QLabel *newLabel = new QLabel(label);
        if (label != "")
            newLabel->setStyleSheet("background-color: red");
        this->ui->l1->addWidget(newLabel);
    }
}

void MainWindow::drawStateL2(QStringList labels)
{
    if ( ui->l2 != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->l2->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        //delete ui->l1;
    }

    for(QString label : labels)
    {
        QLabel *newLabel = new QLabel(label);
        if (label != "")
            newLabel->setStyleSheet("background-color: red");
        this->ui->l2->addWidget(newLabel);
    }
}

void MainWindow::drawStateL3(QStringList labels)
{
    if ( ui->l3 != NULL )
    {
        QLayoutItem* item;
        while ( ( item = ui->l3->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        //delete ui->l1;
    }

    for(QString label : labels)
    {
        QLabel *newLabel = new QLabel(label);
        if (label != "")
            newLabel->setStyleSheet("background-color: red");
        this->ui->l3->addWidget(newLabel);
    }
}


void MainWindow::on_pushButton_clicked()
{
    // File IO Testing
    Utilities util;
    util.readStateFile(this->statesfile);
    State initialState = util.getInitialState();
    State finalState = util.getFinalState();

    qDebug() << "Equality: " << initialState.equals(finalState);
    AIThread *searchThread = new AIThread();

    searchThread->moveToThread(&worker);

    connect(&worker, SIGNAL(finished()), searchThread, SLOT(deleteLater()));

    connect(searchThread, SIGNAL(requestDrawStateL1(QStringList)), this, SLOT(drawStateL1(QStringList)));
    connect(searchThread, SIGNAL(requestDrawStateL2(QStringList)), this, SLOT(drawStateL2(QStringList)));
    connect(searchThread, SIGNAL(requestDrawStateL3(QStringList)), this, SLOT(drawStateL3(QStringList)));
    connect(searchThread, SIGNAL(requestDrawTrans(bool)), this, SLOT(drawTrans(bool)));

    connect(searchThread, SIGNAL(requestUpdateButton(QString)), this, SLOT(updateButton(QString)));
    connect(this, SIGNAL(operate()), searchThread, SLOT(doWork()));

    searchThread->initial = initialState;
    searchThread->final = finalState;
    worker.start();
    emit operate();
}

void MainWindow::on_pushButton_2_clicked()
{
    QFileDialog *fd = new QFileDialog();
    this->statesfile = fd->getOpenFileName(this, tr("Open state file"), "./", tr("Text File (*.txt)"));
    this->ui->lineEdit->setText(this->statesfile);
}
