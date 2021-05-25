/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Render Texture Functions
*/

#include "RenderTexture.hpp"

rl::RenderTexture::RenderTexture(int width, int height)
{
    _rtexture = LoadRenderTexture(width, height);
}

rl::RenderTexture::~RenderTexture()
{
    UnloadRenderTexture(_rtexture);
}