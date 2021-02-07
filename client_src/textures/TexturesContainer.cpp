#include "TexturesContainer.h"
#include <SDL2/SDL_image.h>

#define WALL_PATH "../client_src/textures/img/sprites/rocky.bmp"
#define DOOR_PATH "../client_src/textures/img/sprites/door.bmp"
#define INVERTED_DOOR_PATH "../client_src/textures/img/sprites/inv_door.bmp"
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
#define KNIFE_HUD "../client_src/textures/img/miscellaneous/knife_interface.bmp"
#define PISTOL_HUD "../client_src/textures/img/miscellaneous/pistol_HUD.bmp"
#define MACHINE_HUD "../client_src/textures/img/miscellaneous/machinegun_HUD.bmp"
#define CHAIN_HUD "../client_src/textures/img/miscellaneous/chaingun_HUD.bmp"
#define RPGHUD "../client_src/textures/img/miscellaneous/rpg_HUD.bmp"
#define KEY_PATH "../client_src/textures/img/miscellaneous/has_key.bmp"
#define NOT_KEY_PATH "../client_src/textures/img/miscellaneous/has_not_key.bmp"
#define BACKGROUND "../client_src/textures/img/miscellaneous/back.png"
#define PL_HUD "../client_src/textures/img/miscellaneous/HUD_1.png"
#define PISTOL_PL "../client_src/textures/img/sprites/magnum.bmp"
#define PISTOL_PL_1 "../client_src/textures/img/sprites/magnum(1).bmp"
#define PISTOL_PL_2 "../client_src/textures/img/sprites/magnum(2).bmp"
#define PISTOL_PL_3 "../client_src/textures/img/sprites/magnum(3).bmp"
#define PISTOL_PL_4 "../client_src/textures/img/sprites/magnum(4).bmp"
#define PISTOL_PL_5 "../client_src/textures/img/sprites/magnum(5).bmp"
#define PISTOL_PL_6 "../client_src/textures/img/sprites/magnum(6).bmp"
#define PISTOL_PL_7 "../client_src/textures/img/sprites/magnum(7).bmp"
#define PISTOL_PL_8 "../client_src/textures/img/sprites/magnum(8).bmp"
#define PISTOL_PL_9 "../client_src/textures/img/sprites/magnum(9).bmp"
#define PISTOL_PL_10 "../client_src/textures/img/sprites/magnum(10).bmp"
#define PISTOL_PL_11 "../client_src/textures/img/sprites/magnum(11).bmp"
#define PISTOL_PL_12 "../client_src/textures/img/sprites/magnum(12).bmp"
#define PISTOL_PL_13 "../client_src/textures/img/sprites/magnum(13).bmp"
#define PISTOL_PL_14 "../client_src/textures/img/sprites/magnum(14).bmp"


TexturesContainer::TexturesContainer(SDL_Renderer *renderer,
                                     SDL_Surface *window_surface)
        : renderer(renderer), window_surface(window_surface){
    _loadStaticTextures();
    _loadDynamicTextures();
}

Texture* TexturesContainer::get(TextureID id) {
    return static_textures[id];
}

TexturesContainer::~TexturesContainer() {
    for (auto& tex:static_textures){
        delete tex.second;
        tex.second = nullptr;
    }
    for (auto& tex:dynamic_textures){
        delete tex.second;
        tex.second = nullptr;
    }
}

void TexturesContainer::_loadStaticTextures() {
    static_textures.emplace(None, nullptr);
    static_textures.emplace(Wall, new Texture(WALL_PATH, this->renderer));
    static_textures.emplace(Door, new Texture(DOOR_PATH, this->renderer));
    static_textures.emplace(InvertedDoor, new Texture(INVERTED_DOOR_PATH, this->renderer));
    static_textures.emplace(Barrel, new Texture(BARREL_PATH, this->renderer));
    static_textures.emplace(Guard_0, new Texture(GUARD_0_PATH, this->renderer));
    static_textures.emplace(Guard_1, new Texture(GUARD_1_PATH, this->renderer));
    static_textures.emplace(Guard_2, new Texture(GUARD_2_PATH, this->renderer));
    static_textures.emplace(Guard_3, new Texture(GUARD_3_PATH, this->renderer));
    static_textures.emplace(Guard_4, new Texture(GUARD_4_PATH, this->renderer));
    static_textures.emplace(Guard_5, new Texture(GUARD_5_PATH, this->renderer));
    static_textures.emplace(Guard_6, new Texture(GUARD_6_PATH, this->renderer));
    static_textures.emplace(Guard_7, new Texture(GUARD_7_PATH, this->renderer));
    static_textures.emplace(BJ_0, new Texture(BJ_0_PATH, this->renderer));
    static_textures.emplace(BJ_1, new Texture(BJ_1_PATH, this->renderer));
    static_textures.emplace(BJ_2, new Texture(BJ_2_PATH, this->renderer));
    static_textures.emplace(BJ_3, new Texture(BJ_3_PATH, this->renderer));
    static_textures.emplace(BJ_4, new Texture(BJ_4_PATH, this->renderer));
    static_textures.emplace(BJ_5, new Texture(BJ_5_PATH, this->renderer));
    static_textures.emplace(BJ_6, new Texture(BJ_6_PATH, this->renderer));
    static_textures.emplace(BJ_7, new Texture(BJ_7_PATH, this->renderer));
    static_textures.emplace(Knife_HUD, new Texture(KNIFE_HUD, this->renderer));
    static_textures.emplace(Pistol_HUD, new Texture(PISTOL_HUD, this->renderer));
    static_textures.emplace(MachineGun_HUD, new Texture(MACHINE_HUD, this->renderer));
    static_textures.emplace(ChainGun_HUD, new Texture(CHAIN_HUD, this->renderer));
    static_textures.emplace(RPG_HUD, new Texture(RPGHUD, this->renderer));
    static_textures.emplace(HasKey, new Texture(KEY_PATH, this->renderer));
    static_textures.emplace(HasNotKey, new Texture(NOT_KEY_PATH, this->renderer));
    static_textures.emplace(Background,new Texture(BACKGROUND,
                                                   this->renderer, this->window_surface));
    static_textures.emplace(HUD, new Texture(PL_HUD, this->renderer, this->window_surface));
}

void TexturesContainer::_loadDynamicTextures() {
    dynamic_textures.emplace(Pistol_Pl,new DynamicTexture(
            std::vector<std::string>{PISTOL_PL, PISTOL_PL_1, PISTOL_PL_2,
                                     PISTOL_PL_3, PISTOL_PL_4, PISTOL_PL_5,
                                     PISTOL_PL_6, PISTOL_PL_7, PISTOL_PL_8,
                                     PISTOL_PL_9, PISTOL_PL_10, PISTOL_PL_11,
                                     PISTOL_PL_12, PISTOL_PL_13, PISTOL_PL_14},
                                     this->renderer, this->window_surface, 2000));
}
