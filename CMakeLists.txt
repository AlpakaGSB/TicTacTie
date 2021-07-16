cmake_minimum_required(VERSION 3.17)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
add_executable(TicTacToe main.cpp MCTS.h MCTS.cpp Node.cpp Node.h State.cpp State.h Board.cpp Board.h UCT.cpp UCT.h Other.cpp Other.h MiniMax.cpp MiniMax.h)