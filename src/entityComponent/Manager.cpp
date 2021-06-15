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
    _settings._sizeMap = 0.0;
    _settings._mVol = 1.0;
    _settings._sVol = 1.0;
    _settings._fScreen = false;
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

    delete _PhysXTree;
    _PhysXTree = new UniTree<AObject, rl::Vec3, 3>(rl::Vec3(0, 0, 0), rl::Vec3(1024, 1024, 1024));
    for (auto &obj : _objs[scene])
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

    fillPhysXTree(3);
    computeAImap();

    for (long unsigned int i = 0; i < _objs[6].size(); i++) {
        auto obj = _objs[6][i];
        obj->simulate();
    }
    for (long unsigned int i = 0; i < _objs[_settings._scene].size(); i++) {
        auto obj = _objs[_settings._scene][i];
        obj->simulate();
    }
    _frame++;
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

void ComponentManager::computeAImap() {
    _currentMapSize = {0, 0};
    for (auto obj : _objs[3]) {
        if (dynamic_cast<Wall *>(obj)) {
        } else if (dynamic_cast<Box *>(obj)) {
        } else if (dynamic_cast<Player *>(obj)) {
        } else if (dynamic_cast<Bomb *>(obj)) {
        } else if (dynamic_cast<PowerUp *>(obj)) {
        } else {
            continue;
        }


        rl::Vec3 &pos = obj->_pos;
        if (pos[0] > _currentMapSize.x) {
            _currentMapSize.x = (*obj)[0];
        }
        if (pos[2] > _currentMapSize.y) {
            _currentMapSize.y = (*obj)[2];
        }
    }
    _AImap.clear();
    _AImap.resize(_currentMapSize.x+1);
    for (auto &vec : _AImap)
        vec.resize(_currentMapSize.y+1, ControlsAI::cellType::EMPTY); // standard cell attractiveness
    
    _AImapValues.clear();
    _AImapValues.resize(_currentMapSize.x+1);
    for (auto &vec : _AImapValues)
        vec.resize(_currentMapSize.y+1, 0); // standard cell attractiveness

    for (auto obj : _objs[3]) {
        if ((*obj)[0] < 0 || (*obj)[2] < 0)
            continue;
        rl::Vec3 pos = obj->_pos;
        int x = pos[0];
        int y = pos[2];
        if (dynamic_cast<Wall *>(obj)) {
            _AImap[x][y] |= ControlsAI::cellType::WALL;
        } else if (dynamic_cast<Box *>(obj)) {
            _AImap[x][y] |= ControlsAI::cellType::BOX;
        } else if (dynamic_cast<Player *>(obj)) {
            _AImap[x][y] |= ControlsAI::cellType::PLAYER;
        } else if (dynamic_cast<Bomb *>(obj)) {
            _AImap[x][y] |= ControlsAI::cellType::BOMB;
        } else if (dynamic_cast<PowerUp *>(obj)) {
            _AImap[x][y] |= ControlsAI::cellType::POWERUP;
        }
    }

    for (auto obj : _objs[3]) {
        if ((*obj)[0] < 0 || (*obj)[2] < 0)
            continue;
        rl::Vec3 pos = obj->_pos;
        int x = round(pos[0]);
        int y = round(pos[2]);
        if (auto obj2 = dynamic_cast<Wall *>(obj)) {
            _AImapValues[x][y] += 50000;
        } else if (auto obj2 = dynamic_cast<Box *>(obj)) {
            _AImapValues[x][y] += 50000;
        } else if (auto obj2 = dynamic_cast<Player *>(obj)) {
            _AImapValues[x][y] += 50000;
        } else if (auto obj2 = dynamic_cast<Bomb *>(obj)) {
            _AImapValues[x][y] += 50000;
            int explosionRadius = obj2->_explosionRadius;
            int time = obj2->_time;
            int maxTime = obj2->_maxTime;
            rl::Vec3 axis[4] = {
                {1, 0, 0},
                {-1, 0, 0},
                {0, 0, 1},
                {0, 0, -1},
            };
            for (int axis_nb = 0; axis_nb < 4; axis_nb++){
                rl::Vec3 offset = {(float)x, 0, (float)y};
                for (int i = 0; i <= explosionRadius; i++, offset += axis[axis_nb]) {
                    ControlsAI::cellType &cell = (ControlsAI::cellType &)_AImap[(int)offset[0]][(int)offset[2]];
                    float &cellVal = _AImapValues[(int)offset[0]][(int)offset[2]];
                    if (cell & ControlsAI::cellType::BLOCKEPLOSION)
                        break;
                    cellVal += (maxTime - time)*10;
                }
            }
        } else if (auto obj2 = dynamic_cast<PowerUp *>(obj)) {
            _AImapValues[x][y] -= 100;
        }
    }

    if (!(_frame % 30)&& 0){
        for (auto &vec : _AImapValues) {
            for (auto &val : vec){
                std::cout << std::setw(8) << val << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }
}