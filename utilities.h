#ifndef UTILITIES_H
#define UTILITIES_H

#include "state.h"

class Utilities
{
public:
    Utilities();

    State initialState;
    State finalState;

    // Initial & Final state file format

    /*
     * Line 1: Initial State L1 Stack <Block ID> <Block ID> <Block ID> ...
     * Line 2: Initial State L2 Stack <Block ID> <Block ID> <Block ID> ...
     * Line 3: Initial State L3 Stack <Block ID> <Block ID> <Block ID> ...
     * Line 4: Final State L1 Stack <Block ID> <Block ID> <Block ID> ...
     * Line 5: Final State L2 Stack <Block ID> <Block ID> <Block ID> ...
     * Line 6: Final State L3 Stack <Block ID> <Block ID> <Block ID> ...
    */

    void readStateFile(QString file);

    State getInitialState();

    State getFinalState();

};

#endif // UTILITIES_H
