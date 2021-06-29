#include "Tree.h"

const Node &Tree::getRoot() const {
    return *root;
}

void Tree::setRoot(Node *newRoot) {
    root = newRoot;
}

Tree::Tree(Node *root) : root(root) {}

void Tree::rerootByBoard(State *state) {
    for (auto el: root->getChildren()) {
        if (el->getState() == state) {
            this->setRoot(el);
            return;
        }
    }
    Node *newNode = new Node(state);
    this->setRoot(newNode);
}