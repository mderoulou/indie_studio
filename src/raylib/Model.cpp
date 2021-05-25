/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Model Functions
*/

#include "Model.hpp"

/**
 *  Model Functions
 */

rl::Model::Model(const std::string filename)
{
    _model = LoadModel(filename.c_str());
}

rl::Model::Model(rl::Mesh &mesh)
{
    _model = LoadModelFromMesh(mesh.getMesh());
}

rl::Model::~Model()
{
    UnloadModel(_model);
}

void rl::Model::draw(rl::Vec3 pos, float scale, rl::Color color)
{
    DrawModel(_model, pos, scale, color);
}

void rl::Model::drawEx(rl::Vec3 pos, rl::Vec3 rotaAxis, float rotaAngle, rl::Vec3 scale, rl::Color color)
{
    DrawModelEx(_model, pos, rotaAxis, rotaAngle, scale, color);
}

void rl::Model::drawWires(rl::Vec3 pos, float scale, rl::Color color)
{
    DrawModelWires(_model, pos, scale, color);
}

void rl::Model::drawWiresEx(rl::Vec3 pos, rl::Vec3 rotaAxis, float rotaAngle, rl::Vec3 scale, rl::Color color)
{
    DrawModelWiresEx(_model, pos, rotaAxis, rotaAngle, scale, color);
}

/**
 *  ModelAnimation Functions
 */

rl::ModelAnimation::ModelAnimation(const std::string filename, int *animsCount)
{
    _anims = LoadModelAnimations(filename.c_str(), animsCount);
    _count = *animsCount;
}

rl::ModelAnimation::~ModelAnimation()
{
    UnloadModelAnimations(_anims, _count);
}

void rl::ModelAnimation::update(rl::Model model, int anims, int frame)
{
    UpdateModelAnimation(model.getModel(), _anims[anims], frame);
}

bool  rl::ModelAnimation::isModelAnimationValid(rl::Model model, int anims)
{
    return IsModelAnimationValid(model.getModel(), _anims[anims]);
}