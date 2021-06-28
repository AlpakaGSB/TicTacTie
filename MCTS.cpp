#include "MCTS.h"

Node *MonteCarloTreeSearch::selectPromisingNode(Node *rootNode) {
    Node *node = rootNode;
    while (!node->getChildren().empty()) {
        node = UCT::findBestMoveWithUct(node);
    }
    return node;
}

void MonteCarloTreeSearch::expandNode(Node &node) {
    std::vector<State> possibleStates = node.getState()->getAllPossibleStates();
    for (const auto &state:possibleStates) {
        State *nstate = new State(state);
        Node *newNode = new Node(nstate);
        newNode->setParent(&node);
        newNode->getState()->setPlayerNo(node.getState()->getOpponent());
        newNode->getState()->setVisitCount(0);
        newNode->getState()->setWinScore(0);
        node.addChild(newNode);
    }
}

void MonteCarloTreeSearch::backPropagation(Node *nodeToExplore, int playerNo, Node *root) {
    int player = Board::DRAW;
    if (playerNo == Board::COMP_WIN)player = COMP;
    else if (playerNo == Board::OPPONENT_WIN)player = OPPONENT;
    root->getState()->incrementVisit();
    Node *tempNode = nodeToExplore;
    while (tempNode != root) {
        tempNode->getState()->incrementVisit();
        if (player == Board::DRAW) {
            tempNode->getState()->addScore(0.5);
        } else if (tempNode->getState()->getPlayerNo() != player) {
            tempNode->getState()->addScore(WIN_SCORE);
        }
        tempNode = tempNode->getParent();
    }
}

int MonteCarloTreeSearch::simulateRandomPlayout(const Node &node) {
    Node *tempNode = new Node(node);
    State *tempState = new State();
    tempState->setBoard(tempNode->getState()->getBoard());
    tempState->setPlayerNo(tempNode->getState()->getPlayerNo());
    int boardStatus = tempState->getBoard().checkStatus();
    if (boardStatus == Board::DRAW) {
        return boardStatus;
    }
    if (boardStatus == Board::OPPONENT_WIN || boardStatus == Board::COMP_WIN) {
        tempNode->getParent()->getState()->setWinScore(-INF);
        tempNode->getState()->setWinScore(INF);
        return boardStatus;
    }
    while (boardStatus == Board::IN_PROGRESS) {
        tempState->randomPlay();
        boardStatus = tempState->getBoard().checkStatus();
    }
    return boardStatus;
}

Position MonteCarloTreeSearch::findNextMove(Board board, int playerNo) {
    opponent = changePlayer(playerNo);
    State *state = new State();
    state->setPlayerNo(playerNo);
    state->setBoard(board);
    Node *root = new Node(state);
    Tree *tree = new Tree(root);
    Node *rootNode = root;
    //rootNode->setParent(nullptr);
    int cnt = 10000;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    while (std::chrono::duration_cast<std::chrono::milliseconds>(end - start) < TIME_LIMIT) {
        Node *promisingNode = selectPromisingNode(rootNode);
        if (promisingNode->getState()->getBoard().checkStatus() == Board::IN_PROGRESS &&
            promisingNode->getState()->getVisitCount()) {
            expandNode(*promisingNode);
        }
        Node *nodeToExplore = promisingNode;
        if (!promisingNode->getChildren().empty()) {
            nodeToExplore = promisingNode->getRandomChildNode();
        }
        int playoutResult = simulateRandomPlayout(*nodeToExplore);
        backPropagation(nodeToExplore, playoutResult, rootNode);
        end = std::chrono::steady_clock::now();
    }
    Node winnerNode = rootNode->getChildWithMaxScore();
    //tree->setRoot(&winnerNode);
    std::cerr << tree->getRoot().getState()->getVisitCount() << ' ';

    auto result = winnerNode.getState()->getBoard().getLastPosition();
    //Node::deleteTree(rootNode);
    Node::deleteTree(root);
    return result;
}