/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Manager Functions
*/

#include "Manager.hpp"

ComponentManager::ComponentManager(Bomberman *bomberman)
    : _objs(7)
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

void ComponentManager::addComponent(AObject *obj, int index)
{
    obj->_manager = this;
    _objs[index].push_back(obj);
}

void ComponentManager::clearComponents()
{
    _objs[_settings._scene].clear();
}

void ComponentManager::fillPhysXTree(int scene) {
    // rebuilt physicX tree
    if (scene == -1)
        scene = _settings._scene;
    delete _PhysXTree;
    _PhysXTree = new UniTree<AObject, rl::Vec3, 3>(rl::Vec3(0, 0, 0), rl::Vec3(64000, 64000, 64000));
    for (auto obj : _objs[scene])
        if (obj->_isSolid)
            _PhysXTree->addData(obj);

}

void ComponentManager::simulate()
{
    // remove designated objects
    for (int i = 0; i < _objs[_settings._scene].size(); i++) {
        auto obj = _objs[_settings._scene][i];
        // clear object
        if (obj->_toRemove) {
            _objs[_settings._scene].erase(_objs[_settings._scene].begin()+i);
            delete obj;
            i--;
        }
    }

    fillPhysXTree(-1);

    for (long unsigned int i = 0; i < _objs[6].size(); i++) {
        auto obj = _objs[6][i];
        obj->simulate();
    }
    for (long unsigned int i = 0; i < _objs[_settings._scene].size(); i++) {
        auto obj = _objs[_settings._scene][i];
        obj->simulate();
    }
}

void ComponentManager::renderAll()
{
    //std::cout << "[MANAGER] Rendering!" << std::endl;
    for (auto obj: _objs[6])
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj))
            obj->render(_cam);
    
    for (auto obj : _objs[_settings._scene])
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj))
            obj->render(_cam);

    _cam->beginMode();
    for (auto obj: _objs[6])
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj))
            obj->render(_cam);
    
    for (auto obj : _objs[_settings._scene])
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj))
            obj->render(_cam);
    _cam->endMode();
}

void ComponentManager::handleEvent()
{
    //std::cout << "[MANAGER] Handling Events!" << std::endl;
    for (auto obj: _objs[6])
        obj->handleEvent();
    for (auto obj: _objs[_settings._scene])
        obj->handleEvent();
}
