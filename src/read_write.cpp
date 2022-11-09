//
// Created by ksgamora on 08.11.22.
//

#include "read_write.hpp"

/*
 * A Forsyth–Edwards Notation-like record
 */


//Board read() {
//    Board board;
//    std::string gamePosition;
//
//    //horizontal wall positions
//    std::cin >> gamePosition;
//
//    if (gamePosition[0] != '/') {
//        for (char c : gamePosition) {
//            uint8_t col = cols[*i];
//            i++;
//            uint8_t row = *i - '0';
//            state.addFence(true, std::make_pair(row, col));
//        }
//        std::cin >> gamePosition;
//    }
//
//    //vertical wall positions
//    std::cin >> gamePosition;
//
//    if (gamePosition[0] != '/') {
//        for (auto i = gamePosition.begin(); i != gamePosition.end(); ++i) {
//            uint8_t col = cols[*i];
//            i++;
//            uint8_t row = *i - '0';
//            state.addFence(false, std::make_pair(row, col));
//        }
//        std::cin >> gamePosition;
//    }
//
//    //p1 position
//    std::cin >> gamePosition;
//    uint8_t row = gamePosition[1] - '0';
//    uint8_t col = cols[gamePosition[0]];
//    state.setP1(std::make_pair(row, col));
//
//    //p2 position
//    std::cin >> gamePosition;
//    row = gamePosition[1] - '0';
//    col = cols[gamePosition[0]];
//    board.setP2({row, col});
//
//    std::cin >> gamePosition;
//
//    //walls
//    std::cin >> gamePosition;
//    board.setP1Fences(gamePosition[0] - '0');
//    std::cin >> gamePosition;
//    board.setP2Fences(gamePosition[0] - '0');
//
//    std::cin >> gamePosition;
//
//    //who's turn
//    std::cin >> gamePosition;
//    board.setActivePlayer(gamePosition[0] == '1');
//
//    return board;
//}

/*
 * writes current position in Forsyth–Edwards Notation-like record, e.g. "d4f4e7 / a2a8 / e4 e6 / 7 8 / 2"
 */

void writePosition(const Board& board) {

}

/*
 * prints state in ASCII notation
 */

void printBoard(const Board& board) {
    Position p1Pos = board.getP1();
    Position p2Pos = board.getP2();

    const std::vector<Position>& verticalWalls = board.getVerticalFences();
    const std::vector<Position>& horizontalWalls = board.getHorizontalFences();

    for (int i = 0; i < 19; ++i) {
        std::string line;
        if (i == 0 or i == 18) {
            line.append('+' + std::string(35, '-') + '+');
        } else {
            if (i % 2 == 0) {
                for (int j = 0; j < 9; ++j) {
                    if (j == 0) {
                        line.append("|");
                    } else {
                        line.append("+");
                    }
                    uint8_t wallRow = i / 2;
                    uint8_t wallCol = j + 1;
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
                for (int j = 0; j < 9; ++j) {
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
                        uint8_t wallRow = (i - 1) / 2;
                        uint8_t rowCol = j + 1;
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