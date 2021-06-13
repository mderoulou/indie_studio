/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Manager Functions
*/

#include "Manager.hpp"

ComponentManager::ComponentManager(Bomberman *bomberman)
{
    _cam = new rl::Camera3d(rl::Vec3(5.0f, 20.0f, 20.0f),
                            rl::Vec3(0.0f, 0.0f, 0.0f),
                            rl::Vec3(0.0f, 1.0f, 0.0f),
                            45.0f, 0);
    _settings._scene = 0;
    _settings._sizeMap = 10.0;
    _settings._mVol = 1.0;
    _settings._sVol = 1.0;
    _PhysXTree = new UniTree<AObject, rl::Vec3, 3>(rl::Vec3(0, 0, 0), rl::Vec3(64000, 64000, 64000));
    _bomberman = bomberman;
}

ComponentManager::~ComponentManager()
{
    delete _cam;
    this->clearComponents();
}

void ComponentManager::addComponent(AObject *obj)
{
    obj->_manager = this;
    _objs.push_back(obj);
}

void ComponentManager::removeComponent(AObject *to_rm)
{
    uint32_t index = 0;

    for (auto obj : _objs) {
        if (obj == to_rm)
            break;
        index++;
    }
    _objs.erase(_objs.begin() + index);
    delete to_rm;
}

void ComponentManager::clearComponents()
{
    _objs.clear();
}

void ComponentManager::simulate()
{
    // remove designated objects
    for (int i = 0; i < _objs.size(); i++) {
        auto obj = _objs[i];
        // clear object
        if (obj->_toRemove) {
            _objs.erase(_objs.begin()+i);
            delete obj;
            i--;
        }
    }

    // rebuilt physicX tree
    delete _PhysXTree;
    _PhysXTree = new UniTree<AObject, rl::Vec3, 3>(rl::Vec3(0, 0, 0), rl::Vec3(64000, 64000, 64000));
    for (auto obj : _objs)
        if (obj->_isSolid)
            _PhysXTree->addData(obj);


    for (long unsigned int i = 0; i < _objs.size(); i++) {
        auto obj = _objs[i];
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj))
            if (obj2->_scene == _settings._scene || obj2->_scene < 0)
                obj->simulate();
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj))
            if (obj2->_scene == _settings._scene || obj2->_scene < 0)
                obj->simulate();
    }
}

void ComponentManager::renderAll()
{
    //std::cout << "[MANAGER] Rendering!" << std::endl;
    for (auto obj : _objs)
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj))
            if (obj2->_scene == _settings._scene || obj2->_scene < 0)
                obj->render(_cam);

    _cam->beginMode();
    for (auto obj : _objs)
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj))
            if (obj2->_scene == _settings._scene || obj2->_scene < 0)
                obj->render(_cam);
    _cam->endMode();
}

void ComponentManager::handleEvent()
{
    //std::cout << "[MANAGER] Handling Events!" << std::endl;
    for (auto obj: _objs) {
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj))
            if (obj2->_scene == _settings._scene || obj2->_scene < 0)
                obj->handleEvent();
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj))
            if (obj2->_scene == _settings._scene || obj2->_scene < 0)
                obj->handleEvent();
    }
}