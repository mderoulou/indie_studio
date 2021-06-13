/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Mesh Functions
*/

#include "Mesh.hpp"

rl::Mesh::Mesh(int sides, float radius)
{
    _mesh = GenMeshPoly(sides, radius);
}

rl::Mesh::Mesh(float width, float length, int resX, int resZ)
{
    _mesh = GenMeshPlane(width, length, resX, resZ);
}

rl::Mesh::Mesh(float width, float height, float length)
{
    _mesh = GenMeshCube(width, height, length);
}

rl::Mesh::Mesh(float radius, int rings, int slices)
{
    _mesh = GenMeshSphere(radius, rings, slices);
}

rl::Mesh::Mesh(rl::Image map, rl::Vec3 size, int type)
{
    if (type == 1)
        _mesh = GenMeshHeightmap(map.getImg(), size);
    else
        _mesh = GenMeshCubicmap(map.getImg(), size);

}

rl::Mesh::~Mesh()
{
    //UnloadMesh(_mesh);
}

void rl::Mesh::computeTangents()
{
    MeshTangents(&this->_mesh);
}

void rl::Mesh::computeBinormals()
{
    MeshTangents(&this->_mesh);
}

bool rl::Mesh::exportMesh(const std::string filename)
{
    return ExportMesh(this->_mesh, filename.c_str());
}

void rl::Mesh::uploadMesh(bool dynamic)
{
    UploadMesh(&this->_mesh, dynamic);
}