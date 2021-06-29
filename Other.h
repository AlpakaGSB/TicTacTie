#pragma once

#include <chrono>

using milliseconds = std::chrono::duration<long long, std::milli>;

struct Position {
    int x;
    int y;
};

int changePlayer(int player);

extern int COMP, OPPONENT;

const int INF = 1e9 + 7;
const int MAX_DEPTH = 5;
const milliseconds TIME_LIMIT{1000};