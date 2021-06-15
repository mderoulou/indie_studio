/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Manager
*/

#ifndef INDIE_MANAGER_
#define INDIE_MANAGER_

#include "../Indie.hpp"
#include "UniTree.hpp"

class Gamepad;

class Settings
{
    public:
        std::string _optSkin;
        std::vector<std::string> _skins;
        int _scene;
        uint16_t _sizeMap;
        bool _fScreen;
        float _mVol;
        float _sVol;
        int _width;
        int _height;
};

class ComponentManager
{
    public:
        ComponentManager(Bomberman *_bomberman);
        ~ComponentManager();

        void addComponent(AObject *obj, int index);
        void fillPhysXTree(int scene = -1);
        void clearComponents();

        void simulate();
        void renderAll();
        void handleEvent();

        void computeAImap();

        int size() const { return _objs.size(); };
        Bomberman *_bomberman;
        //std::vector<AObject *> _objs;
        std::vector<std::vector<AObject *>> _objs;
        UniTree<AObject, rl::Vec3, 3> *_PhysXTree;
        rl::Camera3d *_cam;
        Settings _settings;
        uint _frame = 0;
        std::vector<std::vector<float>> _AImapValues;
        std::vector<std::vector<int>> _AImap;
        rl::Vec2 _currentMapSize = {0, 0};
    private:
        
    private:
};

#endif