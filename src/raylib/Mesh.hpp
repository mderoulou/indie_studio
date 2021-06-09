/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Mesh Class
*/

#ifndef RL_MESH_
#define RL_MESH_

#include "raylib.h"
#include "Image.hpp"
#include "Vector.hpp"

namespace rl {

class Mesh
{
    public:
        Mesh(int sides, float radius);
        Mesh(float width, float length, int resX, int resZ);
        Mesh(float width, float height, float length);
        Mesh(float radius, int rings, int slices);
        Mesh(rl::Image map, rl::Vec3 size, int type = 2);
        ~Mesh();
    
        ::Mesh getMesh() const { return _mesh;};

        void computeTangents();
        void computeBinormals();
        bool exportMesh(const std::string filename);
        void uploadMesh(bool dynamic);
    private:
        ::Mesh _mesh;
};

}

#endif