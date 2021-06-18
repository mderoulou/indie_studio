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
    for (const auto &entry : std::filesystem::directory_iterator("assets/musics/"))
        if (entry.path().extension().string() == ".mp3")
            _musics.push_back(entry.path().filename().string());
    for (const auto &entry : std::filesystem::directory_iterator("assets/voices/"))
        if (entry.path().extension().string() == ".ogg") {
            _sounds[entry.path().filename().string()] = std::make_unique<rl::Sound>(std::string("assets/voices/") + entry.path().filename().string());
        }
    _music = nullptr;
    _scene = -1;
    _mVol = 1.0;
    _sVol = 1.0;
}

MusicManager::~MusicManager()
{
    rl::Sound::StopSoundMulti();
    if (_music != nullptr)
        delete _music;
}

void MusicManager::playMusic()
{
    try {
        uint32_t id = std::rand() % _musics.size();

        if (_music != nullptr) {
            delete _music;
            _music = nullptr;
        }
        if (!rl::Sound::IsAudioDeviceReady())
            return;
            _music = new rl::Music(std::string(std::string("assets/musics/") + _musics[id]));
            _music->play();
            std::cout << "Playing :" << std::string(std::string("assets/musics/") + _musics[id]) << std::endl;
    } catch (...) {
        std::cerr << "Unable to play music! Passing ..." << std::endl;
    }
}

void MusicManager::playSound(const std::string &name, bool multi)
{
    try {
        if (!rl::Sound::IsAudioDeviceReady())
            return;
        _sounds[name]->setVolume(_win->_manager->_settings._sVol);
        if (multi)
            _sounds[name]->playMulti();
        else
            _sounds[name]->play();
    } catch (...) {
        std::cerr << "Unable to play sound! Passing ..." << std::endl;
    }
}

void MusicManager::render(rl::Camera3d *cam)
{
    try {
        if (_win->_manager->_settings._scene <= 2 && _music == nullptr)
            this->playMusic();
        if (_music != nullptr && _music->getTimePlayed() + 2 >= _music->getTimeLength())
            this->playMusic();
        if (_music != nullptr) {
            _music->update();
            _music->setVolume(_win->_manager->_settings._mVol);
        }
    } catch (...) {
        std::cerr << "Error rendering musics! Passing ..." << std::endl;
    }
}
