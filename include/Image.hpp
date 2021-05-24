/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Image Class
*/

#ifndef RL_IMAGE_
#define RL_IMAGE_

#include "rayLib.hpp"

namespace rl {

class Image
{
    public:
    Image(const std::string fileName);
    Image(const std::string fileName, int width, int height, int format, int headerSize);
    Image(const Image &img);
    ~Image();

    ::Image getImg() const { return _img; };

    private:
    ::Image _img;
};

}

#endif