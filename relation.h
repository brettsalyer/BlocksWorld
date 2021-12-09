#ifndef RELATION_H
#define RELATION_H

#include <QString>

class Relation
{

public:
    // default
    Relation();

    // For blocks that have relations like CLEAR and TABLE, where there is no association with other
    // blocks when describing these relations.
    Relation(QString relationType);

    // Creates a new relation, relation, from block fromBlock onto block toBlock
    Relation(QString relationType, QChar fromBlock, QChar toBlock);

    // Member variables
    QString relationType = "";
    QChar  fromBlock;
    QChar toBlock;


    // Member methods

    // Converts the current relationship to a human-readable string format
    QString toString();

    // Set relation
    void setRelation(QString relationType, QChar fromBlock, QChar toBlock);

    // Gets the relation type
    QString getRelationType();

    // Gets the relation fromId
    QChar getFromBlock();

    // Get the relation toId
    QChar getToBlock();

    // Sets the relation type
    void setRelationType(QString relationType);

    // Sets the relation fromId
    void setFromBlock(QChar fromBlock);

    // Sets the relation toId
    void setToBlock(QChar toBlock);




private:

};

#endif // RELATION_H
