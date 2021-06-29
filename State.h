#pragma once

#include "Board.h"
#include <vector>
#include <iostream>

class State {
private:
    Board board;
    int playerNo;
    int visitCount;
    long double winScore;
public:
    void setBoard(const Board &newBoard);

    std::vector<State> getAllPossibleStates() const;

    void randomPlay();

    const Board getBoard() const;

    int getPlayerNo() const;

    int getOpponent();

    int getVisitCount();

    long double getWinScore() const;

    void setPlayerNo(int newPlayerNo);

    void setVisitCount(int newVisitCount);

    void setWinScore(long double newWinScore);

    void addScore(long double add);

    void incrementVisit();

    void togglePlayer();
};