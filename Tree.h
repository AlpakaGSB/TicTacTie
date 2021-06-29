#pragma once

#include "Node.h"

class Tree {
private:
    Node *root;
public:
    void rerootByBoard(State* state);

    const Node &getRoot() const;

    void setRoot(Node *newRoot);

    Tree(Node *root);

};