/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Model Functions
*/

#include "Model.hpp"

/**
 *  Shader Include
 */

#include "rlgl.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

/**
 *  Model Functions
 */

rl::Model::Model(const std::string filename)
{
    _isSkyBox = false;
    _model = LoadModel(filename.c_str());
}

rl::Model::Model(rl::Mesh &mesh)
{
    _isSkyBox = false;
    _model = LoadModelFromMesh(mesh.getMesh());
}

rl::Model::~Model()
{
    if (_isSkyBox) {
        UnloadShader(_model.materials[0].shader);
        UnloadTexture(_model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
    }
    //UnloadModel(_model);
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

void rl::Model::setMaterialTexture(int material, std::shared_ptr<rl::Texture> texture)
{
    SetMaterialTexture(&_model.materials[material], MAP_DIFFUSE, (*texture).getTexture());
}

void rl::Model::makeItSkybox(std::string pathSharderVs, std::string pathSharderFs, std::string pathImg)
{
    _isSkyBox = true;
    _model.materials[0].shader = LoadShader(TextFormat(pathSharderVs.c_str(), GLSL_VERSION),
                                            TextFormat(pathSharderFs.c_str(), GLSL_VERSION));

    const int a[1] = {MATERIAL_MAP_CUBEMAP};
    const int b[1] = {0};
    const int c[1] = {0};

    SetShaderValue(_model.materials[0].shader, GetShaderLocation(_model.materials[0].shader, "environmentMap"), a, SHADER_UNIFORM_INT);
    SetShaderValue(_model.materials[0].shader, GetShaderLocation(_model.materials[0].shader, "doGamma"), b, SHADER_UNIFORM_INT);
    SetShaderValue(_model.materials[0].shader, GetShaderLocation(_model.materials[0].shader, "vflipped"), c, SHADER_UNIFORM_INT);

    ::Image img = LoadImage(pathImg.c_str());
    _model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT);
    UnloadImage(img);
}

void rl::Model::drawSkybox()
{
    Vector3 vec = { 0, 0, 0 };
    DrawModel(_model, vec, 1.0f, WHITE);
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

void rl::ModelAnimation::update(std::shared_ptr<rl::Model> model, int anims, int frame)
{
    UpdateModelAnimation(model->getModel(), _anims[anims], frame);
}

bool  rl::ModelAnimation::isModelAnimationValid(std::shared_ptr<rl::Model> model, int anims)
{
    return IsModelAnimationValid(model->getModel(), _anims[anims]);
}