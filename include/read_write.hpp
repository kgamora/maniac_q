#pragma once

#include "board.hpp"

#include <string>
#include <iostream>
#include <map>
#include <algorithm>

std::string translatePosition(Position position);
std::string translateFence(Position position, bool isHorizontal);
void printBoard(const Board& board);
