#include "QueueFrontier.h"

Node QueueFrontier::remove()
{
    if(this->empty())
    {
        throw("Frontier is empty");
    }
    else
    {
        Node first = this->frontier[0];
        frontier.erase(frontier.begin());
        return first;
    }
}