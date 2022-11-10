//
// Created by Иван Назаров on 08.11.2022.
//

#include "board.hpp"
#include "game.hpp"

#include <cstring>
#include <sstream>

int main(int argc, char **argv) {
//    if (argc == 1) {
//        std::cout << "Недостаточно аргументов!" << std::endl;
//    }

    Mode mode = Mode::play;
    InitType init = InitType::fromStdIn;
    int playerId = 0;
    std::string path;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--play") == 0) {
            mode = Mode::play;
        } else if (strcmp(argv[i], "--engine") == 0) {
            mode = Mode::engine;
        } else if (strcmp(argv[i], "--interactive") == 0) {
            mode = Mode::interactive;
        } else if (strcmp(argv[i], "--from-file") == 0) {
            path = argv[++i];
            init = InitType::fromFile;
        } else if (strcmp(argv[i], "--player") == 0) {
            playerId = argv[++i][0] - '1';
        } else {
            std::cout << "Неизвестный аргумент!" << std::endl;
            return -1;
        }

    }

    Game game(mode, init, playerId, path);
    game.run();
}