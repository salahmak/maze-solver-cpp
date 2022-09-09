#include "Node.h"

#include <utility>

std::pair<int, int> Node::getState() const {
    return this->state;
}

Node *Node::getParent() const {
    return parent;
}

std::string Node::getAction() const {
    return action;
}

Node::Node(std::pair<int, int> state, Node node, std::string action) : state(std::move(state)), parent(new Node(std::move(node))),
                                                                       action(std::move(action)) {}

Node::Node(std::pair<int, int> state, std::string action) : state(std::move(state)), action(std::move(action)) {

}