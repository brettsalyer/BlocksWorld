#ifndef AITHREAD_H
#define AITHREAD_H
#include <QObject>
#include <QThread>
#include "state.h"
#include "windows.h"
#include "mainwindow.h"
#include <QSet>

class AIThread : public QObject
 {
     Q_OBJECT
     QThread workerThread;

     // As we visit new states, this list gets updated so we can check against it and not visit the same state twice
     QSet<QString> visited;
     // Holds all children states that have been calculated
     QList<State *> children;
    public:
     State initial;
     State final;

     QList<QStringList> generateLabels(State states);




 public slots:
     void doWork();
     void drawStateL1(QStringList labels) {emit requestDrawStateL1(labels);}
     void drawStateL2(QStringList labels) {emit requestDrawStateL2(labels);}
     void drawStateL3(QStringList labels) {emit requestDrawStateL3(labels);}
     void updateButton(QString text) {emit requestUpdateButton(text);}
     void drawTrans(bool status) {emit requestDrawTrans(status);}

 signals:
     void requestDrawStateL1(QStringList labels);
     void requestDrawStateL2(QStringList labels);
     void requestDrawStateL3(QStringList labels);
     void requestDrawTrans(bool status);

     void requestUpdateButton(QString text);
 };



#endif // AITHREAD_H
