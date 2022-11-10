//
// Created by Иван Назаров on 08.11.2022.
//

#include "board.hpp"
#include "game.hpp"
#include "cstring"

#include <sstream>

int main(int argc, char **argv) {
    Mode mode;
    char* cmode = argv[1];
    int nextArg = 2;
    if (strcmp(cmode, "--play") == 0) {
        mode = Mode::play;
    } else if (strcmp(cmode, "--engine") == 0) {
        if (strcmp(argv[2], "interactive") == 0) {
            nextArg++;
            mode = Mode::engineInteractive;
        } else {
            mode = Mode::engine;
        }
    } else {
        std::cout << "unknown argument: " << cmode;
        return 1;
    }

    BoardInit boardInit;
    std::string path;
    if (strcmp(argv[nextArg], "--from-file") == 0) {
        nextArg++;
        path = argv[nextArg];
        boardInit = BoardInit::fromFile;
    } else {
        nextArg++;
        boardInit = BoardInit::fromStart;
    }
    int player;
    if (strcmp(argv[nextArg], "--player") == 0) {
        nextArg++;
        player = argv[nextArg][0] - '1';
    }

    Game game(mode, boardInit, path, player);

    game.run();
}