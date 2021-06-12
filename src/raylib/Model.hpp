/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Model Class
*/

#ifndef RL_MODEL_
#define RL_MODEL_

#include "raylib.h"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Vector.hpp"
#include "Color.hpp"
#include <memory>

namespace rl {

class Model
{
    public:
        Model(const std::string fileName);
        Model(rl::Mesh &mesh);
        ~Model();

        ::Model getModel() const { return _model ; };
        void setMaterialTexture(int material, std::shared_ptr<rl::Texture> texture);

        void makeItSkybox(std::string pathSharderVs, std::string pathSharderFs, std::string pathImg);
        void drawSkybox();

        void draw(rl::Vec3 pos, float scale, rl::Color color);
        void drawEx(rl::Vec3 pos, rl::Vec3 rotaAxis, float rotaAngle, rl::Vec3 scale, rl::Color color);
        void drawWires(rl::Vec3 pos, float scale, rl::Color color);
        void drawWiresEx(rl::Vec3 pos, rl::Vec3 rotaAxis, float rotaAngle, rl::Vec3 scale, rl::Color color);

    private:
        ::Model _model;
        bool _isSkyBox;
};

class ModelAnimation
{
    public:
        ModelAnimation(const std::string fileName, int *animsCount);
        ~ModelAnimation();

        void update(std::shared_ptr<rl::Model> model, int anims, int frame);
        bool isModelAnimationValid(std::shared_ptr<rl::Model> model, int anims);

        int getFrameCount(int anim) const { return _anims[anim].frameCount; };
    private:
        ::ModelAnimation *_anims;
        int _count;
};


}

#endif