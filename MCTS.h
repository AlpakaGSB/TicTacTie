#pragma once

#include "Node.h"
#include "UCT.h"
#include "Tree.h"

class MonteCarloTreeSearch {
private:
    static const int WIN_SCORE = 1;
    int level;
    int opponent;

    Node *selectPromisingNode(Node *rootNode);

    static void expandNode(Node &node);

    void backPropagation(Node *nodeToExplore, int playerNo, Node *root);

    static int simulateRandomPlayout(const Node &node);

public:
    Position findNextMove(Board board, int playerNo);
};


