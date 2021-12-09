#include "utilities.h"
#include <QFile>
#include <QTextStream>
#include "block.h"
#include <QDebug>

Utilities::Utilities()
{

}

void Utilities::readStateFile(QString file)
{
    State initialState;
    State finalState;

    // Create file
    QFile inputFile(file);
    if(inputFile.open((QIODevice::ReadOnly)))
    {
        // Read input
        QTextStream in(&inputFile);
        for(int i = 0; i < 6; i++)
        {
            QString line = in.readLine();
            if (line != 32)
            {

                QStringList blocks = line.split(" ");

                QStack<Block> temp;
                // Loop through blocks at this location
                for(int j = 0; j < blocks.size(); j++)
                {
                    Block block(blocks[j].back());
                    temp.append(block);
                }

                switch(i){
                // If this is the first line
                case 0:
                    initialState.setL1(temp);
                    temp.clear();
                    break;
                // If this is the second line
                case 1:
                    initialState.setL2(temp);
                    temp.clear();
                    break;
                // If this is line 3
                case 2:
                    initialState.setL3(temp);
                    temp.clear();
                    break;
                // If this is line 4
                case 3:
                    finalState.setL1(temp);
                    temp.clear();
                    break;
                // If this is line 5
                case 4:
                    finalState.setL2(temp);
                    temp.clear();
                    break;
                // If this is line 6
                case 5:
                    finalState.setL3(temp);
                    temp.clear();
                    break;

                }
            }


        }
    }
    else
    {
        qDebug() << "File not found..";
    }

    this->initialState = initialState;
    this->finalState = finalState;

}

State Utilities::getInitialState()
{
    return this->initialState;
}

State Utilities::getFinalState()
{
    return this->finalState;
}


