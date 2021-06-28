#include "Node.h"

Node Node::getChildWithMaxScore() {
    int mx = -INF;
    Node *res;
    for (Node *child:children) {
        int totalVisit = child->getState()->getVisitCount();
        if (totalVisit > mx) {
            mx = totalVisit;
            res = child;
        }
    }
    return *res;
}

State *Node::getState() const {
    return state;
}

Node::~Node() {
    state = nullptr;
    parent = nullptr;
    children.clear();
}

Node::Node(State *state) : state(state) {}

const std::vector<Node *> &Node::getChildren() const {
    return children;
}

void Node::setParent(Node *newParent) {
    Node::parent = newParent;
}

void Node::addChild(Node *child) {
    Node *node = new Node(*child);
    children.emplace_back(node);
}

Node *Node::getRandomChildNode() {
    int numberOfChildren = static_cast<int>(children.size());
    int pos = rand() % numberOfChildren;
    return children[pos];
}

void Node::deleteTree(Node *node) {
    std::vector<Node *> children = node->getChildren();
    for (Node *child: children) {
        if (child != nullptr)deleteTree(child);
    }
    delete node;
}

Node *Node::getParent() const {
    return parent;
}