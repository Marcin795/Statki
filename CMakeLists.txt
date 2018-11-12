cmake_minimum_required(VERSION 3.12)
project(Statki)

set(CMAKE_CXX_STANDARD 17)

add_executable(Statki main.cpp Board.cpp Board.h Player.cpp Player.h Human.cpp Human.h Bot.cpp Bot.h Game.cpp Game.h)