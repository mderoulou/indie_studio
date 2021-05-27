/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Error
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <string>
#include <exception>


class RaylibError : public std::exception
{
    public:
        RaylibError(std::string const &message, std::string const &component = "RaylibError")
        : _message(message), _component(component) {};

        std::string const &getComponent() const noexcept { return _component;};
        const char *what() const noexcept {return _message.c_str();};
    private:
        std::string _message;
        std::string _component;
};

class WindowError : public RaylibError
{
    public:
        WindowError(std::string const &message, std::string const &component = "Window Error")
        : RaylibError(message, component) {};
};

class InvalidArgError : public RaylibError
{
    public:
        InvalidArgError(std::string const &message, std::string const &component = "Argument Error")
        : RaylibError(message, component) {};
};

#endif