//
// Created by Иван Назаров on 08.11.2022.
//

#include "state.h"
#include "read_write.hpp"
#include "is_valide_state.h"

int main() {
    State state = read();
    printState(state);
    assert(isValidState(state));
}