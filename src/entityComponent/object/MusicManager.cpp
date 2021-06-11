/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** MusicManager
*/

#include "../Object.hpp"
#include "../../Indie.hpp"
#include <filesystem>
#include <vector>

MusicManager::MusicManager(Bomberman *win)
{
    _win = win;
    for (const auto &entry : std::filesystem::directory_iterator("../assets/musics/"))
        if (entry.path().extension().string() == ".mp3")
            _musics.push_back(entry.path().filename().string());
    for (const auto &entry : std::filesystem::directory_iterator("../assets/voices/"))
        if (entry.path().extension().string() == ".ogg")
            _voices.push_back(entry.path().filename().string());
    _music = nullptr;
    _sound = nullptr;
    _scene = -1;
    _mVol = 1.0;
    _sVol = 1.0;
}

MusicManager::~MusicManager()
{
    if (_music != nullptr)
        delete _music;
    if (_sound != nullptr)
        delete _sound;
}

void MusicManager::playMusic()
{
    uint32_t id = std::rand() % _musics.size();

    if (_music != nullptr) {
        delete _music;
        _music = nullptr;
    }
    _music = new rl::Music(std::string(std::string("../assets/musics/") + _musics[id]));
    _music->play();
    std::cout << "Playing :" << std::string(std::string("../assets/musics/") + _musics[id])<< std::endl;
}

void MusicManager::playSound(const std::string &name)
{
    if (_sound != nullptr) {
        delete _sound;
        _sound = nullptr;
    }
    for (std::string title : _voices)
        if (title == name) {
            _sound = new rl::Sound(std::string(std::string("../assets/voices/") + name));
            _sound->setVolume(_win->_manager->_settings._sVol);
            _sound->play();
        }
}

void MusicManager::render(rl::Camera3d *cam)
{
    if (_win->_manager->_settings._scene <= 2 && _music == nullptr)
        this->playMusic();
    if (_music != nullptr && _music->getTimePlayed() + 2 >= _music->getTimeLength())
        this->playMusic();
    if (_music != nullptr) {
        _music->update();
        _music->setVolume(_win->_manager->_settings._mVol);
    }
}
