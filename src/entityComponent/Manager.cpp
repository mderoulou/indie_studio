/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Manager Functions
*/

#include "Manager.hpp"

ComponentManager::ComponentManager(Bomberman *bomberman)
    : _objs(8)
{
    _cam = new rl::Camera3d(rl::Vec3(1.0f, 1.0f, 1.0f),
                            rl::Vec3(4.0f, 1.5f, 1.0f),
                            rl::Vec3(0.0f, 1.0f, 0.0f),
                            45.0f, 0);
    _settings._scene = 0;
    _settings._sizeMap = 0.0;
    _settings._mVol = 1.0;
    _settings._sVol = 1.0;
    _settings._fScreen = false;
    _PhysXTree = new UniTree<AObject, rl::Vec3, 3>(rl::Vec3(0, 0, 0), rl::Vec3(1024, 1024, 1024));
    _bomberman = bomberman;
}

ComponentManager::~ComponentManager()
{
    delete _cam;
    this->clearComponents();
}

void ComponentManager::addComponent(std::shared_ptr<AObject> obj, int index)
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
            _PhysXTree->addData(&*obj);
}

void ComponentManager::simulate()
{
    // remove designated objects
    for (int i = 0; i < _objs[_settings._scene].size(); i++) {
        auto obj = _objs[_settings._scene][i];
        // clear object
        if (obj->_toRemove) {
            _objs[_settings._scene].erase(_objs[_settings._scene].begin()+i);
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
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj.get()))
            obj->render(_cam);
    
    for (auto obj : _objs[_settings._scene])
        if (Object2D *obj2 = dynamic_cast<Object2D *>(obj.get()))
            obj->render(_cam);

    _cam->beginMode();
    for (auto obj: _objs[6])
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj.get()))
            obj->render(_cam);
    
    for (auto obj : _objs[_settings._scene])
        if (Object3D *obj2 = dynamic_cast<Object3D *>(obj.get()))
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

void ComponentManager::moveCamera(bool dynamic)
{
    if (dynamic) {
        static rl::Vec3 v_pos(0, 0, 0);
        static rl::Vec3 v_target(0, 0, 0);
        rl::Vec3 pos = _cam->getPosition();
        rl::Vec3 target = _cam->getTarget();

        v_pos    += (_set_pos    - v_pos    * 50 - pos   ) * 0.001;
        v_target += (_set_target - v_target * 50 - target) * 0.001;

        _cam->setTarget( target + v_target);
        _cam->moveCamera(pos    + v_pos);

    } else {
        _cam->setTarget(_set_target);
        _cam->moveCamera(_set_pos);
    }
}

bool ComponentManager::verifyIsSet()
{
    if (_cam->getTarget() != _set_target)
        return false;
    else if (_cam->getPosition() != _set_pos)
        return false;
    return true;
}

void ComponentManager::manageCamera()
{
    int size = 0;

    if (_settings._scene == 3 || _settings._scene == 4) {
        size = 11 + 6 * _settings._sizeMap;
        _set_pos = rl::Vec3(size / 2,  size * 1.3, (size / 2) + 0.5);
        _set_target = rl::Vec3(size / 2,  0, size / 2);
        moveCamera(true);
    } else {
        _set_pos = rl::Vec3(1.0f, 1.0f, 1.0f);
        _set_target = rl::Vec3(4.0f, 1.5f, 1.0f);
        moveCamera(true);
    }
}

void ComponentManager::computeAImap() {
    _currentMapSize = {0, 0};
    for (auto obj : _objs[3]) {
        if (!dynamic_cast<Floor *>(obj.get()))
            continue;


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

    _boxCount = 0;
    _playerCount = 0;
    Player *player = 0;
    for (auto obj : _objs[3]) {
        if ((*obj)[0] < 0 || (*obj)[2] < 0)
            continue;
        rl::Vec3 pos = obj->_pos;
        int x = round(pos[0]);
        int y = round(pos[2]);
        if (x > _currentMapSize.x || y > _currentMapSize.y)
            continue;
        if (dynamic_cast<Wall *>(obj.get())) {
            _AImap[x][y] |= ControlsAI::cellType::WALL;
        } else if (dynamic_cast<Box *>(obj.get())) {
            _AImap[x][y] |= ControlsAI::cellType::BOX;
            _boxCount++;
        } else if (dynamic_cast<Player *>(obj.get())) {
            _AImap[x][y] |= ControlsAI::cellType::PLAYER;
            _playerCount++;
            player = dynamic_cast<Player *>(obj.get());
        } else if (dynamic_cast<Bomb *>(obj.get())) {
            _AImap[x][y] |= ControlsAI::cellType::BOMB | ControlsAI::cellType::WILLDIE;
        } else if (dynamic_cast<PowerUp *>(obj.get())) {
            _AImap[x][y] |= ControlsAI::cellType::POWERUP;
        }
    }

    if (_playerCount == 1 && _settings._scene == 3) {    
        _mm->playSound("winner.ogg", false);
        std::cout << "Player " << player->_playerId << " won!" << std::endl;
        // TODO VICTORY TRIGER
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _objs[3].clear();
        rl::Mouse::ShowCursor();
        _settings._scene = 2;
    } else if (_playerCount == 0 && _settings._scene == 3) {
        _mm->playSound("tie.ogg", false);
        std::cout << "It's a tie!" << std::endl;
        // TODO DRAW TRIGER
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        _objs[3].clear();
        _settings._scene = 2;
    }

    for (auto obj : _objs[3]) {
        if ((*obj)[0] < 0 || (*obj)[2] < 0)
            continue;
        rl::Vec3 pos = obj->_pos;
        int x = round(pos[0]);
        int y = round(pos[2]);
        if (x > _currentMapSize.x || y > _currentMapSize.y)
            continue;
        if (auto obj2 = dynamic_cast<Wall *>(obj.get())) {
            _AImapValues[x][y] += 50000000;
        } else if (auto obj2 = dynamic_cast<Box *>(obj.get())) {
            _AImapValues[x][y] += 50000000;
        } else if (auto obj2 = dynamic_cast<Player *>(obj.get())) {
            if (_boxCount == 0)
                _AImapValues[x][y] += -120;
        } else if (auto obj2 = dynamic_cast<Bomb *>(obj.get())) {
            _AImapValues[x][y] += 50000000;
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
                    if (cell & ControlsAI::cellType::BLOCKEXPLOSION)
                        break;

                    for (int axis_nb2 = 0; axis_nb2 < 4; axis_nb2++){
                        _AImapValues[(int)offset[0]+axis[axis_nb2][0]][(int)offset[2]+axis[axis_nb2][2]] += 260;   
                    }
                    
                    if ((maxTime - time) > maxTime/3){
                        _AImap[(int)offset[0]][(int)offset[2]] |= ControlsAI::cellType::WILLDIESOON;
                        cellVal += (maxTime - time)*5000;
                    }
                    _AImap[(int)offset[0]][(int)offset[2]] |= ControlsAI::cellType::WILLDIE;
                }
            }
        } else if (auto obj2 = dynamic_cast<PowerUp *>(obj.get())) {
        }
    }


    for (auto obj : _objs[3]) {
        if ((*obj)[0] < 0 || (*obj)[2] < 0)
            continue;
        rl::Vec3 pos = obj->_pos;
        int x = round(pos[0]);
        int y = round(pos[2]);
        if (x > _currentMapSize.x || y > _currentMapSize.y)
            continue;
        if (auto obj2 = dynamic_cast<Wall *>(obj.get())) {
        } else if (auto obj2 = dynamic_cast<Box *>(obj.get())) {
            if (!(_AImap[x+1][y] & ControlsAI::cellType::WILLDIE)){
                _AImap[x+1][y] |= ControlsAI::cellType::WILLDAMGE;
                if (_AImapValues[x+1][y] > -240)
                    _AImapValues[x+1][y] -= 30;
            }
            if (!(_AImap[x-1][y] & ControlsAI::cellType::WILLDIE)){
                _AImap[x-1][y] |= ControlsAI::cellType::WILLDAMGE;
                if (_AImapValues[x-1][y] > -240)
                    _AImapValues[x-1][y] -= 30;
            }
            if (!(_AImap[x][y+1] & ControlsAI::cellType::WILLDIE)){
                _AImap[x][y+1] |= ControlsAI::cellType::WILLDAMGE;
                if (_AImapValues[x][y+1] > -240)
                    _AImapValues[x][y+1] -= 30;
            }
            if (!(_AImap[x][y-1] & ControlsAI::cellType::WILLDIE)){
                _AImap[x][y-1] |= ControlsAI::cellType::WILLDAMGE;
                if (_AImapValues[x][y-1] > -240)
                    _AImapValues[x][y-1] -= 30;
            }

        } else if (auto obj2 = dynamic_cast<Player *>(obj.get())) {
            if (_boxCount == 0)
                _AImapValues[x][y] -= 120;
        } else if (auto obj2 = dynamic_cast<Bomb *>(obj.get())) {
        } else if (auto obj2 = dynamic_cast<PowerUp *>(obj.get())) {
            if (!(_AImap[x][y] & ControlsAI::cellType::WILLDIE))
                _AImapValues[x][y] = -240;
        }
    }

    auto buf = _AImapValues;
    // smooth the grid
    const auto &r1 = _AImapValues; 
    auto &r2 = buf; 
    for (int i = 0; i < 64; i++){
        for (int x = 1; x < r1.size()-1; x++) {
            for (int y = 1; y < r1[x].size()-1; y++) {
                if (_AImap[x][y] & ControlsAI::cellType::BLOCKING)
                    continue;
                rl::Vec2 axes[5] = {
                    {0, 0},
                    {-1, 0},
                    {1, 0},
                    {0, -1},
                    {0, 1},
                };
                int bestAxis = 0;
                int count = 1;
                float bestscore = r1[x][y];
                float some = bestscore;
                for (int axesID = 1; axesID < 5; axesID++) {
                    if (r1[x+axes[axesID].x][y+axes[axesID].y] < bestscore) {
                        bestAxis = axesID;
                        bestscore = r1[x+axes[axesID].x][y+axes[axesID].y];
                    }
                    if (_AImap[x+axes[axesID].x][y+axes[axesID].y] & (ControlsAI::BLOCKING))
                        continue;
                    some += r1[x+axes[axesID].x][y+axes[axesID].y];
                    count++;
                }
                if (_AImap[x][y] & (ControlsAI::WILLDIESOON))
                    r2[x][y] = r1[x][y]*0.99 + bestscore*0.01; //;//;
                else
                    r2[x][y] = r1[x][y]*0.95 + bestscore*0.05; // + some/count*0.001; //;//;
            }
        }
        _AImapValues = buf;
    }
    std::cout.precision(2);
    if (!(_frame % 30) && 0){
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