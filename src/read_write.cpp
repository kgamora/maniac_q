//
// Created by ksgamora on 08.11.22.
//

#include "read_write.hpp"

std::string translatePosition(Position position) {
    char first = 'a' + static_cast<char>(position.col);
    char second = '1' + static_cast<char>(position.row);
    std::string result = std::string (1, first);
    result.append(std::string(1, second));
    return result;
}

std::string translateFence(Position position, bool isHorizontal) {
    std::string result = translatePosition(position);
    if (isHorizontal) {
        result.append("h");
    } else {
        result.append("v");
    }
    return result;
}

/*
 * prints board in ASCII notation
 */
void printBoard(const Board& board) {
//    Position p1Pos = board.getP1();
    Position p1Pos = board.getPlayerPos(0);
//    Position p2Pos = board.getP2();
    Position p2Pos = board.getPlayerPos(1);

    const std::vector<Position>& verticalWalls = board.getVerticalFences();
    const std::vector<Position>& horizontalWalls = board.getHorizontalFences();

    for (int i = 0; i < 19; ++i) {
        std::string line;
        if (i == 0 or i == 18) {
            line.append('+' + std::string(35, '-') + '+');
        } else {
            if (i % 2 == 0) {
                for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
                    if (j == 0) {
                        line.append("|");
                    } else {
                        line.append("+");
                    }
                    int wallRow = i / 2;
                    int wallCol = j + 1;
                    if (std::find(horizontalWalls.cbegin(), horizontalWalls.cend(), Position(wallRow, wallCol)) != horizontalWalls.cend()
                    || std::find(horizontalWalls.cbegin(), horizontalWalls.cend(), Position(wallRow, wallCol - 1)) != horizontalWalls.cend()) {
                        line.append(std::string(3, '-'));
                    } else {
                        line.append(std::string(3, ' '));
                    }
                }
                line.append("|");
            } else {
                line.append("|");
                for (int j = 0; j < BOARD_SIDE_LENGTH; ++j) {
                    if (i == (p1Pos.row) * 2 + 1 and j == p1Pos.col) {
                        line.append(" X ");
                    } else if (i == (p2Pos.row) * 2 + 1 and j == p2Pos.col) {
                        line.append(" O ");
                    } else {
                        line.append(std::string(3 , ' '));
                    }
                    if (j == 8) {
                        line.append("|");
                    } else {
                        int wallRow = (i - 1) / 2;
                        int rowCol = j + 1;
                        if (std::find(verticalWalls.cbegin(), verticalWalls.cend(), Position(wallRow + 1, rowCol)) != verticalWalls.cend()
                        || std::find(verticalWalls.cbegin(), verticalWalls.cend(), Position(wallRow, rowCol)) != verticalWalls.cend()) {
                            line.append("|");
                        } else {
                            line.append(" ");
                        }
                    }
                }
            }
        }
        std::cout << line << std::endl;
    }
}