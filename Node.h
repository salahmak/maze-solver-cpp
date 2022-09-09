#pragma once
#include <string>

class Node
{
public:
    Node(std::pair<int, int>, Node, std::string = "");
    Node(std::pair<int, int>, std::string = "");

    std::pair<int, int> getState() const;
    Node* getParent() const;
    std::string getAction() const;
    

private:
    // the state is the coords of the pos in the maze
    std::pair<int, int> state;

    Node *parent = nullptr;

    std::string action;
};
