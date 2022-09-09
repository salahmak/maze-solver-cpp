#pragma once
#include "StackFrontier.h"


class QueueFrontier : public StackFrontier
{
public:
    virtual Node remove();
};
