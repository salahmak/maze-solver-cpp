#pragma once

#include <string>
#include <vector>
#include "Node.h"
#include "StackFrontier.h"

typedef std::pair<int, int>  NodeState;

using std::vector;
using std::pair;
using std::string;

class Maze
{
public:

    //opens a file and parses it into an array
    explicit Maze(const std::string&);


    // a function that returns an array of pairs (action, (x, y))
    vector<pair<string, NodeState>> neighbors(NodeState);


    //solves the maze
    void solve();

    void print();

    std::vector<std::string> getSolActions();


private:
    // a 2d array of walls (true of wall, false if not wall)
    std::vector<std::vector<bool>> walls;
    
    int height, width;

    //solutions
    std::vector<std::string> solutionActions;
    std::vector<NodeState> solutionCells;

    //num of explored paths
    int numExplored = 0;


    // set of explored nodes
    std::vector<NodeState> explored;

    NodeState start;
    NodeState goal;


};