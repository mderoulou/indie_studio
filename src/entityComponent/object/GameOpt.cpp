/*
** EPITECH PROJECT, 2021
** indie_studio
** File description:
** GameOpt
*/

#include "../Object.hpp"
#include "../Manager.hpp"
#include "../../functionalities/Control.hpp"

GameOpt::GameOpt(Bomberman *win, int scene, std::shared_ptr<rl::Font> font)
    : _win(win),
    _types(4, 0),
    _keys{ 
        { KeyboardKey::KEY_W, KeyboardKey::KEY_S, KeyboardKey::KEY_A, KeyboardKey::KEY_D, KeyboardKey::KEY_E, KeyboardKey::KEY_Q},
        { KeyboardKey::KEY_UP, KeyboardKey::KEY_DOWN, KeyboardKey::KEY_LEFT, KeyboardKey::KEY_RIGHT, KeyboardKey::KEY_SPACE, KeyboardKey::KEY_ENTER},
        { KeyboardKey::KEY_KP_5, KeyboardKey::KEY_KP_2, KeyboardKey::KEY_KP_1, KeyboardKey::KEY_KP_3, KeyboardKey::KEY_KP_6, KeyboardKey::KEY_KP_4},
        { KeyboardKey::KEY_I, KeyboardKey::KEY_K, KeyboardKey::KEY_J, KeyboardKey::KEY_L, KeyboardKey::KEY_O, KeyboardKey::KEY_U}
    }
{
    std::shared_ptr<Preview> preview = nullptr;
    std::shared_ptr<Btn> b = nullptr;
    _scene = scene;
    _win = win;
    _font = font;
    for (int x = 0; x < 4; x++)
        _names.push_back("skin.png");
    _win->_manager->addComponent(std::make_shared<Btn>(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-300.0, 60.0), "skin", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, win, &(BF::switchSkin), (void *)0, win->_t._btn, _win->_t._ft), 2);
    _win->_manager->addComponent(std::make_shared<Btn>(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-100.0, 60.0), "skin", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, win, &(BF::switchSkin), (void *)1, _win->_t._btn, _win->_t._ft), 2);
    _win->_manager->addComponent(std::make_shared<Btn>(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(104.0, 60.0), "skin", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, win, &(BF::switchSkin), (void *)2, _win->_t._btn, _win->_t._ft), 2);
    _win->_manager->addComponent(std::make_shared<Btn>(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(304.0, 60.0), "skin", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, win, &(BF::switchSkin), (void *)3, _win->_t._btn, _win->_t._ft), 2);
    
    preview = std::make_shared<Preview>(rl::Vec3(20, 0, -5), 0.75, 2, 90, rl::Color(255,255,255,255), _win->_t._walking);
    b = std::make_shared<Btn>(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-300.0, 0.0), "None", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, _win, &(BF::switchType), (void *)0, _win->_t._btn, _win->_t._ft);
    _btns.push_back(b);
    _previews.push_back(preview);
    _win->_manager->addComponent(b, 2);
    _win->_manager->addComponent(preview, 2);
    preview->_disabled = true;
    
    preview = std::make_shared<Preview>(rl::Vec3(21, 0, -1), 0.75, 2, 90, rl::Color(255,255,255,255), _win->_t._walking);
    b = std::make_shared<Btn>(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(-100.0, 0.0), "None", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, _win, &(BF::switchType), (void *)1, _win->_t._btn, _win->_t._ft);
    _btns.push_back(b);
    _previews.push_back(preview);
    _win->_manager->addComponent(b, 2);
    _win->_manager->addComponent(preview, 2);
    preview->_disabled = true;
    
    preview = std::make_shared<Preview>(rl::Vec3(21, 0, 3), 0.75, 2, 90, rl::Color(255,255,255,255), _win->_t._walking);
    b = std::make_shared<Btn>(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(104, 0.0), "None", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, _win, &(BF::switchType), (void *)2, _win->_t._btn, _win->_t._ft);
    _btns.push_back(b);
    _previews.push_back(preview);
    _win->_manager->addComponent(b, 2);
    _win->_manager->addComponent(preview, 2);
    preview->_disabled = true;
    
    preview = std::make_shared<Preview>(rl::Vec3(20, 0, 7), 0.75, 2, 90, rl::Color(255,255,255,255), _win->_t._walking);
    b = std::make_shared<Btn>(rl::Vec2(1.0/2, 5.0/20), rl::Vec2(304, 0.0), "None", 24, rl::Rectangle(400,0,196,40), _win->_t._click, 2, _win, &(BF::switchType), (void *)3, _win->_t._btn, _win->_t._ft);
    _btns.push_back(b);
    _previews.push_back(preview);
    _win->_manager->addComponent(b, 2);
    _win->_manager->addComponent(preview, 2);
    preview->_disabled = true;
    
    for (int x = 0; x < 4; x++)
        _controllers.push_back(0);
}

void GameOpt::simulate()
{
    int count = 0;
    int id = 0;
    float posx[] = {-350.0, -150.0, 4.0, 204.0};

    for (int x = 0; x < 4; x++) {
        if (!_controllers[x] && !_types[x]) { // Controller not set
            _win->_t._ft->drawTextEx("Press a Key", rl::Vec2(1.0/2.0 * (float)_win->_win->getScreenWidth() + posx[x],  5.0/20.0 * (float)_win->_win->getScreenHeight() + 200.0), 24, 0.0, rl::Color(0,0,0,255));
            if ((id = Controls::newControls()) >= 0) {// GamePad was pressed!
                for (auto controller : _controllers) // Is it already binded ?
                    if (controller && controller->_id == id)
                        return;
                if (id >= 0) {
                    _btns[x]->_text = "Player";
                    _previews[x]->_disabled = false;
                    _types[x] = 1;
                }
                if (id >= 0 && id <= 3)
                    _controllers[x] = std::make_shared<GamePad>(id); 
                if (id == 4)
                    _controllers[x] = std::make_shared<KeyBoard>(-1, _keys[x]);
            } else
                break;
        }
    }
}