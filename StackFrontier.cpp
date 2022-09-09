#include "StackFrontier.h"
#include <algorithm>

void StackFrontier::add(Node node)
{
    this->frontier.push_back(node);
}

bool StackFrontier::contains(NodeState state)
{
    for(Node node : frontier)
    {
        if(node.getState() == state)
        {
            return true;
        }
    }

    return false;
}

bool StackFrontier::empty()
{
    return this->frontier.empty();
}


Node StackFrontier::remove()
{
    if(this->empty())
    {
        throw("Frontier is empty");
    }
    else
    {
        Node last = frontier[frontier.size() - 1];
        frontier.pop_back();
        return last;
    }
}
