/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Manager
*/

#ifndef INDIE_MANAGER_
#define INDIE_MANAGER_

#include "Indie.hpp"

class ComponentManager
{
    public:
        ComponentManager() {};
        ~ComponentManager();

        void addComponent(IObject *obj);
        void clearComponents();

        void setPos();
        void movePos();
        void renderAll();
        void handleEvent();

        int size() const { return _objs.size(); };
    private:

        void draw(IObject * obj);
        std::vector<IObject *> _objs;
};

#endif