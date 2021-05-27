/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Render Texture Class
*/

#ifndef RL_RTEXTURE_
#define RL_RTEXTURE_

#include "rayLib.hpp"

namespace rl {

class RenderTexture
{
    public:
        RenderTexture(int width, int height);
        ~RenderTexture();

        ::RenderTexture getRTexture() const { return _rtexture; };
    private:
        ::RenderTexture _rtexture;
};

}

#endif