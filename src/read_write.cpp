//
// Created by ksgamora on 08.11.22.
//

#include "read_write.hpp"

/*
 * A Forsyth–Edwards Notation-like record
 */

std::map<char, uint8_t> cols {{'a', 1}, {'b', 2}, {'c', 3}, {'d', 4}, {'e', 5}, {'f', 6}, {'g', 7}, {'h', 8}, {'i', 9},};

State read () {
    State state;
    std::string gamePosition;

    //horizontal wall positions
    std::cin >> gamePosition;

    if (gamePosition[0] != '/') {
        for (auto i = gamePosition.begin(); i != gamePosition.end(); ++i) {
            uint8_t col = cols[*i];
            i++;
            uint8_t row = *i - '0';
            state.addFence(true, std::make_pair(row, col));
        }
        std::cin >> gamePosition;
    }


    //vertical wall positions
    std::cin >> gamePosition;

    if (gamePosition[0] != '/') {
        for (auto i = gamePosition.begin(); i != gamePosition.end(); ++i) {
            uint8_t col = cols[*i];
            i++;
            uint8_t row = *i - '0';
            state.addFence(false, std::make_pair(row, col));
        }
        std::cin >> gamePosition;
    }

    //p1 position
    std::cin >> gamePosition;
    uint8_t row = gamePosition[1] - '0';
    uint8_t col = cols[gamePosition[0]];
    state.setP1(std::make_pair(row, col));

    //p2 position
    std::cin >> gamePosition;
    row = gamePosition[1] - '0';
    col = cols[gamePosition[0]];
    state.setP2(std::make_pair(row, col));

    std::cin >> gamePosition;

    //walls
    std::cin >> gamePosition;
    state.setP1Fences(gamePosition[0] - '0');
    std::cin >> gamePosition;
    state.setP2Fences(gamePosition[0] - '0');

    std::cin >> gamePosition;

    //who's turn
    std::cin >> gamePosition;
    state.setActivePlayer(gamePosition[0] == '1');

    return state;
}

/*
 * writes current position in Forsyth–Edwards Notation-like record, e.g. "d4f4e7 / a2a8 / e4 e6 / 7 8 / 2"
 */

void writePosition (State state) {

}

/*
 * prints state in ASCII notation
 */

void printState (State state) {

    std::pair<uint8_t, uint8_t> p1Pos = state.getP1();
    std::pair<uint8_t, uint8_t> p2Pos = state.getP2();

    std::vector<std::pair<uint8_t, uint8_t>> verticalWalls = state.getVerticalFences();
    std::vector<std::pair<uint8_t, uint8_t>> horizontalWalls = state.getHorizontalFences();

    for (int i = 0; i < 19; ++i) {
        std::string line;
        if (i == 0 or i == 18) {
            line.append("+");
            line.append(std::string(35, '-'));
            line.append("+");
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
                    std::pair<uint8_t, uint8_t> item = std::make_pair(wallRow, wallCol);
                    std::pair<uint8_t, uint8_t> item2 = std::make_pair(wallRow, wallCol - 1);
                    if (std::find(horizontalWalls.begin(), horizontalWalls.end(), item) != horizontalWalls.end()
                    or std::find(horizontalWalls.begin(), horizontalWalls.end(), item2) != horizontalWalls.end()) {
                        line.append(std::string(3, '-'));
                    } else {
                        line.append(std::string(3, ' '));
                    }
                }
                line.append("|");
            } else {
                line.append("|");
                for (int j = 0; j < 9; ++j) {
                    if (i == (p1Pos.first) * 2 + 1 and j == p1Pos.second) {
                        line.append(" X ");
                    } else if (i == (p2Pos.first) * 2 + 1 and j == p2Pos.second) {
                        line.append(" O ");
                    } else {
                        line.append(std::string(3 , ' '));
                    }
                    if (j == 8) {
                        line.append("|");
                    } else {
                        uint8_t wallRow = (i - 1) / 2;
                        uint8_t rowCol = j + 1;
                        std::pair<uint8_t, uint8_t> item = std::make_pair(wallRow + 1, rowCol);
                        std::pair<uint8_t, uint8_t> item2 = std::make_pair(wallRow, rowCol);
                        if (std::find(verticalWalls.begin(), verticalWalls.end(), item) != verticalWalls.end()
                        or std::find(verticalWalls.begin(), verticalWalls.end(), item2) != verticalWalls.end()) {
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