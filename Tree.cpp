#include "Tree.h"

const Node &Tree::getRoot() const {
    return *root;
}

void Tree::setRoot(Node *newRoot) {
    root = newRoot;
}

Tree::Tree(Node *root) : root(root) {}
