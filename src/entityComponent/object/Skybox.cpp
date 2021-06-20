/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** Skybox
*/

#include "../Object.hpp"
#include "../../Indie.hpp"

// Shader include

#include "rlgl.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

Skybox::Skybox(Bomberman *m)
{
    _m = m;
    _scene = 3;
    _mesh = std::make_shared<rl::Mesh>(10.0f, 10.0f, 10.0f);
    _skybox = std::make_shared<rl::Model>(*(_mesh.get()));
    (*_skybox).makeItSkybox("assets/shader/skybox/glsl%i/skybox.vs",
                            "assets/shader/skybox/glsl%i/skybox.fs",
                            "assets/shader/skybox/skybox.png");
}

void Skybox::render(rl::Camera3d *cam)
{
    cam->beginMode();
    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    rlDrawRenderBatchActive();
    rlDisableDepthTest();
    (*_skybox).drawSkybox(rl::Vec2{(float) _m->_win->getScreenWidth(), (float) _m->_win->getScreenHeight()});
    rlDrawRenderBatchActive();
    rlEnableBackfaceCulling();
    rlEnableDepthMask();
    rlEnableDepthTest();
    cam->endMode();
}
