/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Music Functions
*/

#include "Music.hpp"

/**
 *  Music Functions
 */

rl::Music::Music(const std::string filename)
{
    _music = LoadMusicStream(filename.c_str());
}

rl::Music::~Music()
{
    UnloadMusicStream(_music);
}

void rl::Music::play()
{
    PlayMusicStream(_music);
}

void rl::Music::pause()
{
    PauseMusicStream(_music);
}

void rl::Music::stop()
{
    StopMusicStream(_music);
}

void rl::Music::resume()
{
    ResumeMusicStream(_music);
}

void rl::Music::setVolume(float volume)
{
    SetMusicVolume(_music, volume);
}

void rl::Music::setPitch(float pitch)
{
    SetMusicPitch(_music, pitch);
}

float rl::Music::getTimePlayed()
{
    return GetMusicTimePlayed(_music);
}

float rl::Music::getTimeLength()
{
    return GetMusicTimeLength(_music);
}

void rl::Music::update()
{
    ::UpdateMusicStream(_music);
}

/**
 *  AudioStream Functions
 */

rl::AudioStream::AudioStream(unsigned int sampleRate, unsigned int sampleSizen, unsigned int channels)
{
    _as = InitAudioStream(sampleRate, sampleSizen, channels);
}

rl::AudioStream::~AudioStream()
{
    CloseAudioStream(_as);
}

void rl::AudioStream::play()
{
    PlayAudioStream(_as);
}

void rl::AudioStream::pause()
{
    PauseAudioStream(_as);
}

void rl::AudioStream::resume()
{
    ResumeAudioStream(_as);
}

void rl::AudioStream::stop()
{
    StopAudioStream(_as);
}

void rl::AudioStream::setVolume(float volume)
{
    SetAudioStreamVolume(_as, volume);
}

void rl::AudioStream::setPitch(float pitch)
{
    SetAudioStreamPitch(_as, pitch);
}
