#include "state.h"
#include "constants.h"
#include <QDebug>
#include <iostream>

State::State()
{

}

State::State(QStack<Block> l1, QStack<Block> l2, QStack<Block> l3)
{
    this->l1 = l1;
    this->l2 = l2;
    this->l3 = l3;

    // Assign relationships
    this->assignClear();
    this->assignTable();
    this->assignOn();
    this->setID();


}

QStack<Block> State::getL1()
{
    return this->l1;
}

QStack<Block> State::getL2()
{
    return this->l2;
}


QStack<Block> State::getL3()
{
    return this->l3;
}


State * State::move(int source, int destination)
{
    QStack<Block> l1 = this->getL1();
    QStack<Block> l2 = this->getL2();
    QStack<Block> l3 = this->getL3();

    State *yieldedState = new State(l1, l2, l3);
    Block moving;

    yieldedState->stateYieldedBy = MOVE;
    yieldedState->stateYieldedBy.append(source).append(destination);

    // Where is the block coming from?
    switch (source){
    case 1:
        moving = yieldedState->l1.pop();
        break;
    case 2:
        moving = yieldedState->l2.pop();
        break;
    case 3:
        moving = yieldedState->l3.pop();
        break;
    }
    // Where is the block going?
    switch (destination){
    case 1:
        yieldedState->l1.append(moving);
        break;
    case 2:
        yieldedState->l2.append(moving);
        break;
    case 3:
        yieldedState->l3.append(moving);
        break;
    }
    yieldedState->setID();
    yieldedState->updateRelations();
    yieldedState->parent = this;

    return yieldedState;
}

QList<State *> State::calculateChildStates()
{
    QList<State *> children;
    // Blocks on top of the stack are the only ones that can be moved

    // States that can be yielded from moving CLEAR block on stack L1:
    if (!this->l1.isEmpty())
    {
        children.append(this->move(1, 2));
        children.append(this->move(1, 3));
    }

    if (!this->l2.isEmpty())
    {
        children.append(this->move(2, 1));
        children.append(this->move(2, 3));
    }

    if (!this->l3.isEmpty())
    {
        children.append(this->move(3, 1));
        children.append(this->move(3, 2));
    }


    return children;

}

void State::setID()
{
    this->stateID.clear();
    for(Block block : this->l1)
    {
        this->stateID.append(block.id);
    }
    this->stateID.append("-");

    for(Block block : this->l2)
    {
        this->stateID.append(block.id);
    }
    this->stateID.append("-");

    for(Block block : this->l3)
    {
        this->stateID.append(block.id);
    }
}

void State::updateRelations()
{
    for(int i = 0; i < this->l1.size(); i++)
    {
        this->l1[i].clearRelations();
    }

    for(int i = 0; i < this->l2.size(); i++)
    {
        this->l2[i].clearRelations();
    }

    for(int i = 0; i < this->l3.size(); i++)
    {
        this->l3[i].clearRelations();
    }

    // Assign relationships
    this->assignClear();
    this->assignTable();
    this->assignOn();
    this->setID();
}

bool State::equals(State otherState)
{
    // Comapre state IDs
    if (this->stateID == otherState.stateID)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void State::assignClear()
{
    int l1Length = this->l1.length();
    int l2Length = this->l2.length();
    int l3Length = this->l3.length();



    // Start with L1
    if(l1Length > 0)
    {
        this->l1.top().addRelation(Relation(CLEAR));
    }

    // L2
    if(l2Length > 0)
    {
        this->l2.top().addRelation(Relation(CLEAR));
    }

    // L3
    if(l3Length > 0)
    {
        this->l3.top().addRelation(Relation(CLEAR));
    }
}

void State::assignTable()
{
    int l1Length = this->l1.length();
    int l2Length = this->l2.length();
    int l3Length = this->l3.length();

    // Start with L1
    if(l1Length > 0)
    {
        this->l1.first().addRelation(Relation(TABLE));
    }

    // L2
    if(l2Length > 0)
    {
        this->l2.first().addRelation(Relation(TABLE));
    }

    // L3
    if(l3Length > 0)
    {
        this->l3.first().addRelation(Relation(TABLE));
    }
}

void State::assignOn()
{
    // For each block in the stack, if the current block has a block below it, it is ON that block.
    // L1
    for(int i = 1; i < this->l1.size(); i++)
    {
        this->l1[i].addRelation(Relation(ON, this->l1[i].id, this->l1[i-1].id));
    }

    // L2
    for(int i = 1; i < this->l2.size(); i++)
    {
        this->l2[i].addRelation(Relation(ON, this->l2[i].id, this->l2[i-1].id));
    }

    // L3
    for(int i = 1; i < this->l3.size(); i++)
    {
        this->l3[i].addRelation(Relation(ON, this->l3[i].id, this->l3[i-1].id));
    }
}

void State::setL1(QStack<Block> stack)
{
    this->l1 = stack;
    this->updateRelations();

}

void State::setL2(QStack<Block> stack)
{
    this->l2 = stack;
    this->updateRelations();

}

void State::setL3(QStack<Block> stack)
{
    this->l3 = stack;
    this->updateRelations();

}

void State::toString()
{
    for(int i = 0; i < l1.size(); i++)
    {
       qDebug() << l1[i].id << ": ";
        for(int j = 0; j < l1[i].relations.size(); j++)
        {
          qDebug() << l1[i].relations[j].toString();
        }
    }
}

