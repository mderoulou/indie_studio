/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Texture Class
*/

#ifndef RL_TEXTURE_
#define RL_TEXTURE_

#include <string>

#include "raylib.h"
#include "Image.hpp"
#include "Color.hpp"
#include "Vector.hpp"
#include "Rectangle.hpp"

namespace rl {

class Texture
{
    public:
    Texture(const std::string filename);
    Texture(rl::Image img); // Image data
    Texture(rl::Image img, int layout); // Cubemap
    ~Texture();

    // Draw
    void draw(int posX, int posY, rl::Color color);
    void drawV(rl::Vec2 vec, rl::Color color);
    void drawEx(rl::Vec2 vec, float rotation, float scale, rl::Color color);
    void drawRec(rl::Rectangle rect, rl::Vec2 pos, rl::Color color);
    void drawQuad(rl::Vec2 vec, rl::Vec2 offset, rl::Rectangle rect, rl::Color color);
    void drawTiled(rl::Rectangle src, rl::Rectangle dest, rl::Vec2 origin, float rotation, float scale, rl::Color color);
    void drawPro(rl::Rectangle src, rl::Rectangle dest, rl::Vec2 origin, float rotation, rl::Color color);
    void drawPoly(rl::Vec2 center, rl::Vec2 *points, rl::Vec2 *textcoords, int pointsLen, rl::Color color);
    void drawTexture(rl::Vec3 pos, rl::Vec3 size, rl::Color color);

    ::Texture getTexture() const { return _texture;};
    private:
        ::Texture _texture;
};

}

#endif