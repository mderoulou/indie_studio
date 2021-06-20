#include "Indie.hpp"

void sighandler(int code)
{
    (void)code;
    exit(84);
}

int main(void)
{
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    try {
        Bomberman game;
        #ifdef __linux__
        signal(SIGSEGV, sighandler);
        #endif
        game.launch();
    } catch (...) {
        return 84;
    }
    return 0;
}
