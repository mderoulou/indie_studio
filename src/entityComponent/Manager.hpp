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

class ComponentManager
{
    public:
        ComponentManager();
        ~ComponentManager();

        void addComponent(AObject *obj);
        void clearComponents();

        void simulate();
        void renderAll();
        void handleEvent();

        int size() const { return _objs.size(); };
        int _scene;
        std::vector<AObject *> _objs;
        UniTree<AObject, rl::Vec3, 3> *_PhysXTree;
        std::string _optSkin;
        std::vector<std::string> _skins;

        rl::Camera3d *_cam;
    private:
        
    private:
};

#endif