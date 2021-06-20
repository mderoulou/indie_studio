/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomberman Class
*/

#ifndef BOMB_CLASS_
#define BOMB_CLASS_

#include "entityComponent/Manager.hpp"
#include "functionalities/BtnFuncs.hpp"
#include "Indie.hpp"
#include <thread>
#include <chrono>
#include <memory>

class ComponentManager;
class GameOpt;

class allTexture
{
    public:
        std::shared_ptr<rl::Texture> _btn; // Btn texture
        std::shared_ptr<rl::Texture> _sb; // StoneBrick texture
        std::shared_ptr<rl::Texture> _redstone; // Redstone texture
        std::shared_ptr<rl::Texture> _dirt; // Dirt texture
        std::shared_ptr<rl::Model> _sb_mod;
        std::shared_ptr<rl::Texture> _wood; // wood texture
        std::shared_ptr<rl::Model> _wood_mod;
        std::shared_ptr<rl::Font> _ft; // Minecraft font
        std::shared_ptr<rl::Sound> _click;
        std::shared_ptr<std::vector<std::shared_ptr<rl::Model>>> _walking; // Walking Animation
        std::shared_ptr<rl::Model> _tnt_a;
        std::shared_ptr<rl::Model> _smoke;
        std::shared_ptr<rl::Model> _power_speed;
        std::shared_ptr<rl::Model> _power_bomb;
        std::shared_ptr<rl::Model> _power_size;
        rl::Mesh _cube_mesh = {1, 1, 1};
};

class Skybox;

class Bomberman
{
    public:
        Bomberman();
        ~Bomberman();

        void launch();
        void generateMap(int type);
        ComponentManager *_manager;
        allTexture _t;
        rl::Window *_win;
        bool _ending = false;
        Skybox *_skybox;
        void saveMap();
        void saveSettings();
        bool loadMap();
        void loadSettings();
    private:
        void createUI();
        void preLoad();
        void setupWin();
};
#endif