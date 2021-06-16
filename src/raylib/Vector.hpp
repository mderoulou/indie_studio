/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Vector Class
*/

#ifndef RL_VECTOR_
#define RL_VECTOR_

#include "raylib.h"
#include "Color.hpp"

namespace rl {

class Vec2 : public ::Vector2
{
    public:
        Vec2();
        Vec2(float x, float y);
        Vec2(const Vec2 &vec);
        Vec2(const ::Vector2 vec);
        ~Vec2() {};

        void drawPixel(rl::Color color);
    private:
};

class Vec3 : public ::Vector3
{
    public:
        Vec3();
        Vec3(float x, float y, float z);
        Vec3(::Vector3 &vec) {
            x = vec.x;
            y = vec.y;
            z = vec.z;
        }
        ~Vec3() {};

        float &operator[](int i) {
            if (i == 0){
                return x;
            } else if (i == 1) {
                return y;
            } else if (i == 2) {
                return z;
            }
            return x;
        }


        Vec3 operator+(const Vec3 &other) const {
            return Vec3(x + other.x, y + other.y, z + other.z);
        }

        Vec3 operator-(const Vec3 &other) const {
            return Vec3(x - other.x, y - other.y, z - other.z);
        }

        Vec3 operator*(const Vec3 &other) const {
            return Vec3(x * other.x, y * other.y, z * other.z);
        }

        Vec3 operator/(const Vec3 &other) const {
            return Vec3(x / other.x, y / other.y, z / other.z);
        }

        Vec3 &operator+=(const Vec3 &other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vec3 &operator-=(const Vec3 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vec3 &operator*=(const Vec3 &other) {
            x *= other.x;
            y *= other.y;
            z *= other.z;
            return *this;
        }

        Vec3 &operator/=(const Vec3 &other) {
            x /= other.x;
            y /= other.y;
            z /= other.z;
            return *this;
        }


        Vec3 operator+(float val) const {
            return Vec3(x + val, y + val, z + val);
        }
        
        Vec3 operator-(float val) const {
            return Vec3(x - val, y - val, z - val);
        }

        Vec3 operator*(float val) const {
            return Vec3(x * val, y * val, z * val);
        }

        Vec3 operator/(float val) const {
            return Vec3(x / val, y / val, z / val);
        }

        Vec3 &operator+=(float val) {
            x += val;
            y += val;
            z += val;
            return *this;
        }

        Vec3 &operator-=(float val) {
            x -= val;
            y -= val;
            z -= val;
            return *this;
        }

        Vec3 &operator*=(float val) {
            x *= val;
            y *= val;
            z *= val;
            return *this;
        }

        Vec3 &operator/=(float val) {
            x /= val;
            y /= val;
            z /= val;
            return *this;
        }

        Vec3 &operator=(Vec3 val)
        {
            x = val.x;
            y = val.y;
            z = val.z;
            return *this;
        }
        
        bool operator!=(const Vec3 &second)
        {
            if (x != second.x)
                return true;
            if (y != second.y)
                return true;
            if (z != second.z)
                return true;
            return false;
        }

        void drawCube(rl::Vec3 size, rl::Color color);
        void drawCubeWires(rl::Vec3 size, rl::Color color);
    private:
};

class Vec4 : public ::Vector4
{
    public:
        Vec4();
        Vec4(float x1, float y1, float x2, float y2);
        Vec4(const Vec4 &vec);
        Vec4(const ::Vector4 &vec);
        ~Vec4() {};

        void drawLine(rl::Color color);
    private:
};

}

#endif
