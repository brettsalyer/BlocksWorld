#include "block.h"
#include "relation.h"

Block::Block()
{

}

Block::Block(QChar blockId)
{
    this->id = blockId;
}

QChar Block::getBlockId()
{
    return this->id;
}

void Block::setBlockId(QChar id)
{
    this->id = id;
}

QList<Relation> Block::getRelations()
{
    return this->relations;
}

void Block::setRelations(QList<Relation> list)
{
    this->relations = list;
}

void Block::addRelation(Relation rel)
{
    this->relations.append(rel);
}

void Block::clearRelations()
{
    this->relations.clear();
}

