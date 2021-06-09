/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** RayLib Ray Class
*/

#ifndef RL_BOX_
#define RL_BOX_

#include "raylib.h"
#include "Color.hpp"
#include "Vector.hpp"
#include "Mesh.hpp"

namespace rl {

class BoundingBox
{
    public:
        BoundingBox(rl::Mesh *mesh);
        BoundingBox(rl::Vec3 max, rl::Vec3 min);

        void draw(rl::Color color);
        bool checkColissionBox(rl::BoundingBox *box);
        bool checkColissionSphere(rl::Vec3 pos, float radius);

        void changeBox(rl::Vec3 max, rl::Vec3 min);

        ::BoundingBox getBox() const { return _bd; };
    private:
        ::BoundingBox _bd;
};

}

#endif