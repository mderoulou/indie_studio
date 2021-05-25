/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Shader Functions
*/

#include "Shader.hpp"
#include "Texture.hpp"

rl::Shader::Shader(const std::string vsFileName, const std::string fsFileName)
{
    _shader = LoadShader(vsFileName.c_str(), fsFileName.c_str());
}

rl::Shader::~Shader()
{
    UnloadShader(_shader);
}

int rl::Shader::getShaderLocation(std::string uniformName)
{
    return GetShaderLocation(_shader, uniformName.c_str());
}

int rl::Shader::getShaderLocationAttrib(std::string attributeName)
{
    return GetShaderLocationAttrib(_shader, attributeName.c_str());
}

void rl::Shader::setShaderValue(int locIndex, void *value, int uniformType)
{
    SetShaderValue(_shader, locIndex, value, uniformType);
}

void rl::Shader::setShaderValueTexture(int locIndex, rl::Texture _texture)
{
    SetShaderValueTexture(_shader, locIndex, _texture.getTexture());
}
