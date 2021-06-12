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
        float _mVol;
        float _sVol;
};

class ComponentManager
{
    public:
        ComponentManager(Bomberman *_bomberman);
        ~ComponentManager();

        void addComponent(AObject *obj);
        void removeComponent(AObject *to_rm); // UNSAFE FUNCTION; DO NOT USE
        void clearComponents();

        void simulate();
        void renderAll();
        void handleEvent();

        int size() const { return _objs.size(); };
        Bomberman *_bomberman;
        std::vector<AObject *> _objs;
        UniTree<AObject, rl::Vec3, 3> *_PhysXTree;
        rl::Camera3d *_cam;
        Settings _settings;
    private:
        
    private:
};

#endif