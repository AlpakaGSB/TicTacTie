#pragma once

#include "Node.h"

class Tree {
private:
    Node *root;
public:
    void rerootByBoard(Position pos);

    const Node &getRoot() const;

    void setRoot(Node *newRoot);

    Tree(Node *root);

};