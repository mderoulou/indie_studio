/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Manager Functions
*/

#include "Manager.hpp"

ComponentManager::ComponentManager()
{
    _gp = new Gamepad(rl::Font());
    _cam = new rl::Camera3d(rl::Vec3(5.0f, 20.0f, 20.0f),
                            rl::Vec3(0.0f, 0.0f, 0.0f),
                            rl::Vec3(0.0f, 1.0f, 0.0f),
                            45.0f, 0);
    _scene = 0;
}

ComponentManager::~ComponentManager()
{
    delete _cam;
    delete _gp;
    this->clearComponents();
}

void ComponentManager::addComponent(IObject *obj)
{
    _objs.push_back(obj);
}

void ComponentManager::clearComponents()
{
    _objs.clear();
}

void ComponentManager::simulate()
{
    if (!_gp->initialized)
        _gp->init();
    for (auto obj : _objs) {
        obj->simulate();
    }
}

void ComponentManager::renderAll()
{
    //std::cout << "[MANAGER] Rendering!" << std::endl;
    for (auto obj : _objs) {
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj))
            if (obj2->_scene == _scene)
                obj->render(_cam);
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj))
            if (obj2->_scene == _scene)
                obj->render(_cam);
    }
}

void ComponentManager::handleEvent()
{
    //std::cout << "[MANAGER] Handling Events!" << std::endl;
    for (auto obj: _objs) {
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj))
            if (obj2->_scene == _scene)
                obj->handleEvent();
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj))
            if (obj2->_scene == _scene)
                obj->handleEvent();
    }
}

void ComponentManager::moveAll()
{
    //std::cout << "[MANAGER] Moving Events!" << std::endl;
    rl::Vec3 newPos(0, 0, 0);
    float mov;

    /*if (!_gp->initialized)
        return;
    if ((mov = _gp->isKeyUp()) != 0) {
        newPos.z = -0.1f * mov;
        mov = 0;
    }
    if ((mov = _gp->isKeyDown()) != 0) {
        newPos.z = 0.1f * mov;
        mov = 0;
    }
    if ((mov = _gp->isKeyLeft()) != 0) {
        newPos.x = -0.1f * mov;
        mov = 0;
    }
    if ((mov = _gp->isKeyRight()) != 0) {
        newPos.x = 0.1f * mov;
        mov = 0;
    }*/
    
    for (auto obj : _objs) {
        obj->move(newPos);
    }
}