/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** MusicManager
*/

#ifndef MUSICMANAGER_HPP_
#define MUSICMANAGER_HPP_

#include "../Object.hpp"
#include <unordered_map>

class MusicManager : public Object2D {
    public:
        MusicManager(Bomberman *);
        ~MusicManager();

        void playMusic();
        void playSound(const std::string &name, bool multi = true);
        void render(rl::Camera3d *cam) override;
        float _mVol;
        float _sVol;
    private:
        rl::Music *_music;
        Bomberman *_win;
        std::vector<std::string> _musics;
        std::unordered_map<std::string, std::unique_ptr<rl::Sound>> _sounds;
};

#endif /* !MUSICMANAGER_HPP_ */
