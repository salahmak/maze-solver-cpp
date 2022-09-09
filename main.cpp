#include <iostream>
#include "Maze.h"


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cerr << "Please provide a maze file path as the second argument" << std::endl;
        return 1;
    }

    try{
        Maze maze(argv[1]);

        std::cout << "before solving: \n";
        maze.print();

        maze.solve();

        std::cout << "\n\nafter solving: \n";
        maze.print();

    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}