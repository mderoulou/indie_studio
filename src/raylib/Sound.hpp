/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Sound Class
*/

#ifndef RL_SOUND_
#define RL_SOUND_

#include "raylib.h"
#include <string>

namespace rl {

class Wave
{
    public:
        Wave(const std::string fileName);
        ~Wave();

        ::Wave getWave() const { return _wave; };
    private:
        ::Wave _wave;
};

class Sound
{
    public:
        Sound(const std::string fileName);
        Sound(const rl::Wave wave);
        ~Sound();

        void play();
        void stop();
        void pause();
        void resume();

        void playMulti();
        void stopMulti();

        void setVolume(float volume);
        void setPitch(float pitch);

        static void InitAudioDevice() { ::InitAudioDevice(); };
        static void CloseAudioDevice() { ::CloseAudioDevice(); };
        static bool IsAudioDeviceReady() { return ::IsAudioDeviceReady(); };

        ::Sound getSound() const { return _sound; };
    private:
        ::Sound _sound;
};

}

#endif