#pragma once

#include "board.hpp"

#include <string>
#include <iostream>
#include <map>
#include <algorithm>

Board read();
void writePosition(const Board& board);
void printBoard(const Board& board);
