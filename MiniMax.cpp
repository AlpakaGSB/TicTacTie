#include "MiniMax.h"
#include <algorithm>
#include <random>

Position minimax::findNextMove(const Board &board) {
    Position result = {-1, -1};
    int bestVal = -INF;

    std::vector<Position> moves;
    board.getAvailableMoves(moves);

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(moves.begin(), moves.end(), g);

    for (auto move:moves) {
        Board tempBoard = board;
        tempBoard.performMove(COMP, move);
        int curVal = calculate(tempBoard, 1, OPPONENT, -INF, INF);
        if (curVal > bestVal) {
            bestVal = curVal;
            result = move;
        }
    }
    std::cerr << "<" << bestVal << "> ";
    return result;
}

int minimax::calculate(Board board, int depth, int player, int alpha, int beta) {
    int status = board.checkStatus();
    if (depth == MAX_DEPTH || status != Board::IN_PROGRESS) {
        return evaluate(board, status, depth);
    }
    if (player == COMP) {
        int best = -INF;
        std::vector<Position> moves;
        board.getAvailableMoves(moves);
        for (auto move:moves) {
            Board tempBoard = board;
            tempBoard.performMove(COMP, move);
            int curVal = calculate(tempBoard, depth + 1, OPPONENT, alpha, beta);
            best = std::max(best, curVal);
            alpha = std::max(best, alpha);
            if (beta <= alpha)break;
        }
        return best;
    } else {
        int best = INF;
        std::vector<Position> moves;
        board.getAvailableMoves(moves);
        for (auto move:moves) {
            Board tempBoard = board;
            tempBoard.performMove(OPPONENT, move);
            int curVal = calculate(tempBoard, depth + 1, COMP, alpha, beta);
            best = std::min(best, curVal);
            beta = std::min(best, beta);
            if (beta <= alpha)break;
        }
        return best;
    }

}

int minimax::evaluate(const Board &board, int status, int depth) {
    if (status == COMP_WIN)return 10000 - depth;
    if (status == OPPONENT_WIN)return -10000 + depth;
    if (status == Board::DRAW)return 0;
    int cnt = 0;
    std::vector<std::vector<signed char>> bigField = board.getBigField();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (bigField[i][j] == COMP_WIN)cnt++;
            if (bigField[i][j] == OPPONENT_WIN)cnt--;
        }
    }
    cnt *= 100;
    std::vector<std::vector<signed char>> smallField = board.getSmallField();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (bigField[i][j] != Board::IN_PROGRESS)continue;
            for (int k = 0; k < 3; k++) {
                for (int p = 0; p < 3; p++) {
                    if (smallField[i * 3 + k][j * 3 + p] == COMP)cnt++;
                    if (smallField[i * 3 + k][j * 3 + p] == OPPONENT)cnt--;
                }
            }
        }
    }
    return cnt;
}
