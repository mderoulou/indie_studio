/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Model Class
*/

#ifndef RL_MODEL_
#define RL_MODEL_

#include "rayLib.hpp"

namespace rl {

class Mesh;

class Model
{
    public:
        Model(const std::string fileName);
        Model(rl::Mesh &mesh);
        ~Model();

        ::Model getModel() const { return _model ; };

        void draw(rl::Vec3 pos, float scale, rl::Color color);
        void drawEx(rl::Vec3 pos, rl::Vec3 rotaAxis, float rotaAngle, rl::Vec3 scale, rl::Color color);
        void drawWires(rl::Vec3 pos, float scale, rl::Color color);
        void drawWiresEx(rl::Vec3 pos, rl::Vec3 rotaAxis, float rotaAngle, rl::Vec3 scale, rl::Color color);

    private:
        ::Model _model;
};

class ModelAnimation
{
    public:
        ModelAnimation(const std::string fileName, int *animsCount);
        ~ModelAnimation();

        void update(rl::Model model, int anims, int frame);
        bool isModelAnimationValid(rl::Model model, int anims);
    private:
        ::ModelAnimation *_anims;
        int _count;
};


}

#endif