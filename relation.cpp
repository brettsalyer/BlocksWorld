#include "relation.h"

Relation::Relation()
{
    this->fromBlock = NULL;
    this->toBlock = NULL;
}

Relation::Relation(QString relationType, QChar fromBlock, QChar toBlock)
{
    this->relationType = relationType;
    this->fromBlock = fromBlock;
    this->toBlock = toBlock;
}

Relation::Relation(QString relationType)
{
    this->relationType = relationType;
    this->fromBlock = NULL;
    this->toBlock = NULL;
}

void Relation::setRelation(QString relationType, QChar fromBlock, QChar toBlock)
{
    setRelationType(relationType);
    setFromBlock(fromBlock);
    setToBlock(toBlock);
}

QString Relation::toString()
{
    if(this->fromBlock != NULL && this->toBlock != NULL)
        return QString(this->getRelationType() + "(" + this->getFromBlock() + ", " + this->getToBlock() + ")");
    else
        return QString(this->getRelationType());
}

QString Relation::getRelationType()
{
    return this->relationType;
}

QChar Relation::getFromBlock()
{
    return this->fromBlock;
}

QChar Relation::getToBlock()
{
    return this->toBlock;
}

void Relation::setRelationType(QString relationType)
{
    this->relationType = relationType;
}

void Relation::setFromBlock(QChar fromBlock)
{
    this->fromBlock = fromBlock;
}

void Relation::setToBlock(QChar toBlock)
{
    this->toBlock = toBlock;
}
