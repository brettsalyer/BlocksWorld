#ifndef BLOCK_H
#define BLOCK_H

#include <QStringList>
#include <QChar>
#include <QList>
#include "relation.h"

class Block
{
    public:
        Block();
        Block(QChar blockId);

        // Member variables
        QChar id = ' ';  // Char used to represent a block (A-G)
        QList<Relation> relations; // A list of relationships this block has with others

        // Methods

        // Gets the block id
        QChar getBlockId();

        // Sets the block id
        void setBlockId(QChar id);

        // Get the relationships
        QList<Relation> getRelations();

        // Sets the relationships
        void setRelations(QList<Relation> list);

        // Add a relation to the list
        void addRelation(Relation rel);

        // Clear relationships
        void clearRelations();


    private:


};

#endif // BLOCK_H
