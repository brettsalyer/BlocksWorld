#include "searching.h"
#include <windows.h>

Searching::Searching(Ui::MainWindow *ui)
{
    this->ui = ui;
}

void Searching::search(State *initial, State *final)
{
    State current;
    this->children = initial->calculateChildStates();

    //while (!current.equals(final))
    //{
        for(State child : this->children)
        {
           current = child;
           current.drawState(this->ui);
           Sleep(1000);
           ui->pushButton->setText(current.stateID);
        }
    //}



}
