/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Texture Functions
*/

#include "Texture.hpp"
#include <iostream>

rl::Texture::Texture(const std::string filename)
{
    _texture = LoadTexture(filename.c_str());
    SetTextureFilter(_texture, TEXTURE_FILTER_ANISOTROPIC_16X);
}

rl::Texture::Texture(rl::Image img)
{
    _texture = LoadTextureFromImage(img.getImg());
    SetTextureFilter(_texture, TEXTURE_FILTER_ANISOTROPIC_16X);
}

rl::Texture::Texture(rl::Image img, int layout)
{
    _texture = LoadTextureCubemap(img.getImg(), layout);
    SetTextureFilter(_texture, TEXTURE_FILTER_ANISOTROPIC_16X);
}

rl::Texture::~Texture()
{
    UnloadTexture(_texture);
}

// Draw

void rl::Texture::draw(int posX, int posY, rl::Color color)
{
    DrawTexture(_texture, posX, posY, color);
}

void rl::Texture::drawV(rl::Vec2 vec, rl::Color color)
{
    DrawTextureV(_texture, vec, color);
}

void rl::Texture::drawEx(rl::Vec2 vec, float rotation, float scale, rl::Color color)
{
    DrawTextureEx(_texture, vec, rotation, scale, color);
}

void rl::Texture::drawRec(rl::Rectangle rect, rl::Vec2 pos, rl::Color color)
{
    DrawTextureRec(_texture, rect, pos, color);
}

void rl::Texture::drawQuad(rl::Vec2 vec, rl::Vec2 offset, rl::Rectangle rect, rl::Color color)
{
    DrawTextureQuad(_texture, vec, offset, rect, color);
}

void rl::Texture::drawTiled(rl::Rectangle src, rl::Rectangle dest, rl::Vec2 origin, float rotation, float scale, rl::Color color)
{
    DrawTextureTiled(_texture, src, dest, origin, rotation, scale, color);
}

void rl::Texture::drawPro(rl::Rectangle src, rl::Rectangle dest, rl::Vec2 origin, float rotation, rl::Color color)
{
    DrawTexturePro(_texture, src, dest, origin, rotation, color);
}

void rl::Texture::drawPoly(rl::Vec2 center, rl::Vec2 *points, rl::Vec2 *textcoords, int pointsLen, rl::Color color)
{
    DrawTexturePoly(_texture, center, points, textcoords, pointsLen, color);
}

void rl::Texture::drawTexture(rl::Vec3 pos, rl::Vec3 size, rl::Color color)
{
    DrawCubeTexture(_texture, pos, size.x, size.y, size.z, color);
}