/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Music Class
*/

#ifndef RL_MUSIC_
#define RL_MUSIC_

#include "raylib.h"
#include <string>

namespace rl {

class Music
{
    public:
        Music(const std::string filename);
        ~Music();

        void play();
        void stop();
        void pause();
        void resume();
        void update();

        void setVolume(float volume);
        void setPitch(float pitch);

        float getTimeLength();
        float getTimePlayed();

    private:
        ::Music _music;
};

class AudioStream
{
    public:
        AudioStream(unsigned int sampleRate, unsigned int sampleSizen, unsigned int channels);
        ~AudioStream();

        void play();
        void pause();
        void resume();
        void stop();
        void setVolume(float volume);
        void setPitch(float pitch);

    private:
        ::AudioStream _as;
};

}

#endif