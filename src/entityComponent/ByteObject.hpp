/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#ifndef BYTEOBJECT_OBJ_
#define BYTEOBJECT_OBJ_

#include <vector>
#include <string.h>
#include <ostream>

#ifdef _WIN32 
typedef unsigned int uint;
#endif 

class ByteObject
{
    public:

        enum ObjectType {
            PLAYER,
            PLAYERAI,
            BOX,
            WALL,
            FLOOR,
            DEFAULT,
            POWERUP,
        };

        ByteObject() {
            size = 0;
            data.resize(0);
        }

        ByteObject(std::vector<char> &data, uint size) :
            data(data), size(size)
        {}

        ~ByteObject(){}

        ByteObject &operator+(const ByteObject &that) const 
        {
            int newSize = that.size + this->size;
            std::vector<char> newData;
            newData.insert(newData.end(), this->data.begin(), this->data.end());
            newData.insert(newData.end(), that.data.begin(), that.data.end());
            ByteObject *obj = new ByteObject(newData, newSize);
            return *obj;
        }

        template <typename T>
        ByteObject &operator<<(T &&thing) {
            data.resize(size + sizeof(T));
            memcpy(&data[size], &thing, sizeof(T));
            size += sizeof(T);
            return *this;
        };

        template <typename T>
        ByteObject &operator>>(T &thing) {
            memcpy(&thing, &data[cursor] , sizeof(T));
            cursor += sizeof(T);
            return *this;
        };

        void setCursor(int val) {
            cursor = val;
        }        

        uint size = 0;
        uint cursor = 0;
        std::vector<char> data;
    private:    
};

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const ByteObject &obj);
std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, ByteObject &obj);


#endif