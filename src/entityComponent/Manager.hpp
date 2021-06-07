/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Manager
*/

#ifndef INDIE_MANAGER_
#define INDIE_MANAGER_

#include "../Indie.hpp"

class Gamepad;

class ComponentManager
{
    public:
        ComponentManager();
        ~ComponentManager();

        void addComponent(IObject *obj);
        void clearComponents();

        void simulate();
        void renderAll();
        void handleEvent();

        int size() const { return _objs.size(); };
    private:

        void draw(IObject * obj);
        std::vector<IObject *> _objs;
        Gamepad *_gp;
};

#endif