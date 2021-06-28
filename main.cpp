#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "MCTS.h"
#include "Board.h"
#include "Other.h"


int main() {
    srand(time(0));
    int DRAW_CNT = 0;
    int MCTS_CNT = 0;
    int RANDOM_CNT = 0;
    for (int i = 0; i < 50; i++) {
        Board *board = new Board();
        while (1) {
            int a, b;
//        cin >> a >> b;
//        if (a != -1) {
//            board->performMove(OPPONENT, {a, b});
//        }
//            vector<Position> possibleMoves;
//            board->getAvailableMoves(possibleMoves);
//            int index = rand() % (possibleMoves.size());
//            board->performMove(OPPONENT, possibleMoves[index]);
//            int n;
//        cin >> n;
//        for (int i = 0; i < n; i++) {
//            int m1, m2;
//            cin >> m1 >> m2;
//        }
            COMP = 3;
            OPPONENT = 4;
            MonteCarloTreeSearch *mcts1 = new MonteCarloTreeSearch();
            Position pos1 = mcts1->findNextMove(*board, COMP);
            board->performMove(COMP, {pos1.x, pos1.y});
            if (board->checkStatus() != Board::IN_PROGRESS) {
                if (board->checkStatus() != Board::DRAW) {
                    MCTS_CNT++;
                    std::cout << "MCTS_WIN" << std::endl;
                } else {
                    DRAW_CNT++;
                    std::cout << "DRAW" << std::endl;
                }
                break;
            }
            //cout << pos.x << ' ' << pos.y << endl;
            std::vector<Position> possibleMoves;
            board->getAvailableMoves(possibleMoves);
            int index = rand() % (possibleMoves.size());
            board->performMove(OPPONENT, possibleMoves[index]);
            if (board->checkStatus() != Board::IN_PROGRESS) {
                if (board->checkStatus() != Board::DRAW) {
                    RANDOM_CNT++;
                    std::cout << "MCTS2_WIN" << std::endl;
                } else {
                    DRAW_CNT++;
                    std::cout << "DRAW" << std::endl;
                }
                break;
            }
            delete mcts1;
        }
        std::cout << "GAME " << i + 1 << " FINISHED" << std::endl;
    }
    std::cout << "RANDOM: " << RANDOM_CNT << std::endl;
    std::cout << "DRAW: " << DRAW_CNT << std::endl;
    std::cout << "MCTS: " << MCTS_CNT << std::endl;
}

