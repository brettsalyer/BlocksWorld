#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "state.h"
#include "aithread.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QThread worker;
    QString statesfile;

public slots:
    void drawStateL1(QStringList labels);
    void drawStateL2(QStringList labels);
    void drawStateL3(QStringList labels);
    void updateButton(QString text);
    void drawTrans(bool status);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

signals:
    void operate();
};
#endif // MAINWINDOW_H
