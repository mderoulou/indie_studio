/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Raylib Sound Functions
*/

#include "Sound.hpp"

/**
 * Wave Functions
 */

rl::Wave::Wave(const std::string filename)
{
    _wave = LoadWave(filename.c_str());
}

rl::Wave::~Wave()
{
    UnloadWave(_wave);
}

/**
 * Sound Functions
 */

rl::Sound::Sound(const std::string filename)
{
    _sound = LoadSound(filename.c_str());
}

rl::Sound::Sound(const rl::Wave wave)
{
    _sound = LoadSoundFromWave(wave.getWave());
}

rl::Sound::~Sound()
{
    UnloadSound(_sound);
}

void rl::Sound::play()
{
    PlaySound(_sound);
}

void rl::Sound::pause()
{
    PauseSound(_sound);
}

void rl::Sound::stop()
{
    StopSound(_sound);
}

void rl::Sound::resume()
{
    ResumeSound(_sound);
}

void rl::Sound::playMulti()
{
    PlaySoundMulti(_sound);
}

void rl::Sound::stopMulti()
{
    StopSoundMulti();
}

void rl::Sound::setVolume(float volume)
{
    SetSoundVolume(_sound, volume);
}

void rl::Sound::setPitch(float pitch)
{
    SetSoundPitch(_sound, pitch);
}