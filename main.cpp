#include <iostream>
#include "Maze.h"


int main()
{
    try{
        Maze maze("maze.txt");

        std::cout << "before solving: \n";
        maze.print();

        maze.solve();

        std::cout << "\n\nafter solving: \n";
        maze.print();

    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}