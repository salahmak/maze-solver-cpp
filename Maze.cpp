#include "Maze.h"
#include "QueueFrontier.h"
#include <fstream>
#include <iostream>
#include <algorithm>

Maze::Maze(const string& filename)
{
    std::ifstream myfile;
    myfile.open(filename);

    string line;

    string tile;

    int i = 0;
    int j = 0;

    int maxWidth = 0;

    // parsing the maze file
    while (getline(myfile, line))
    {
        vector<bool> row;

        j = 0;

        for (char c : line)
        {
            row.push_back(c == '#');

            if (c == 'A')
            {
                this->start = std::make_pair(i, j);
            }
            else if (c == 'B')
            {
                this->goal = std::make_pair(i, j);
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


    height = i;
    width = maxWidth;

}

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

// node state is coordinates (i, j) of a node
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
        if(frontier.empty())
        {
            throw "no solution";
        }

        Node node = frontier.remove();
        numExplored++;

        if(node.getState() == this->goal)
        {
             while(node.getParent() != nullptr)
             {
                 //inserting the action at the start of the solution actions array
                 this->solutionActions.insert(solutionActions.begin(), node.getAction());

                 //inserting the current node state at the start of the solution cells array
                 this->solutionCells.insert(solutionCells.begin(), node.getState());

                 node = *node.getParent();
             }

            std::cout << this->numExplored << std::endl;
            return;
        }


        //adding the current node to the explored states array
        this->explored.push_back(node.getState());

        //adding the neighbors to the frontier
        for(const pair<string, NodeState>& neighbor : neighbors(node.getState()))
        {

            bool isNotExplored = std::find(explored.begin(), explored.end(), neighbor.second) == explored.end();

            //neighbor.second is the NodeState
            if(!frontier.contains(neighbor.second) && isNotExplored)
            {
                Node child = Node(neighbor.second, node, neighbor.first);
                frontier.add(child);
            }
        }
    }
}

std::vector<std::string> Maze::getSolActions()
{
    solve();
    return this->solutionActions;
}