cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)

add_executable(TicTacToe main.cpp MCTS.h MCTS.cpp Node.cpp Node.h State.cpp State.h Board.cpp Board.h UCT.cpp UCT.h Tree.cpp Tree.h Other.cpp Other.h)