#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include "MCTS.h"
#include "Board.h"
#include "Other.h"
#include "MiniMax.h"


int main() {
    srand(time(0));
    int DRAW_CNT = 0;
    int MCTS_CNT = 0;
    int MINIMAX_CNT = 0;
    for (int i = 0; i < 25; i++) {
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
            //cout << pos.x << ' ' << pos.y << endl;

            COMP_WIN = 2;
            OPPONENT_WIN = 1;
            COMP = 4;
            OPPONENT = 3;
            MonteCarloTreeSearch *mcts = new MonteCarloTreeSearch();
            Position pos2 = mcts->findNextMove(*board, COMP);
            board->performMove(COMP, {pos2.x, pos2.y});

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
            COMP_WIN = 1;
            OPPONENT_WIN = 2;
            COMP = 3;
            OPPONENT = 4;
            Position pos1 = minimax::findNextMoveWithTimeLimit(*board, minimax::evaluate2, 10000);
            board->performMove(COMP, {pos1.x, pos1.y});
            if (board->checkStatus() != Board::IN_PROGRESS) {
                if (board->checkStatus() != Board::DRAW) {
                    MINIMAX_CNT++;
                    std::cout << "MINIMAX_WIN" << std::endl;
                } else {
                    DRAW_CNT++;
                    std::cout << "DRAW" << std::endl;
                }
                break;
            }
        }
        std::cout << "GAME " << i + 1 << " FINISHED" << std::endl;
        delete board;
    }
    std::cout << "MINIMAX: " << MINIMAX_CNT << std::endl;
    std::cout << "DRAW: " << DRAW_CNT << std::endl;
    std::cout << "MCTS: " << MCTS_CNT << std::endl;
}

