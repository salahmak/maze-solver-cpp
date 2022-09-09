#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <algorithm>

#include "Maze.h"



int main(int argc, char const *argv[])
{
    
    Maze maze("maze.txt");


    // vector<pair<string, NodeState>> n = maze.neighbors(std::make_pair(5, 2));

    // for(pair<string, NodeState> p : n)
    // {
    //     std::cout << p.first << std::endl;
    // }

    std::cout << "before solving: \n";
    maze.print();
    std::vector<std::string> sol = maze.getSolActions();

    for(std::string action : sol)
    {
//        std::cout << action << std::endl;
    }

    std::cout << "\n\nafter solving: \n";
    maze.print();

    return 0;
}





//Queue
