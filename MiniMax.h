#pragma once
#include "Node.h"
class minimax{
public:
    static Position findNextMove(const Board&);
    static int calculate(Board, int, int, int, int);

    static int evaluate(const Board&, int, int);
};
