#pragma once

#include "board.hpp"
#include "read_write.hpp"

Board parseMove(const Board& currentState, const std::string& move);