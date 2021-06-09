/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Shader Class
*/

#ifndef RL_SHADER_
#define RL_SHADER_

#include "raylib.h"
#include "Texture.hpp"

namespace rl {

class Shader
{
    public:
        Shader(const std::string vsFileName, const std::string fsFileName);
        ~Shader();

        int getShaderLocation(std::string uniformName);
        int getShaderLocationAttrib(std::string attributeName);
        void setShaderValue(int locIndex, void *value, int uniformType);
        void setShaderValueTexture(int locIndex, rl::Texture _texture);
        // TODO : setShaderValueMatrix

        ::Shader getShader() const { return _shader; };
    private:
        ::Shader _shader;
};

}

#endif