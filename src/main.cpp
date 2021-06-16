#include "Indie.hpp"

int main(void)
{
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    try {
        Bomberman game;
        game.launch();
    } catch (...) {
        return 84;
    }
    return 0;
}