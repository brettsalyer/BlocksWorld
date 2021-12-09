#include "aithread.h"
#include <QStack>
#include <QList>
#include <QDebug>

QList<QStringList> AIThread::generateLabels(State state)
{
    QList<QStringList> labels;
    QStringList l1;
    QStringList l2;
    QStringList l3;

    QString data;

    for(int i = 6; i >= 0; i--)
    {
        if(state.l1.size() - 1 >= i)
        {
            //QLabel *newBlock = new QLabel();
            //newBlock->setStyleSheet("background-color: red");

            data = state.l1[i].id;
            data.append("\n");
            for(int j = 0; j < state.l1[i].relations.size(); j++)
            {
                data.append(state.l1[i].relations[j].toString() + "\n");
            }
            //newBlock->setText(data);
            //l1->addWidget(newBlock);
            l1.append(data);
        }else
        {
            //QLabel *wid = new QLabel();
            //l1->addWidget(wid);
            data = "";
            l1.append(data);
        }

    }
    labels.append(l1);

    for(int i = 6; i >= 0; i--)
    {
        if(state.l2.size() - 1 >= i)
        {
            //QLabel *newBlock = new QLabel();
            //newBlock->setStyleSheet("background-color: red");

            QString data = state.l2[i].id;
            data.append("\n");
            for(int j = 0; j < state.l2[i].relations.size(); j++)
            {
                data.append(state.l2[i].relations[j].toString() + "\n");
            }
            //newBlock->setText(data);
            //l2->addWidget(newBlock);
            l2.append(data);
        }else
        {
            //QLabel *wid = new QLabel();
            //l2->addWidget(wid);
            data = "";
            l2.append(data);
        }

    }
    labels.append(l2);

    for(int i = 6; i >= 0; i--)
    {
        if(state.l3.size() - 1 >= i)
        {
            //QLabel *newBlock = new QLabel();
            //newBlock->setStyleSheet("background-color: red");

            QString data = state.l3[i].id;
            data.append("\n");
            for(int j = 0; j < state.l3[i].relations.size(); j++)
            {
                data.append(state.l3[i].relations[j].toString() + "\n");
            }
            //newBlock->setText(data);
            //l3->addWidget(newBlock);
            l3.append(data);
        }else
        {
            //QLabel *wid = new QLabel();
            //l3->addWidget(wid);
            data = "";
            l3.append(data);
        }

    }
    labels.append(l3);

    return labels;
}

void AIThread::doWork()
{
    qDebug("Signal Received");

    //this->drawState(initialState);
    //Sleep(1000);
    State *current;
    this->children = initial.calculateChildStates();

    // While we are still looking for the final state
    bool found = false;
    while (!found)
    {

        QList<State *> temp;  // Temp list to hold children
        for(State *child : this->children)  // For every child at this layer
        {
            current = child;  // Current

            if(!visited.contains(current->stateID))
            {
                qDebug() << current->stateID;

                if(current->equals(final))
                {
                    found = true;
                    break;
                }
                else
                {
                    this->visited.insert(current->stateID);
                    temp.append(current->calculateChildStates());
                }
            }else
            {
                qDebug() << "Skipping";
            }
        }
        qDebug() << "Visited state count: " << this->visited.size();
        this->children = temp;
        temp.clear();




    }

    State *traceptr = current;
    QStack<State*> trace;

    // Trace the route back to the starting point
    while(traceptr != 0x0){
        trace.append(traceptr);
        traceptr = traceptr->parent;
    }
    int size = trace.size();
    // Once the path has been determined, show this on the UI
    while(trace.size() > 0)
    {
        this->drawTrans(false);
        QList<QStringList> labels = this->generateLabels(*trace.pop());
        this->drawStateL1(labels[0]);
        this->drawStateL2(labels[1]);
        this->drawStateL3(labels[2]);
        Sleep(2000);

        if  (trace.size() != 0)
        {
            QChar block = trace.top()->stateYieldedBy[4];
            if(block == 1)
            {
                int i;
                // Find the top block
                for(i = 0; i < labels[0].size(); i++)
                {

                    if(labels[0][i] != "")
                    {
                        break;
                    }
                }
                labels[0].removeAt(i);
                this->drawStateL1(labels[0]);
            }
            else if (block == 2)
            {
                int i;
                // Find the top block
                for(i = 0; i < labels[1].size(); i++)
                {

                    if(labels[1][i] != "")
                    {
                        break;
                    }
                }
                labels[1].removeAt(i);
                this->drawStateL2(labels[1]);
            }
            else if (block == 3)
            {
                int i;
                // Find the top block
                for(i = 0; i < labels[2].size(); i++)
                {

                    if(labels[2][i] != "")
                    {
                        break;
                    }
                }
                labels[2].removeAt(i);
                this->drawStateL3(labels[2]);
            }

            this->drawTrans(true);
            Sleep(2000);
        }

       this->drawTrans(false);
    }
    qDebug() << "Done";
    qDebug() << size;

}
