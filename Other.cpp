#include "Other.h"

int COMP, OPPONENT;

int changePlayer(int player) {
    if (player == COMP)return OPPONENT;
    else return COMP;
}
