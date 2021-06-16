/*
** EPITECH PROJECT, 2020
** YEP Indie Studio
** File description:
** Bomberman functions
*/

#include <iostream>
#include <fstream>
#include "Bomberman.hpp"
#include "rlgl.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
    #define GLSL_VERSION            100
#endif

/* * * * * * * * * * * *\
*                       *
*      SCENES LIST      *
*|_____________________|*
*                       *
*   0 => MAIN MENU      *
*   1 => OPTIONS        *
*   2 => GAME LOBBY     *
*   3 => GAME           *
*   4 => PAUSE          *
*   5 => SKIN MENU      *
*                       *
\***********************/

Bomberman::Bomberman()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    std::srand(time(NULL));
    _win = new rl::Window(800, 600, "Indie Studio");
    _win->setWindowIcon(rl::Image("../assets/logo.png"));
    std::unique_ptr<rl::Texture> logo = std::make_unique<rl::Texture>("../assets/menus/noui.png");
    while (!_win->ShouldClose()) {
        _win->beginDrawing();
        _win->clearBackground(rl::Color(255, 255, 255, 255));
        logo->draw(0, 0, rl::Color(255, 255, 255, 255));
        _win->endDrawing();
        break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    preLoad();
    createUI();
    setupWin();
}

Bomberman::~Bomberman()
{
    rl::Sound::CloseAudioDevice();
    delete _win;
    delete _manager;
}

#define PYTAGORE(x, y, z) (pow((float)(x)*(x)+(y)*(y)+(z)*(z), 0.5))

void Bomberman::generateMap(int type)
{
    int x = type;
    int y = type;


    rl::Vec2 spawnPoints[] = {
        {(float)1, (float)1},
        {(float)(x-1), (float)(y-1)},
        {(float)1, (float)(y-1)},
        {(float)(x-1), (float)1},
    };

    // Create the ground
    for (int i = 0; i < x; i += 1) {
        for (int j = 0; j < y; j += 1) {
            _manager->addComponent(new Floor(rl::Vec3(i, -1.0f, j),
                            rl::Vec3(1.02f, 1.02f, 1.02f),
                            rl::Color(200, 200, 200, 255), 3, _t._sb), 3);
        }
    }

    // fill with grid
    for (int xx = 0; xx < x; xx += 1){
        for (int yy = 0; yy < y; yy += 1){
            if (((xx+1) % 2 && (yy+1) % 2) || xx == 0 || xx == x-1 || yy == 0 || yy == y-1){
                _manager->addComponent(new Wall(rl::Vec3(xx, 0.0f, yy),
                    rl::Vec3(1.02f, 1.02f, 1.02f),
                    rl::Color(255, 255, 255, 255), 3, _t._sb), 3);
            } else {
                if (rand() % 4){
                    for (auto &vec : spawnPoints)
                        if (PYTAGORE(vec.x - xx, vec.y - yy, 0) < 3)
                            goto skip;
                    _manager->addComponent(new Box(rl::Vec3(xx, 0.0f, yy),
                        rl::Vec3(1.02f, 1.02f, 1.02f),
                        rl::Color(255, 255, 255, 255), 3, _t._wood), 3);
                    skip:;
                }
            }
        }
    }
    
}

void Bomberman::launch()
{
    Skybox *skybox = new Skybox();

    // _manager->_objs[3].clear();
    // loadMap();
    // _manager->_settings._scene = 3;
    

    while (!_win->ShouldClose() && !_ending) {
        _win->beginDrawing();
        ClearBackground(Color{255, 255, 255, 255});
        _win->clearBackground(rl::Color(255, 255, 255, 255));
        skybox->render(_manager->_cam);
        _t._ft->drawFPS(5, 25);
        _manager->manageCamera();
        _manager->handleEvent();
        _manager->simulate();
        _manager->renderAll();
        _win->endDrawing();
    }
}

void Bomberman::preLoad()
{
    _manager = new ComponentManager(this);
    BF::loadAll(this); //Load all available skins;
    loadSettings();
    rl::Sound::InitAudioDevice(); // Init audio

    _t._btn = std::make_shared<rl::Texture>("../assets/menus/btns.png");
    _t._ft = std::make_shared<rl::Font>("../assets/minecraftia.ttf");

    _t._sb = std::make_shared<rl::Texture>("../assets/block/stone-bricks.png");
    _t._sb_mod = std::make_shared<rl::Model>(_t._cube_mesh);
    _t._sb_mod->setMaterialTexture(0, _t._sb);
    
    _t._wood = std::make_shared<rl::Texture>("../assets/block/wood.png");
    _t._wood_mod = std::make_shared<rl::Model>(_t._cube_mesh);
    _t._wood_mod->setMaterialTexture(0, _t._wood);
    
    _t._tnt_a = std::make_shared<rl::Model>("../assets/block/tnt.glb");
    _t._power_speed = std::make_shared<rl::Model>("../assets/block/speed.glb");
    _t._power_bomb = std::make_shared<rl::Model>("../assets/block/bomb.glb");
    _t._power_size = std::make_shared<rl::Model>("../assets/block/explo.glb");
    _t._smoke = std::make_shared<rl::Model>("../assets/block/smoke.glb");
    _t._click = std::make_shared<rl::Sound>("../assets/musics/click.wav");
    _t._walking = std::make_shared<std::vector<std::shared_ptr<rl::Model>>>();
    std::ostringstream objPath("");

    for (int i = 1; i < 41; i++) {
        if (i < 10)
            objPath << "../assets/steve-obj/anims/steve_0" << i << ".glb";
        else
            objPath << "../assets/steve-obj/anims/steve_" << i << ".glb";
        _t._walking->push_back(std::make_shared<rl::Model>(objPath.str().c_str()));
        objPath.str("");
        objPath.clear();
    }
}

void Bomberman::createUI()
{
    std::vector<std::string>sizes{"Map size: Small", "Map size: Medium", "Map size: Large"};
    // USED BY OTHERS :
    MusicManager* musicManager = new MusicManager(this);
    _manager->_mm = musicManager;
    // HOME MENU :
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 0.0), "Play", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 0, this, &(BF::playBtn), (void*)musicManager, _t._btn, _t._ft), 0);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 60.0), "Skins", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 0, this, &(BF::skinBtn), 0, _t._btn, _t._ft), 0);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(104.0, 120.0), "Respository", 24, rl::Rectangle(400, 0, 196, 40), _t._click, 0, this, &(BF::repoLink), 0, _t._btn, _t._ft), 0);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(-100.0, 120.0), "Options", 24, rl::Rectangle(400, 0, 196, 40), _t._click, 0, this, &(BF::optBtn), 0, _t._btn, _t._ft), 0);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 180.0), "Quit Game", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 0, this, &(BF::quitBtn), 0, _t._btn, _t._ft), 0);
    // OPTIONS MENU :
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 0.0), std::string("FullScreen: ") + (_manager->_settings._fScreen ? "ON" : "OFF"), 24, rl::Rectangle(0, 0, 400, 40), _t._click, 1, this, &(BF::fullScreen), 0, _t._btn, _t._ft), 1);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 60.0), "Resolution: 800 x 600", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 1, this, &(BF::resolutionBtn), 0, _t._btn, _t._ft), 1);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 120.0), sizes[(int)_manager->_settings._sizeMap], 24, rl::Rectangle(0, 0, 400, 40), _t._click, 1, this, &(BF::mapSize), 0, _t._btn, _t._ft), 1);
    _manager->addComponent(new Slider(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 180.0), 24, rl::Rectangle(1040, 0, 300, 40), rl::Rectangle(1340, 0, 16, 40), 1, std::string(std::string("Musics: ") + std::to_string((int)(_manager->_settings._mVol * 100))) + "%", this, &(BF::setMusic), (void*)musicManager, _t._btn, _t._btn, _t._ft), 1);
    _manager->addComponent(new Slider(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 240.0), 24, rl::Rectangle(1040, 0, 300, 40), rl::Rectangle(1340, 0, 16, 40), 1, std::string(std::string("Sounds: ") + std::to_string((int)(_manager->_settings._sVol * 100))) + "%", this, &(BF::setSound), (void*)musicManager, _t._btn, _t._btn, _t._ft), 1);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 19.0 / 20), rl::Vec2(0.0, -60.0), "Save", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 1, this, &(BF::saveSettings), 0, _t._btn, _t._ft), 1);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 19.0 / 20), rl::Vec2(0.0, 0.0), "Done", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 1, this, &(BF::backBtn), 0, _t._btn, _t._ft), 1);
    // SKINS MENU :
    Preview* preview = new Preview(rl::Vec3(21, -0.5, 3), 1.2, 5, 90, rl::Color(255, 255, 255, 255), _t._walking);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 4.0 / 20), rl::Vec2(-340.0, 0.0), "+", 24, rl::Rectangle(596, 0, 40, 40), _t._click, 5, this, &(BF::addSkin), 0, _t._btn, _t._ft), 5);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 4.0 / 20), rl::Vec2(-290.0, 0.0), "-", 24, rl::Rectangle(596, 0, 40, 40), _t._click, 5, this, &(BF::removeSkin), 0, _t._btn, _t._ft), 5);
    _manager->addComponent(new Input(rl::Vec2(1.0 / 2, 4.0 / 20), rl::Vec2(-50.0, 0.0), _manager->_settings._optSkin, 16, 5, 24, this, _t._btn, _t._ft), 5);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 4.0 / 20), rl::Vec2(270.0, 0.0), "Load Preview", 24, rl::Rectangle(400, 0, 196, 40), _t._click, 5, this, &(BF::loadSkin), (void*)preview, _t._btn, _t._ft), 5);
    _manager->addComponent(preview, 5);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 19.0 / 20), rl::Vec2(0.0, 0.0), "Done", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 5, this, &(BF::backBtn), 0, _t._btn, _t._ft), 5);
    _manager->addComponent(new List(rl::Vec2(1.0 / 2, 7.0 / 20), rl::Vec2(-350, 0.0), rl::Vec2(0.0, 35.0), 24, 5, this, &(_manager->_settings._skins), &(BF::previewSkin), preview, _t._ft, true, 4), 5);
    //GAME LOBBY :
    GameOpt* go = new GameOpt(this, 2, _t._ft);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 19.0 / 20), rl::Vec2(0.0, -60.0), "Load from save", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 2, this, &(BF::loadGame), (void*)go, _t._btn, _t._ft), 2);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 19.0 / 20), rl::Vec2(104.0, 0.0), "Fight", 24, rl::Rectangle(400, 0, 196, 40), _t._click, 2, this, &(BF::launchGame), (void*)go, _t._btn, _t._ft), 2);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 19.0 / 20), rl::Vec2(-100.0, 0.0), "Back", 24, rl::Rectangle(400, 0, 196, 40), _t._click, 2, this, &(BF::backBtn), 0, _t._btn, _t._ft), 2);
    _manager->addComponent(go, 2);
    //PAUSE MENU:
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 0.0), "Play", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 4, this, &(BF::unpauseBtn), 0, _t._btn, _t._ft), 4);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 60.0), "Save", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 4, this, &(BF::saveBtn), 0, _t._btn, _t._ft), 4);
    _manager->addComponent(new Btn(rl::Vec2(1.0 / 2, 5.0 / 20), rl::Vec2(0.0, 120.0), "Quit", 24, rl::Rectangle(0, 0, 400, 40), _t._click, 4, this, &(BF::homeBtn), 0, _t._btn, _t._ft), 4);

    // ALL MENUS :
    _manager->addComponent(musicManager, 6);
    _manager->addComponent(new EscManager(this, -1), 6);
}

void Bomberman::setupWin()
{
    _win->changeFps(60);
    rl::Window::SetExitKey(-1);
}

void Bomberman::saveSettings()
{
    std::ofstream file("settings.yep", std::ofstream::trunc | std::ofstream::binary | std::ofstream::out);
    if (!file.is_open()) return;
    uint magic = 0x87654321; // MAGIIICCCCC
    file.write((char *)&magic, sizeof(magic));   
    file.write((char *)&_manager->_settings._sizeMap, sizeof(_manager->_settings._sizeMap));
    file.write((char *)&_manager->_settings._fScreen, sizeof(_manager->_settings._fScreen));
    file.write((char *)&_manager->_settings._mVol, sizeof(_manager->_settings._mVol));
    file.write((char *)&_manager->_settings._sVol, sizeof(_manager->_settings._sVol));
    file.write((char *)&_manager->_settings._width, sizeof(_manager->_settings._width));
    file.write((char *)&_manager->_settings._height, sizeof(_manager->_settings._height));
    std::cerr << "Settings successfully saved!" << std::endl;
}

void Bomberman::loadSettings()
{
    std::ifstream file("settings.yep", std::ifstream::binary);
    uint magic;
    uint size;
    if (!file.is_open())
        return;
    file.read((char *)&magic, sizeof(magic));
    if (magic != 0x87654321) {
        std::cerr << "Settings : Bad Magic Number "<< magic << std::endl;
        return;
    }
    file.read((char *)&_manager->_settings._sizeMap, sizeof(_manager->_settings._sizeMap));
    file.read((char *)&_manager->_settings._fScreen, sizeof(_manager->_settings._fScreen));
    file.read((char *)&_manager->_settings._mVol, sizeof(_manager->_settings._mVol));
    file.read((char *)&_manager->_settings._sVol, sizeof(_manager->_settings._sVol));
    file.read((char *)&_manager->_settings._width, sizeof(_manager->_settings._width));
    file.read((char *)&_manager->_settings._height, sizeof(_manager->_settings._height));
    file.close();
    if (_manager->_settings._fScreen)
        _win->setFullscreen();
    if (_manager->_settings._width >= 800)
        _win->setWindowSize(_manager->_settings._width, _manager->_settings._height);
    std::cerr << "Settings successfully loaded!" << std::endl;
}

void Bomberman::saveMap()
{
    std::ofstream file("save.yep", std::ofstream::trunc | std::ofstream::binary | std::ofstream::out);
    if (!file.is_open()) return;
    uint magic = 0x12345678; // MAGIIICCCCC
    file.write((char *)&magic, sizeof(magic));   
    file.write((char *)&_manager->_cam->position, sizeof(_manager->_cam->position));
    file.write((char *)&_manager->_cam->target, sizeof(_manager->_cam->target));
    file.write((char *)&_manager->_cam->up, sizeof(_manager->_cam->up));
    file.write((char *)&_manager->_cam->fovy, sizeof(_manager->_cam->fovy));
    file.write((char *)&_manager->_cam->projection, sizeof(_manager->_cam->projection));
    file.write((char *)&_manager->_cam->_isStarted, sizeof(_manager->_cam->_isStarted));

    file << _manager->_objs[3].size();
    for (auto &obj : _manager->_objs[3]) {
        file << *obj->dump();
    }
}

bool Bomberman::loadMap()
{
    std::ifstream file("save.yep", std::ifstream::binary);
    uint magic;
    uint size;
    std::cerr << "opening file" << std::endl;
    if (!file.is_open()) return false;
    std::cerr << "file opened" << std::endl;
    file.read((char *)&magic, sizeof(magic));
    if (magic != 0x12345678) {
        std::cerr << "Bad Magic Number "<< magic << std::endl;
        return false;
    }
    file.read((char *)&_manager->_cam->position, sizeof(_manager->_cam->position));
    file.read((char *)&_manager->_cam->target, sizeof(_manager->_cam->target));
    file.read((char *)&_manager->_cam->up, sizeof(_manager->_cam->up));
    file.read((char *)&_manager->_cam->fovy, sizeof(_manager->_cam->fovy));
    file.read((char *)&_manager->_cam->projection, sizeof(_manager->_cam->projection));
    file.read((char *)&_manager->_cam->_isStarted, sizeof(_manager->_cam->_isStarted));

    std::vector<std::vector<int>> keys{ 
        {KeyboardKey::KEY_W, KeyboardKey::KEY_S, KeyboardKey::KEY_A, KeyboardKey::KEY_D, KeyboardKey::KEY_E, KeyboardKey::KEY_Q},
        {KeyboardKey::KEY_UP, KeyboardKey::KEY_DOWN, KeyboardKey::KEY_LEFT, KeyboardKey::KEY_RIGHT, KeyboardKey::KEY_SPACE, KeyboardKey::KEY_ENTER},
        {KeyboardKey::KEY_KP_5, KeyboardKey::KEY_KP_2, KeyboardKey::KEY_KP_1, KeyboardKey::KEY_KP_3, KeyboardKey::KEY_KP_6, KeyboardKey::KEY_KP_4},
        {KeyboardKey::KEY_I, KeyboardKey::KEY_K, KeyboardKey::KEY_J, KeyboardKey::KEY_L, KeyboardKey::KEY_O, KeyboardKey::KEY_U}
    };
    
    file >> size;
    uint playerCount = 0;

    std::shared_ptr<ByteObject> obj = std::make_shared<ByteObject>();
    for (int i = 0; i < size; i++) {
        int type;
        file >> *obj;
        if (!obj->size)
            continue;
        *obj >> type;
        switch (type) {
            case ByteObject::PLAYER:
                //std::cout << "load Player" << std::endl;
                _manager->addComponent(new Player(obj, _t._walking, std::make_shared<KeyBoard>(-1, keys[playerCount])), 3);
                playerCount++;
                break;
            case ByteObject::WALL:
                //std::cout << "load Wall" << std::endl;
                _manager->addComponent(new Wall(obj, _t._sb), 3);
                break;
            case ByteObject::FLOOR:
                //std::cout << "load Floor" << std::endl;
                _manager->addComponent(new Floor(obj, _t._sb), 3);
                break;
            case ByteObject::BOX:
                //std::cout << "load Box" << std::endl;
                _manager->addComponent(new Box(obj, _t._wood), 3);
                break;
            case ByteObject::PLAYERAI:
                //std::cout << "load IA" << std::endl;
                _manager->addComponent(PlayerAI::factory(obj, _t._walking), 3);
                break;
            case ByteObject::POWERUP:
                _manager->addComponent(PowerUp::factory(obj, this), 3);
                //_manager->addComponent(new PowerUp(obj, _t._tnt_a), 3);
                break;
            case ByteObject::DEFAULT:
                //std::cerr << "Default type " << type << std::endl;
                break;
            default:
                std::cerr << "Bad Type : " << type << std::endl;
                return false;
        }
    }
    file.close();
    return true;
}