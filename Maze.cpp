#include "Maze.h"
#include "QueueFrontier.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Maze::Maze(const string& filename)
{
    std::ifstream myfile;
    myfile.open(filename);

    // a string that will read each line in the file (row)
    string line;

    //counters, i for rows, j for cols
    int i = 0;
    int j = 0;

    //will use it to find out the width of the maze
    int maxWidth = 0;


    // to track how many start/end points exist in the maze, to make sure there is exactly 1 for each
    int startPointsCount = 0;
    int endPointsCount = 0;

    // parsing the maze file
    while (getline(myfile, line))
    {
        // an array that will store the current row, and then pushed to the walls 2D array
        vector<bool> row;

        //resetting j after each row
        j = 0;

        // looping over columns of the current row
        for (char tile : line)
        {
            // if current tile is a wall, we push true to the row array, otherwise we push false
            row.push_back(tile == '#');

            //initializing the start and end point
            if (tile == 'A')
            {
                this->start = std::make_pair(i, j);
                startPointsCount++;
            }
            else if (tile == 'B')
            {
                this->goal = std::make_pair(i, j);
                endPointsCount++;
            }

            j++;

            if(j > maxWidth)
            {
                maxWidth = j;
            }
        }

        this->walls.push_back(row);

        i++;
    }


    if(startPointsCount != 1 || endPointsCount != 1)
    {
        throw std::runtime_error("Please provide exactly 1 start and 1 end point");
    }

    height = i;
    width = maxWidth;

}

/*
 * A function that prints the maze, if it is solved, it will draw the path of the solution
 * */
void Maze::print()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(std::make_pair(i, j) == start)
            {
                std::cout << 'A';
            }
            else if(std::make_pair(i, j) == goal)
            {
                std::cout << 'B';
            }
            else if (walls[i][j])
            {
                std::cout << "█";
            }
            else if (std::find(solutionCells.begin(), solutionCells.end(), std::make_pair(i, j)) != solutionCells.end())
            {
                std::cout << "+";
            }
            else
            {
                std:: cout << ' ';
            }
        }
        std::cout << std::endl;
    }
}

/*
 * A function that returns an array of pairs of type: <string: action, NodeState>
 * where NodeState is a pair of type: <int: row, int: col>
 * */
vector<pair<string, NodeState>> Maze::neighbors(NodeState node)
{
    int row = node.first;
    int col = node.second;


    //possible movements
    vector<pair<string, NodeState>> candidates = {
        {"up", {row - 1, col}},
        {"down", {row + 1, col}},
        {"right", {row, col + 1}},
        {"left", {row, col - 1}},
    };


    vector<pair<string, NodeState>> results;

    // we check if a movement is allowed to get neighbors that we can move to
    for(const pair<string, NodeState>& candidate : candidates)
    {   
        // (action, (r, c))
        string action = candidate.first;

        int r = candidate.second.first;
        int c = candidate.second.second;



        // (r >= 0 && r <= height): not outside of height range
        // (c >= 0 && c <= width): not outside of width range
        // walls[r][c] == false :  movement doesn't lead us to a wall
        if((r >= 0 && r < height) && (c >= 0 && c < width))
        {
            if(!walls[r][c])
            {
                results.push_back(candidate);
            }
        }
    }

    return results;


}



void Maze::solve()
{

    // initializing the start node
    Node startNode(this->start);

    //init the frontier and adding the start node to it
    QueueFrontier frontier;
    frontier.add(startNode);

    while(true)
    {
        // if the frontier is empty, then there is no solution
        if(frontier.empty())
        {
            throw std::runtime_error("no solution");
        }

        // we pick a node from the frontier to work with (we remove it from the frontier and work with it)
        Node node = frontier.remove();

        // we have explored 1 more node
        numExplored++;

        //if the current node we picked is the goal
        if(node.getState() == this->goal)
        {
            //we backtrace the nodes to get the full solution history
             while(node.getParent() != nullptr)
             {
                 //inserting the action at the start of the solution actions array
                 this->solutionActions.insert(solutionActions.begin(), node.getAction());

                 //inserting the current node state at the start of the solution cells array
                 this->solutionCells.insert(solutionCells.begin(), node.getState());

                 // we swap the current node with its parent (to go backwards)
                 node = *node.getParent();
             }

             // when there is a solution, we return from the solve() function
            return;
        }


        // when the current node is not the solution, we get possible moves and add them to the frontier and we continue again

        //adding the current node to the explored states array
        this->explored.push_back(node.getState());

        //adding the neighbor tiles to the frontier
        for(const pair<string, NodeState>& neighbor : neighbors(node.getState()))
        {

           /*
            * neighbor.first: action
            * neighbor.second: NodeState (i, j)
           */

            // to check that the current NodeState is not explored
            bool isNotExplored = std::find(explored.begin(), explored.end(), neighbor.second) == explored.end();

            // if the current neighbor's state isn't inside the frontier and not explored before
            // we create a child node and add it to the frontier
            if(!frontier.contains(neighbor.second) && isNotExplored)
            {
                // node is the parent of the child, since we got to child by making 1 move from node (neighbor)
                Node child = Node(neighbor.second, node, neighbor.first);
                frontier.add(child);
            }
        }
    }
}

/*
 * getter for solution actions
 * */
std::vector<std::string> Maze::getSolActions()
{
    if(solutionActions.empty())
    {
        throw std::runtime_error("Maze hasn't been solved yet");
    }

    return this->solutionActions;
}