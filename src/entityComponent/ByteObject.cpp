/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Indie Object Class
*/

#include <ostream>
#include <fstream>
#include "ByteObject.hpp"

std::basic_istream<char> &operator>>(std::basic_istream<char> &stream, ByteObject &obj) {
    stream.read((char *)&obj.size, sizeof(obj.size));
    obj.data.resize((int)obj.size);
    stream.read((char *)&(obj.data[0]), obj.size);
    obj.setCursor(0);
    return stream;
}

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &stream, const ByteObject &obj)
{
    stream.write((char *)&obj.size, sizeof(obj.size));
    stream.write((char *)&(obj.data[0]), obj.size);
    return stream;
}