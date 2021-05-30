#include "Indie.hpp"
#include "Gamepad.hpp"

int main()
{
    // Our Raylib

    rl::Window win(1080, 720, "Raylib");
    win.changeFps(24);

    rl::Font f;

//    Gamepad gp(f);
    Keyboard gp(f);

    rl::Rectangle rec(1080/2 - 20, 720/2 - 20, 40, 40);

    while (!win.Close()) {
        win.clearBackground(rl::Color(255, 255, 255, 255));
        win.beginDrawing();

        if (!gp.initialized) {
            gp.init();
        } else {
            rec.draw(rl::Color(255, 0, 0, 255));
            float mov;
            if ((mov = gp.isKeyUp()) != 0) {
                rec.y -= 10 * mov;
                mov = 0;
            }
            if ((mov = gp.isKeyDown()) != 0) {
                rec.y += 10 * mov;
                mov = 0;
            }
            if ((mov = gp.isKeyLeft()) != 0) {
                rec.x -= 10 * mov;
                mov = 0;
            }
            if ((mov = gp.isKeyRight()) != 0) {
                rec.x += 10 * mov;
                mov = 0;
            }
        }

        win.endDrawing();
    }

    return (0);
}