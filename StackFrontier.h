#pragma once

#include <vector>
#include "Node.h"

typedef std::pair<int, int> NodeState;

class StackFrontier
{
public:
    // a function that adds a node to the stack
    void add(Node);

    // a function that tells us whether a node exists in the frontier or not
    bool contains(NodeState);

    // to check if the frontier is empty or not
    bool empty();


    // to remove a node from the end of the stack (LIFO)
    virtual Node remove();


protected:
    std::vector<Node> frontier;
};