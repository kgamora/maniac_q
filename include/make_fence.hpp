#pragma once

#include "read_write.hpp"

bool checkFence(const Board& currentState, Position pos, bool horizontal);
Board makeFence(Board board_copy, Position pos, bool horizontal);