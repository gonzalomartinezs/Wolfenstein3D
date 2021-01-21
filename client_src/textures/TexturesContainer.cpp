#include "TexturesContainer.h"
#include <SDL2/SDL_image.h>

#define WALL_PATH "../client_src/textures/img/sprites/rocky.bmp"
#define BARREL_PATH "../client_src/textures/img/sprites/barrel.bmp"
#define GUARD_0_PATH "../client_src/textures/img/sprites/guard_0.bmp"
#define GUARD_1_PATH "../client_src/textures/img/sprites/guard_1.bmp"
#define GUARD_2_PATH "../client_src/textures/img/sprites/guard_2.bmp"
#define GUARD_3_PATH "../client_src/textures/img/sprites/guard_3.bmp"
#define GUARD_4_PATH "../client_src/textures/img/sprites/guard_4.bmp"
#define GUARD_5_PATH "../client_src/textures/img/sprites/guard_5.bmp"
#define GUARD_6_PATH "../client_src/textures/img/sprites/guard_6.bmp"
#define GUARD_7_PATH "../client_src/textures/img/sprites/guard_7.bmp"
#define BJ_0_PATH "../client_src/textures/img/miscellaneous/bj_0.bmp"
#define BJ_1_PATH "../client_src/textures/img/miscellaneous/bj_1.bmp"
#define BJ_2_PATH "../client_src/textures/img/miscellaneous/bj_2.bmp"
#define BJ_3_PATH "../client_src/textures/img/miscellaneous/bj_3.bmp"
#define BJ_4_PATH "../client_src/textures/img/miscellaneous/bj_4.bmp"
#define BJ_5_PATH "../client_src/textures/img/miscellaneous/bj_5.bmp"
#define BJ_6_PATH "../client_src/textures/img/miscellaneous/bj_6.bmp"
#define BJ_7_PATH "../client_src/textures/img/miscellaneous/bj_7.bmp"
#define KNIFE_INTERFACE "../client_src/textures/img/miscellaneous/knife_interface.bmp"
#define PISTOL_INTERFACE "../client_src/textures/img/miscellaneous/pistol_interface.bmp"
#define MACHINE_INTERFACE "../client_src/textures/img/miscellaneous/machinegun_interface.bmp"
#define CHAIN_INTERFACE "../client_src/textures/img/miscellaneous/chaingun_interface.bmp"
#define RPG_INTERFACE "../client_src/textures/img/miscellaneous/rpg_interface.bmp"
#define KEY_PATH "../client_src/textures/img/miscellaneous/has_key.bmp"
#define NOT_KEY_PATH "../client_src/textures/img/miscellaneous/has_not_key.bmp"
#define BACKGROUND "../client_src/textures/img/miscellaneous/back.png"
#define PL_INTERFACE "../client_src/textures/img/miscellaneous/interface_1.png"

TexturesContainer::TexturesContainer(SDL_Renderer *renderer,
                                     SDL_Surface *window_surface)
        : renderer(renderer), window_surface(window_surface){
    IMG_Init(IMG_INIT_PNG);
    textures.emplace(None, nullptr);
    textures.emplace(Wall, new Texture(WALL_PATH, this->renderer));
    textures.emplace(Barrel, new Texture(BARREL_PATH, this->renderer));
    textures.emplace(Guard_0, new Texture(GUARD_0_PATH, this->renderer));
    textures.emplace(Guard_1, new Texture(GUARD_1_PATH, this->renderer));
    textures.emplace(Guard_2, new Texture(GUARD_2_PATH, this->renderer));
    textures.emplace(Guard_3, new Texture(GUARD_3_PATH, this->renderer));
    textures.emplace(Guard_4, new Texture(GUARD_4_PATH, this->renderer));
    textures.emplace(Guard_5, new Texture(GUARD_5_PATH, this->renderer));
    textures.emplace(Guard_6, new Texture(GUARD_6_PATH, this->renderer));
    textures.emplace(Guard_7, new Texture(GUARD_7_PATH, this->renderer));
    textures.emplace(BJ_0, new Texture(BJ_0_PATH, this->renderer));
    textures.emplace(BJ_1, new Texture(BJ_1_PATH, this->renderer));
    textures.emplace(BJ_2, new Texture(BJ_2_PATH, this->renderer));
    textures.emplace(BJ_3, new Texture(BJ_3_PATH, this->renderer));
    textures.emplace(BJ_4, new Texture(BJ_4_PATH, this->renderer));
    textures.emplace(BJ_5, new Texture(BJ_5_PATH, this->renderer));
    textures.emplace(BJ_6, new Texture(BJ_6_PATH, this->renderer));
    textures.emplace(BJ_7, new Texture(BJ_7_PATH, this->renderer));
    textures.emplace(KnifeInterface, new Texture(KNIFE_INTERFACE, this->renderer));
    textures.emplace(PistolInterface, new Texture(PISTOL_INTERFACE, this->renderer));
    textures.emplace(MachineGunInterface, new Texture(MACHINE_INTERFACE, this->renderer));
    textures.emplace(ChainGunInterface, new Texture(CHAIN_INTERFACE, this->renderer));
    textures.emplace(RPGInterface, new Texture(RPG_INTERFACE, this->renderer));
    textures.emplace(HasKey, new Texture(KEY_PATH, this->renderer));
    textures.emplace(HasNotKey, new Texture(NOT_KEY_PATH, this->renderer));
    textures.emplace(Background,new Texture(BACKGROUND,
                                        this->renderer, this->window_surface));
    textures.emplace(MainInterface, new Texture(PL_INTERFACE,
                                        this->renderer, this->window_surface));
}

Texture* TexturesContainer::get(TextureID id) {
    return textures[id];
}

TexturesContainer::~TexturesContainer() {
    for (std::pair<TextureID, Texture*> tex:textures){
        delete tex.second;
        tex.second = nullptr;
    }
    IMG_Quit();
}
