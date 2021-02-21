#include "TexturesContainer.h"
#include <SDL2/SDL_image.h>

#define WALKING_TIME 800

#define WALL_PATH "../client_src/textures/img/sprites/rocky.bmp"
#define AUTO_DOOR_PATH "../client_src/textures/img/sprites/door.bmp"
#define INVERTED_AUTO_DOOR_PATH "../client_src/textures/img/sprites/inv_door.bmp"
#define LOCKED_DOOR_PATH "../client_src/textures/img/sprites/locked_door.bmp"
#define INVERTED_LOCKED_DOOR_PATH "../client_src/textures/img/sprites/inv_locked_door.bmp"

#define BJ_0_PATH "../client_src/textures/img/miscellaneous/bj_0.bmp"
#define BJ_1_PATH "../client_src/textures/img/miscellaneous/bj_1.bmp"
#define BJ_2_PATH "../client_src/textures/img/miscellaneous/bj_2.bmp"
#define BJ_3_PATH "../client_src/textures/img/miscellaneous/bj_3.bmp"
#define BJ_4_PATH "../client_src/textures/img/miscellaneous/bj_4.bmp"
#define BJ_5_PATH "../client_src/textures/img/miscellaneous/bj_5.bmp"
#define BJ_6_PATH "../client_src/textures/img/miscellaneous/bj_6.bmp"
#define BJ_7_PATH "../client_src/textures/img/miscellaneous/bj_7.bmp"
#define KNIFE_HUD "../client_src/textures/img/miscellaneous/knife_HUD.bmp"
#define PISTOL_HUD "../client_src/textures/img/miscellaneous/pistol_HUD.bmp"
#define MACHINE_HUD "../client_src/textures/img/miscellaneous/machinegun_HUD.bmp"
#define CHAIN_HUD "../client_src/textures/img/miscellaneous/chaingun_HUD.bmp"
#define RPGHUD "../client_src/textures/img/miscellaneous/rpg_HUD.bmp"
#define KEY_PATH "../client_src/textures/img/miscellaneous/has_key.bmp"
#define NOT_KEY_PATH "../client_src/textures/img/miscellaneous/has_not_key.bmp"
#define BACKGROUND "../client_src/textures/img/miscellaneous/back.png"
#define PL_HUD "../client_src/textures/img/miscellaneous/HUD_1.png"

#define DOG_0_0 "../client_src/textures/img/sprites/Dog/dog_0_0.bmp"
#define DOG_0_1 "../client_src/textures/img/sprites/Dog/dog_0_1.bmp"
#define DOG_0_2 "../client_src/textures/img/sprites/Dog/dog_0_2.bmp"
#define DOG_0_3 "../client_src/textures/img/sprites/Dog/dog_0_3.bmp"
#define DOG_1_0 "../client_src/textures/img/sprites/Dog/dog_1_0.bmp"
#define DOG_1_1 "../client_src/textures/img/sprites/Dog/dog_1_1.bmp"
#define DOG_1_2 "../client_src/textures/img/sprites/Dog/dog_1_2.bmp"
#define DOG_1_3 "../client_src/textures/img/sprites/Dog/dog_1_3.bmp"
#define DOG_2_0 "../client_src/textures/img/sprites/Dog/dog_2_0.bmp"
#define DOG_2_1 "../client_src/textures/img/sprites/Dog/dog_2_1.bmp"
#define DOG_2_2 "../client_src/textures/img/sprites/Dog/dog_2_2.bmp"
#define DOG_2_3 "../client_src/textures/img/sprites/Dog/dog_2_3.bmp"
#define DOG_3_0 "../client_src/textures/img/sprites/Dog/dog_3_0.bmp"
#define DOG_3_1 "../client_src/textures/img/sprites/Dog/dog_3_1.bmp"
#define DOG_3_2 "../client_src/textures/img/sprites/Dog/dog_3_2.bmp"
#define DOG_3_3 "../client_src/textures/img/sprites/Dog/dog_3_3.bmp"
#define DOG_4_0 "../client_src/textures/img/sprites/Dog/dog_4_0.bmp"
#define DOG_4_1 "../client_src/textures/img/sprites/Dog/dog_4_1.bmp"
#define DOG_4_2 "../client_src/textures/img/sprites/Dog/dog_4_2.bmp"
#define DOG_4_3 "../client_src/textures/img/sprites/Dog/dog_4_3.bmp"
#define DOG_5_0 "../client_src/textures/img/sprites/Dog/dog_5_0.bmp"
#define DOG_5_1 "../client_src/textures/img/sprites/Dog/dog_5_1.bmp"
#define DOG_5_2 "../client_src/textures/img/sprites/Dog/dog_5_2.bmp"
#define DOG_5_3 "../client_src/textures/img/sprites/Dog/dog_5_3.bmp"
#define DOG_6_0 "../client_src/textures/img/sprites/Dog/dog_6_0.bmp"
#define DOG_6_1 "../client_src/textures/img/sprites/Dog/dog_6_1.bmp"
#define DOG_6_2 "../client_src/textures/img/sprites/Dog/dog_6_2.bmp"
#define DOG_6_3 "../client_src/textures/img/sprites/Dog/dog_6_3.bmp"
#define DOG_7_0 "../client_src/textures/img/sprites/Dog/dog_7_0.bmp"
#define DOG_7_1 "../client_src/textures/img/sprites/Dog/dog_7_1.bmp"
#define DOG_7_2 "../client_src/textures/img/sprites/Dog/dog_7_2.bmp"
#define DOG_7_3 "../client_src/textures/img/sprites/Dog/dog_7_3.bmp"
#define DOG_KILL_0 "../client_src/textures/img/sprites/Dog/dog_kill_0.bmp"
#define DOG_KILL_1 "../client_src/textures/img/sprites/Dog/dog_kill_1.bmp"
#define DOG_KILL_2 "../client_src/textures/img/sprites/Dog/dog_kill_2.bmp"
#define DOG_KILL_3 "../client_src/textures/img/sprites/Dog/dog_kill_3.bmp"
#define DOG_ATT_0 "../client_src/textures/img/sprites/Dog/dog_attack_0.bmp"
#define DOG_ATT_1 "../client_src/textures/img/sprites/Dog/dog_attack_1.bmp"
#define DOG_ATT_2 "../client_src/textures/img/sprites/Dog/dog_attack_2.bmp"

#define GUARD_0_0 "../client_src/textures/img/sprites/Guard/guard_0_0.BMP"
#define GUARD_0_1 "../client_src/textures/img/sprites/Guard/guard_0_1.BMP"
#define GUARD_0_2 "../client_src/textures/img/sprites/Guard/guard_0_2.BMP"
#define GUARD_0_3 "../client_src/textures/img/sprites/Guard/guard_0_3.BMP"
#define GUARD_0_4 "../client_src/textures/img/sprites/Guard/guard_0_4.BMP"
#define GUARD_1_0 "../client_src/textures/img/sprites/Guard/guard_1_0.BMP"
#define GUARD_1_1 "../client_src/textures/img/sprites/Guard/guard_1_1.BMP"
#define GUARD_1_2 "../client_src/textures/img/sprites/Guard/guard_1_2.BMP"
#define GUARD_1_3 "../client_src/textures/img/sprites/Guard/guard_1_3.BMP"
#define GUARD_1_4 "../client_src/textures/img/sprites/Guard/guard_1_4.BMP"
#define GUARD_2_0 "../client_src/textures/img/sprites/Guard/guard_2_0.BMP"
#define GUARD_2_1 "../client_src/textures/img/sprites/Guard/guard_2_1.BMP"
#define GUARD_2_2 "../client_src/textures/img/sprites/Guard/guard_2_2.BMP"
#define GUARD_2_3 "../client_src/textures/img/sprites/Guard/guard_2_3.BMP"
#define GUARD_2_4 "../client_src/textures/img/sprites/Guard/guard_2_4.BMP"
#define GUARD_3_0 "../client_src/textures/img/sprites/Guard/guard_3_0.BMP"
#define GUARD_3_1 "../client_src/textures/img/sprites/Guard/guard_3_1.BMP"
#define GUARD_3_2 "../client_src/textures/img/sprites/Guard/guard_3_2.BMP"
#define GUARD_3_3 "../client_src/textures/img/sprites/Guard/guard_3_3.BMP"
#define GUARD_3_4 "../client_src/textures/img/sprites/Guard/guard_3_4.BMP"
#define GUARD_4_0 "../client_src/textures/img/sprites/Guard/guard_4_0.BMP"
#define GUARD_4_1 "../client_src/textures/img/sprites/Guard/guard_4_1.BMP"
#define GUARD_4_2 "../client_src/textures/img/sprites/Guard/guard_4_2.BMP"
#define GUARD_4_3 "../client_src/textures/img/sprites/Guard/guard_4_3.BMP"
#define GUARD_4_4 "../client_src/textures/img/sprites/Guard/guard_4_4.BMP"
#define GUARD_5_0 "../client_src/textures/img/sprites/Guard/guard_5_0.BMP"
#define GUARD_5_1 "../client_src/textures/img/sprites/Guard/guard_5_1.BMP"
#define GUARD_5_2 "../client_src/textures/img/sprites/Guard/guard_5_2.BMP"
#define GUARD_5_3 "../client_src/textures/img/sprites/Guard/guard_5_3.BMP"
#define GUARD_5_4 "../client_src/textures/img/sprites/Guard/guard_5_4.BMP"
#define GUARD_6_0 "../client_src/textures/img/sprites/Guard/guard_6_0.BMP"
#define GUARD_6_1 "../client_src/textures/img/sprites/Guard/guard_6_1.BMP"
#define GUARD_6_2 "../client_src/textures/img/sprites/Guard/guard_6_2.BMP"
#define GUARD_6_3 "../client_src/textures/img/sprites/Guard/guard_6_3.BMP"
#define GUARD_6_4 "../client_src/textures/img/sprites/Guard/guard_6_4.BMP"
#define GUARD_7_0 "../client_src/textures/img/sprites/Guard/guard_7_0.BMP"
#define GUARD_7_1 "../client_src/textures/img/sprites/Guard/guard_7_1.BMP"
#define GUARD_7_2 "../client_src/textures/img/sprites/Guard/guard_7_2.BMP"
#define GUARD_7_3 "../client_src/textures/img/sprites/Guard/guard_7_3.BMP"
#define GUARD_7_4 "../client_src/textures/img/sprites/Guard/guard_7_4.BMP"
#define GUARD_KILL_0 "../client_src/textures/img/sprites/Guard/guard_kill_0.BMP"
#define GUARD_KILL_1 "../client_src/textures/img/sprites/Guard/guard_kill_1.BMP"
#define GUARD_KILL_2 "../client_src/textures/img/sprites/Guard/guard_kill_2.BMP"
#define GUARD_KILL_3 "../client_src/textures/img/sprites/Guard/guard_kill_3.BMP"
#define GUARD_KILL_4 "../client_src/textures/img/sprites/Guard/guard_kill_4.BMP"
#define GUARD_KILL_5 "../client_src/textures/img/sprites/Guard/guard_kill_5.BMP"
#define GUARD_ATT_0 "../client_src/textures/img/sprites/Guard/guard_attack_0.BMP"
#define GUARD_ATT_1 "../client_src/textures/img/sprites/Guard/guard_attack_1.BMP"
#define GUARD_ATT_2 "../client_src/textures/img/sprites/Guard/guard_attack_2.BMP"

#define SS_0_0 "../client_src/textures/img/sprites/SS/ss_0_0.BMP"
#define SS_0_1 "../client_src/textures/img/sprites/SS/ss_0_1.BMP"
#define SS_0_2 "../client_src/textures/img/sprites/SS/ss_0_2.BMP"
#define SS_0_3 "../client_src/textures/img/sprites/SS/ss_0_3.BMP"
#define SS_0_4 "../client_src/textures/img/sprites/SS/ss_0_4.BMP"
#define SS_1_0 "../client_src/textures/img/sprites/SS/ss_1_0.BMP"
#define SS_1_1 "../client_src/textures/img/sprites/SS/ss_1_1.BMP"
#define SS_1_2 "../client_src/textures/img/sprites/SS/ss_1_2.BMP"
#define SS_1_3 "../client_src/textures/img/sprites/SS/ss_1_3.BMP"
#define SS_1_4 "../client_src/textures/img/sprites/SS/ss_1_4.BMP"
#define SS_2_0 "../client_src/textures/img/sprites/SS/ss_2_0.BMP"
#define SS_2_1 "../client_src/textures/img/sprites/SS/ss_2_1.BMP"
#define SS_2_2 "../client_src/textures/img/sprites/SS/ss_2_2.BMP"
#define SS_2_3 "../client_src/textures/img/sprites/SS/ss_2_3.BMP"
#define SS_2_4 "../client_src/textures/img/sprites/SS/ss_2_4.BMP"
#define SS_3_0 "../client_src/textures/img/sprites/SS/ss_3_0.BMP"
#define SS_3_1 "../client_src/textures/img/sprites/SS/ss_3_1.BMP"
#define SS_3_2 "../client_src/textures/img/sprites/SS/ss_3_2.BMP"
#define SS_3_3 "../client_src/textures/img/sprites/SS/ss_3_3.BMP"
#define SS_3_4 "../client_src/textures/img/sprites/SS/ss_3_4.BMP"
#define SS_4_0 "../client_src/textures/img/sprites/SS/ss_4_0.BMP"
#define SS_4_1 "../client_src/textures/img/sprites/SS/ss_4_1.BMP"
#define SS_4_2 "../client_src/textures/img/sprites/SS/ss_4_2.BMP"
#define SS_4_3 "../client_src/textures/img/sprites/SS/ss_4_3.BMP"
#define SS_4_4 "../client_src/textures/img/sprites/SS/ss_4_4.BMP"
#define SS_5_0 "../client_src/textures/img/sprites/SS/ss_5_0.BMP"
#define SS_5_1 "../client_src/textures/img/sprites/SS/ss_5_1.BMP"
#define SS_5_2 "../client_src/textures/img/sprites/SS/ss_5_2.BMP"
#define SS_5_3 "../client_src/textures/img/sprites/SS/ss_5_3.BMP"
#define SS_5_4 "../client_src/textures/img/sprites/SS/ss_5_4.BMP"
#define SS_6_0 "../client_src/textures/img/sprites/SS/ss_6_0.BMP"
#define SS_6_1 "../client_src/textures/img/sprites/SS/ss_6_1.BMP"
#define SS_6_2 "../client_src/textures/img/sprites/SS/ss_6_2.BMP"
#define SS_6_3 "../client_src/textures/img/sprites/SS/ss_6_3.BMP"
#define SS_6_4 "../client_src/textures/img/sprites/SS/ss_6_4.BMP"
#define SS_7_0 "../client_src/textures/img/sprites/SS/ss_7_0.BMP"
#define SS_7_1 "../client_src/textures/img/sprites/SS/ss_7_1.BMP"
#define SS_7_2 "../client_src/textures/img/sprites/SS/ss_7_2.BMP"
#define SS_7_3 "../client_src/textures/img/sprites/SS/ss_7_3.BMP"
#define SS_7_4 "../client_src/textures/img/sprites/SS/ss_7_4.BMP"
#define SS_KILL_0 "../client_src/textures/img/sprites/SS/ss_kill_0.BMP"
#define SS_KILL_1 "../client_src/textures/img/sprites/SS/ss_kill_1.BMP"
#define SS_KILL_2 "../client_src/textures/img/sprites/SS/ss_kill_2.BMP"
#define SS_KILL_3 "../client_src/textures/img/sprites/SS/ss_kill_3.BMP"
#define SS_KILL_4 "../client_src/textures/img/sprites/SS/ss_kill_4.BMP"
#define SS_ATT_0 "../client_src/textures/img/sprites/SS/ss_attack_0.BMP"
#define SS_ATT_1 "../client_src/textures/img/sprites/SS/ss_attack_1.BMP"
#define SS_ATT_2 "../client_src/textures/img/sprites/SS/ss_attack_2.BMP"

#define OFFICER_0_0 "../client_src/textures/img/sprites/Officer/officer_0_0.BMP"
#define OFFICER_0_1 "../client_src/textures/img/sprites/Officer/officer_0_1.BMP"
#define OFFICER_0_2 "../client_src/textures/img/sprites/Officer/officer_0_2.BMP"
#define OFFICER_0_3 "../client_src/textures/img/sprites/Officer/officer_0_3.BMP"
#define OFFICER_0_4 "../client_src/textures/img/sprites/Officer/officer_0_4.BMP"
#define OFFICER_1_0 "../client_src/textures/img/sprites/Officer/officer_1_0.BMP"
#define OFFICER_1_1 "../client_src/textures/img/sprites/Officer/officer_1_1.BMP"
#define OFFICER_1_2 "../client_src/textures/img/sprites/Officer/officer_1_2.BMP"
#define OFFICER_1_3 "../client_src/textures/img/sprites/Officer/officer_1_3.BMP"
#define OFFICER_1_4 "../client_src/textures/img/sprites/Officer/officer_1_4.BMP"
#define OFFICER_2_0 "../client_src/textures/img/sprites/Officer/officer_2_0.BMP"
#define OFFICER_2_1 "../client_src/textures/img/sprites/Officer/officer_2_1.BMP"
#define OFFICER_2_2 "../client_src/textures/img/sprites/Officer/officer_2_2.BMP"
#define OFFICER_2_3 "../client_src/textures/img/sprites/Officer/officer_2_3.BMP"
#define OFFICER_2_4 "../client_src/textures/img/sprites/Officer/officer_2_4.BMP"
#define OFFICER_3_0 "../client_src/textures/img/sprites/Officer/officer_3_0.BMP"
#define OFFICER_3_1 "../client_src/textures/img/sprites/Officer/officer_3_1.BMP"
#define OFFICER_3_2 "../client_src/textures/img/sprites/Officer/officer_3_2.BMP"
#define OFFICER_3_3 "../client_src/textures/img/sprites/Officer/officer_3_3.BMP"
#define OFFICER_3_4 "../client_src/textures/img/sprites/Officer/officer_3_4.BMP"
#define OFFICER_4_0 "../client_src/textures/img/sprites/Officer/officer_4_0.BMP"
#define OFFICER_4_1 "../client_src/textures/img/sprites/Officer/officer_4_1.BMP"
#define OFFICER_4_2 "../client_src/textures/img/sprites/Officer/officer_4_2.BMP"
#define OFFICER_4_3 "../client_src/textures/img/sprites/Officer/officer_4_3.BMP"
#define OFFICER_4_4 "../client_src/textures/img/sprites/Officer/officer_4_4.BMP"
#define OFFICER_5_0 "../client_src/textures/img/sprites/Officer/officer_5_0.BMP"
#define OFFICER_5_1 "../client_src/textures/img/sprites/Officer/officer_5_1.BMP"
#define OFFICER_5_2 "../client_src/textures/img/sprites/Officer/officer_5_2.BMP"
#define OFFICER_5_3 "../client_src/textures/img/sprites/Officer/officer_5_3.BMP"
#define OFFICER_5_4 "../client_src/textures/img/sprites/Officer/officer_5_4.BMP"
#define OFFICER_6_0 "../client_src/textures/img/sprites/Officer/officer_6_0.BMP"
#define OFFICER_6_1 "../client_src/textures/img/sprites/Officer/officer_6_1.BMP"
#define OFFICER_6_2 "../client_src/textures/img/sprites/Officer/officer_6_2.BMP"
#define OFFICER_6_3 "../client_src/textures/img/sprites/Officer/officer_6_3.BMP"
#define OFFICER_6_4 "../client_src/textures/img/sprites/Officer/officer_6_4.BMP"
#define OFFICER_7_0 "../client_src/textures/img/sprites/Officer/officer_7_0.BMP"
#define OFFICER_7_1 "../client_src/textures/img/sprites/Officer/officer_7_1.BMP"
#define OFFICER_7_2 "../client_src/textures/img/sprites/Officer/officer_7_2.BMP"
#define OFFICER_7_3 "../client_src/textures/img/sprites/Officer/officer_7_3.BMP"
#define OFFICER_7_4 "../client_src/textures/img/sprites/Officer/officer_7_4.BMP"
#define OFFICER_KILL_0 "../client_src/textures/img/sprites/Officer/officer_kill_0.BMP"
#define OFFICER_KILL_1 "../client_src/textures/img/sprites/Officer/officer_kill_1.BMP"
#define OFFICER_KILL_2 "../client_src/textures/img/sprites/Officer/officer_kill_2.BMP"
#define OFFICER_KILL_3 "../client_src/textures/img/sprites/Officer/officer_kill_3.BMP"
#define OFFICER_KILL_4 "../client_src/textures/img/sprites/Officer/officer_kill_4.BMP"
#define OFFICER_ATT_0 "../client_src/textures/img/sprites/Officer/officer_attack_0.BMP"
#define OFFICER_ATT_1 "../client_src/textures/img/sprites/Officer/officer_attack_1.BMP"
#define OFFICER_ATT_2 "../client_src/textures/img/sprites/Officer/officer_attack_2.BMP"

#define MUTANT_0_0 "../client_src/textures/img/sprites/Mutant/mutant_0_0.BMP"
#define MUTANT_0_1 "../client_src/textures/img/sprites/Mutant/mutant_0_1.BMP"
#define MUTANT_0_2 "../client_src/textures/img/sprites/Mutant/mutant_0_2.BMP"
#define MUTANT_0_3 "../client_src/textures/img/sprites/Mutant/mutant_0_3.BMP"
#define MUTANT_0_4 "../client_src/textures/img/sprites/Mutant/mutant_0_4.BMP"
#define MUTANT_1_0 "../client_src/textures/img/sprites/Mutant/mutant_1_0.BMP"
#define MUTANT_1_1 "../client_src/textures/img/sprites/Mutant/mutant_1_1.BMP"
#define MUTANT_1_2 "../client_src/textures/img/sprites/Mutant/mutant_1_2.BMP"
#define MUTANT_1_3 "../client_src/textures/img/sprites/Mutant/mutant_1_3.BMP"
#define MUTANT_1_4 "../client_src/textures/img/sprites/Mutant/mutant_1_4.BMP"
#define MUTANT_2_0 "../client_src/textures/img/sprites/Mutant/mutant_2_0.BMP"
#define MUTANT_2_1 "../client_src/textures/img/sprites/Mutant/mutant_2_1.BMP"
#define MUTANT_2_2 "../client_src/textures/img/sprites/Mutant/mutant_2_2.BMP"
#define MUTANT_2_3 "../client_src/textures/img/sprites/Mutant/mutant_2_3.BMP"
#define MUTANT_2_4 "../client_src/textures/img/sprites/Mutant/mutant_2_4.BMP"
#define MUTANT_3_0 "../client_src/textures/img/sprites/Mutant/mutant_3_0.BMP"
#define MUTANT_3_1 "../client_src/textures/img/sprites/Mutant/mutant_3_1.BMP"
#define MUTANT_3_2 "../client_src/textures/img/sprites/Mutant/mutant_3_2.BMP"
#define MUTANT_3_3 "../client_src/textures/img/sprites/Mutant/mutant_3_3.BMP"
#define MUTANT_3_4 "../client_src/textures/img/sprites/Mutant/mutant_3_4.BMP"
#define MUTANT_4_0 "../client_src/textures/img/sprites/Mutant/mutant_4_0.BMP"
#define MUTANT_4_1 "../client_src/textures/img/sprites/Mutant/mutant_4_1.BMP"
#define MUTANT_4_2 "../client_src/textures/img/sprites/Mutant/mutant_4_2.BMP"
#define MUTANT_4_3 "../client_src/textures/img/sprites/Mutant/mutant_4_3.BMP"
#define MUTANT_4_4 "../client_src/textures/img/sprites/Mutant/mutant_4_4.BMP"
#define MUTANT_5_0 "../client_src/textures/img/sprites/Mutant/mutant_5_0.BMP"
#define MUTANT_5_1 "../client_src/textures/img/sprites/Mutant/mutant_5_1.BMP"
#define MUTANT_5_2 "../client_src/textures/img/sprites/Mutant/mutant_5_2.BMP"
#define MUTANT_5_3 "../client_src/textures/img/sprites/Mutant/mutant_5_3.BMP"
#define MUTANT_5_4 "../client_src/textures/img/sprites/Mutant/mutant_5_4.BMP"
#define MUTANT_6_0 "../client_src/textures/img/sprites/Mutant/mutant_6_0.BMP"
#define MUTANT_6_1 "../client_src/textures/img/sprites/Mutant/mutant_6_1.BMP"
#define MUTANT_6_2 "../client_src/textures/img/sprites/Mutant/mutant_6_2.BMP"
#define MUTANT_6_3 "../client_src/textures/img/sprites/Mutant/mutant_6_3.BMP"
#define MUTANT_6_4 "../client_src/textures/img/sprites/Mutant/mutant_6_4.BMP"
#define MUTANT_7_0 "../client_src/textures/img/sprites/Mutant/mutant_7_0.BMP"
#define MUTANT_7_1 "../client_src/textures/img/sprites/Mutant/mutant_7_1.BMP"
#define MUTANT_7_2 "../client_src/textures/img/sprites/Mutant/mutant_7_2.BMP"
#define MUTANT_7_3 "../client_src/textures/img/sprites/Mutant/mutant_7_3.BMP"
#define MUTANT_7_4 "../client_src/textures/img/sprites/Mutant/mutant_7_4.BMP"
#define MUTANT_KILL_0 "../client_src/textures/img/sprites/Mutant/mutant_kill_0.BMP"
#define MUTANT_KILL_1 "../client_src/textures/img/sprites/Mutant/mutant_kill_1.BMP"
#define MUTANT_KILL_2 "../client_src/textures/img/sprites/Mutant/mutant_kill_2.BMP"
#define MUTANT_KILL_3 "../client_src/textures/img/sprites/Mutant/mutant_kill_3.BMP"
#define MUTANT_KILL_4 "../client_src/textures/img/sprites/Mutant/mutant_kill_4.BMP"
#define MUTANT_KILL_5 "../client_src/textures/img/sprites/Mutant/mutant_kill_5.BMP"
#define MUTANT_ATT_0 "../client_src/textures/img/sprites/Mutant/mutant_attack_0.BMP"
#define MUTANT_ATT_1 "../client_src/textures/img/sprites/Mutant/mutant_attack_1.BMP"
#define MUTANT_ATT_2 "../client_src/textures/img/sprites/Mutant/mutant_attack_2.BMP"
#define MUTANT_ATT_3 "../client_src/textures/img/sprites/Mutant/mutant_attack_3.BMP"

#define KNIFE_PL "../client_src/textures/img/sprites/knife_0.bmp"
#define KNIFE_PL_1 "../client_src/textures/img/sprites/knife_1.bmp"
#define KNIFE_PL_2 "../client_src/textures/img/sprites/knife_2.bmp"
#define KNIFE_PL_3 "../client_src/textures/img/sprites/knife_3.bmp"
#define PISTOL_PL "../client_src/textures/img/sprites/magnum_0.bmp"
#define PISTOL_PL_1 "../client_src/textures/img/sprites/magnum_1.bmp"
#define PISTOL_PL_2 "../client_src/textures/img/sprites/magnum_2.bmp"
#define PISTOL_PL_3 "../client_src/textures/img/sprites/magnum_3.bmp"
#define PISTOL_PL_4 "../client_src/textures/img/sprites/magnum_4.bmp"
#define PISTOL_PL_5 "../client_src/textures/img/sprites/magnum_5.bmp"
#define PISTOL_PL_6 "../client_src/textures/img/sprites/magnum_6.bmp"
#define PISTOL_PL_7 "../client_src/textures/img/sprites/magnum_7.bmp"
#define PISTOL_PL_8 "../client_src/textures/img/sprites/magnum_8.bmp"
#define PISTOL_PL_9 "../client_src/textures/img/sprites/magnum_9.bmp"
#define PISTOL_PL_10 "../client_src/textures/img/sprites/magnum_10.bmp"
#define PISTOL_PL_11 "../client_src/textures/img/sprites/magnum_11.bmp"
#define PISTOL_PL_12 "../client_src/textures/img/sprites/magnum_12.bmp"
#define PISTOL_PL_13 "../client_src/textures/img/sprites/magnum_13.bmp"
#define PISTOL_PL_14 "../client_src/textures/img/sprites/magnum_14.bmp"
#define MACHINEGUN_PL "../client_src/textures/img/sprites/machinegun_0.bmp"
#define MACHINEGUN_PL_1 "../client_src/textures/img/sprites/machinegun_1.bmp"
#define MACHINEGUN_PL_2 "../client_src/textures/img/sprites/machinegun_2.bmp"
#define CHAINGUN_PL "../client_src/textures/img/sprites/chaingun_0.bmp"
#define CHAINGUN_PL_1 "../client_src/textures/img/sprites/chaingun_1.bmp"
#define CHAINGUN_PL_2 "../client_src/textures/img/sprites/chaingun_2.bmp"
#define RPG_PL "../client_src/textures/img/sprites/rpg_0.bmp"
#define RPG_PL_1 "../client_src/textures/img/sprites/rpg_1.bmp"
#define RPG_PL_2 "../client_src/textures/img/sprites/rpg_2.bmp"
#define RPG_PL_3 "../client_src/textures/img/sprites/rpg_3.bmp"
#define MISSILE_0 "../client_src/textures/img/sprites/missile_0.bmp"
#define MISSILE_1 "../client_src/textures/img/sprites/missile_1.bmp"
#define MISSILE_2 "../client_src/textures/img/sprites/missile_2.bmp"
#define MISSILE_3 "../client_src/textures/img/sprites/missile_3.bmp"
#define MISSILE_4 "../client_src/textures/img/sprites/missile_4.bmp"
#define MISSILE_5 "../client_src/textures/img/sprites/missile_5.bmp"
#define MISSILE_6 "../client_src/textures/img/sprites/missile_6.bmp"
#define MISSILE_7 "../client_src/textures/img/sprites/missile_7.bmp"


#define KNIFE_ITEM "../client_src/textures/img/sprites/knife_item.bmp"
#define PISTOL_ITEM "../client_src/textures/img/sprites/pistol_item.bmp"
#define MACHINEGUN_ITEM "../client_src/textures/img/sprites/machinegun_item.bmp"
#define CHAINGUN_ITEM "../client_src/textures/img/sprites/chaingun_item.bmp"
#define RPG_ITEM "../client_src/textures/img/sprites/rpg_item.bmp"
#define BULLETS_ITEM "../client_src/textures/img/sprites/bullets.bmp"
#define BLOOD_ITEM_0 "../client_src/textures/img/sprites/blood_0.bmp"
#define BLOOD_ITEM_1 "../client_src/textures/img/sprites/blood_1.bmp"
#define CROSS_ITEM "../client_src/textures/img/sprites/cross.bmp"
#define CROWN_ITEM "../client_src/textures/img/sprites/crown.bmp"
#define CUP_ITEM "../client_src/textures/img/sprites/cup.bmp"
#define JEWELRY_ITEM "../client_src/textures/img/sprites/jewelry.bmp"
#define FOOD_ITEM_0 "../client_src/textures/img/sprites/food_0.bmp"
#define FOOD_ITEM_1 "../client_src/textures/img/sprites/food_1.bmp"
#define HEALTH_KIT_ITEM "../client_src/textures/img/sprites/health_kit.bmp"
#define KEY_ITEM "../client_src/textures/img/sprites/key.bmp"

TexturesContainer::TexturesContainer(SDL_Renderer *renderer,
                                     SDL_Surface *window_surface)
        : renderer(renderer), window_surface(window_surface){
    _loadStaticTextures();
    _loadTextureSets();
}

Texture* TexturesContainer::getStatic(TextureID id) {
    return static_textures[id];
}

TextureSet *TexturesContainer::getDynamic(TextureID id) {
    return dynamic_textures[id];
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
    static_textures.emplace(AutoDoor, new Texture(AUTO_DOOR_PATH, this->renderer));
    static_textures.emplace(InvertedAutoDoor, new Texture(INVERTED_AUTO_DOOR_PATH, this->renderer));
    static_textures.emplace(LockedDoor, new Texture(LOCKED_DOOR_PATH, this->renderer));
    static_textures.emplace(InvertedLockedDoor, new Texture(INVERTED_LOCKED_DOOR_PATH, this->renderer));

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
    static_textures.emplace(Background,new Texture(BACKGROUND, this->renderer, this->window_surface));
    static_textures.emplace(HUD, new Texture(PL_HUD, this->renderer, this->window_surface));

//    static_textures.emplace(Missile_0, new Texture(MISSILE_0, this->renderer));
//    static_textures.emplace(Missile_1, new Texture(MISSILE_1, this->renderer));
//    static_textures.emplace(Missile_2, new Texture(MISSILE_2, this->renderer));
//    static_textures.emplace(Missile_3, new Texture(MISSILE_3, this->renderer));
//    static_textures.emplace(Missile_4, new Texture(MISSILE_4, this->renderer));
//    static_textures.emplace(Missile_5, new Texture(MISSILE_5, this->renderer));
//    static_textures.emplace(Missile_6, new Texture(MISSILE_6, this->renderer));
//    static_textures.emplace(Missile_7, new Texture(MISSILE_7, this->renderer));

    static_textures.emplace(KnifeItem, new Texture(KNIFE_ITEM, this->renderer));
    static_textures.emplace(PistolItem, new Texture(PISTOL_ITEM, this->renderer));
    static_textures.emplace(MachinegunItem, new Texture(MACHINEGUN_ITEM, this->renderer));
    static_textures.emplace(ChaingunItem, new Texture(CHAINGUN_ITEM, this->renderer));
    static_textures.emplace(RPGItem, new Texture(RPG_ITEM, this->renderer));
    static_textures.emplace(Bullets, new Texture(BULLETS_ITEM, this->renderer));
    static_textures.emplace(Blood_0, new Texture(BLOOD_ITEM_0, this->renderer));
    static_textures.emplace(Blood_1, new Texture(BLOOD_ITEM_1, this->renderer));
    static_textures.emplace(Food_0, new Texture(FOOD_ITEM_0, this->renderer));
    static_textures.emplace(Food_1, new Texture(FOOD_ITEM_1, this->renderer));
    static_textures.emplace(KeyItem_, new Texture(KEY_ITEM, this->renderer));
    static_textures.emplace(Cup, new Texture(CUP_ITEM, this->renderer));
    static_textures.emplace(Crown, new Texture(CROWN_ITEM, this->renderer));
    static_textures.emplace(Cross, new Texture(CROSS_ITEM, this->renderer));
    static_textures.emplace(Jewelry, new Texture(JEWELRY_ITEM, this->renderer));
    static_textures.emplace(HealthKit, new Texture(HEALTH_KIT_ITEM, this->renderer));

}

void TexturesContainer::_loadTextureSets() {
    dynamic_textures.emplace(Knife_Pl, new TextureSet(
            std::vector<std::string>{KNIFE_PL, KNIFE_PL_1, KNIFE_PL_2,
                                     KNIFE_PL_3},
            this->renderer, this->window_surface, 200));

    dynamic_textures.emplace(Pistol_Pl, new TextureSet(
            std::vector<std::string>{PISTOL_PL, PISTOL_PL_1, PISTOL_PL_2,
                                     PISTOL_PL_3, PISTOL_PL_4,
                                     PISTOL_PL_5, PISTOL_PL_6, PISTOL_PL_7,
                                     PISTOL_PL_8, PISTOL_PL_9,
                                     PISTOL_PL_10, PISTOL_PL_11, PISTOL_PL_12,
                                     PISTOL_PL_13, PISTOL_PL_14},
            this->renderer, this->window_surface, 250));

    dynamic_textures.emplace(MachineGun_Pl, new TextureSet(
            std::vector<std::string>{MACHINEGUN_PL, MACHINEGUN_PL_1, MACHINEGUN_PL_2},
            this->renderer, this->window_surface, 100));

    dynamic_textures.emplace(ChainGun_Pl, new TextureSet(
            std::vector<std::string>{CHAINGUN_PL, CHAINGUN_PL_1, CHAINGUN_PL_2},
            this->renderer, this->window_surface, 250));

    dynamic_textures.emplace(RPG_Pl, new TextureSet(
            std::vector<std::string>{RPG_PL, RPG_PL_1, RPG_PL_2, RPG_PL_3},
            this->renderer, this->window_surface, 250));

    dynamic_textures.emplace(Dog_0, new TextureSet(
            std::vector<std::string>{DOG_0_0, DOG_0_1, DOG_0_2, DOG_0_3},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Dog_1, new TextureSet(
            std::vector<std::string>{DOG_1_0, DOG_1_1, DOG_1_2, DOG_1_3},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Dog_2, new TextureSet(
            std::vector<std::string>{DOG_2_0, DOG_2_1, DOG_2_2, DOG_2_3},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Dog_3, new TextureSet(
            std::vector<std::string>{DOG_3_0, DOG_3_1, DOG_3_2, DOG_3_3},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Dog_4, new TextureSet(
            std::vector<std::string>{DOG_4_0, DOG_4_1, DOG_4_2, DOG_4_3},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Dog_5, new TextureSet(
            std::vector<std::string>{DOG_5_0, DOG_5_1, DOG_5_2, DOG_5_3},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Dog_6, new TextureSet(
            std::vector<std::string>{DOG_6_0, DOG_6_1, DOG_6_2, DOG_6_3},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Dog_7, new TextureSet(
            std::vector<std::string>{DOG_7_0, DOG_7_1, DOG_7_2, DOG_7_3},
            this->renderer, this->window_surface, WALKING_TIME));

    dynamic_textures.emplace(Guard_0, new TextureSet(
            std::vector<std::string>{GUARD_0_0, GUARD_0_1, GUARD_0_2, GUARD_0_3, GUARD_0_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Guard_1, new TextureSet(
            std::vector<std::string>{GUARD_1_0, GUARD_1_1, GUARD_1_2, GUARD_1_3, GUARD_1_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Guard_2, new TextureSet(
            std::vector<std::string>{GUARD_2_0, GUARD_2_1, GUARD_2_2, GUARD_2_3, GUARD_2_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Guard_3, new TextureSet(
            std::vector<std::string>{GUARD_3_0, GUARD_3_1, GUARD_3_2, GUARD_3_3, GUARD_3_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Guard_4, new TextureSet(
            std::vector<std::string>{GUARD_4_0, GUARD_4_1, GUARD_4_2, GUARD_4_3, GUARD_4_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Guard_5, new TextureSet(
            std::vector<std::string>{GUARD_5_0, GUARD_5_1, GUARD_5_2, GUARD_5_3, GUARD_5_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Guard_6, new TextureSet(
            std::vector<std::string>{GUARD_6_0, GUARD_6_1, GUARD_6_2, GUARD_6_3, GUARD_6_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Guard_7, new TextureSet(
            std::vector<std::string>{GUARD_7_0, GUARD_7_1, GUARD_7_2, GUARD_7_3, GUARD_7_4},
            this->renderer, this->window_surface, WALKING_TIME));

    dynamic_textures.emplace(SS_0, new TextureSet(
            std::vector<std::string>{SS_0_0, SS_0_1, SS_0_2, SS_0_3, SS_0_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(SS_1, new TextureSet(
            std::vector<std::string>{SS_1_0, SS_1_1, SS_1_2, SS_1_3, SS_1_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(SS_2, new TextureSet(
            std::vector<std::string>{SS_2_0, SS_2_1, SS_2_2, SS_2_3, SS_2_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(SS_3, new TextureSet(
            std::vector<std::string>{SS_3_0, SS_3_1, SS_3_2, SS_3_3, SS_3_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(SS_4, new TextureSet(
            std::vector<std::string>{SS_4_0, SS_4_1, SS_4_2, SS_4_3, SS_4_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(SS_5, new TextureSet(
            std::vector<std::string>{SS_5_0, SS_5_1, SS_5_2, SS_5_3, SS_5_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(SS_6, new TextureSet(
            std::vector<std::string>{SS_6_0, SS_6_1, SS_6_2, SS_6_3, SS_6_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(SS_7, new TextureSet(
            std::vector<std::string>{SS_7_0, SS_7_1, SS_7_2, SS_7_3, SS_7_4},
            this->renderer, this->window_surface, WALKING_TIME));

    dynamic_textures.emplace(Officer_0, new TextureSet(
            std::vector<std::string>{OFFICER_0_0, OFFICER_0_1, OFFICER_0_2, OFFICER_0_3, OFFICER_0_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Officer_1, new TextureSet(
            std::vector<std::string>{OFFICER_1_0, OFFICER_1_1, OFFICER_1_2, OFFICER_1_3, OFFICER_1_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Officer_2, new TextureSet(
            std::vector<std::string>{OFFICER_2_0, OFFICER_2_1, OFFICER_2_2, OFFICER_2_3, OFFICER_2_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Officer_3, new TextureSet(
            std::vector<std::string>{OFFICER_3_0, OFFICER_3_1, OFFICER_3_2, OFFICER_3_3, OFFICER_3_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Officer_4, new TextureSet(
            std::vector<std::string>{OFFICER_4_0, OFFICER_4_1, OFFICER_4_2, OFFICER_4_3, OFFICER_4_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Officer_5, new TextureSet(
            std::vector<std::string>{OFFICER_5_0, OFFICER_5_1, OFFICER_5_2, OFFICER_5_3, OFFICER_5_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Officer_6, new TextureSet(
            std::vector<std::string>{OFFICER_6_0, OFFICER_6_1, OFFICER_6_2, OFFICER_6_3, OFFICER_6_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Officer_7, new TextureSet(
            std::vector<std::string>{OFFICER_7_0, OFFICER_7_1, OFFICER_7_2, OFFICER_7_3, OFFICER_7_4},
            this->renderer, this->window_surface, WALKING_TIME));

    dynamic_textures.emplace(Mutant_0, new TextureSet(
            std::vector<std::string>{MUTANT_0_0, MUTANT_0_1, MUTANT_0_2, MUTANT_0_3, MUTANT_0_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Mutant_1, new TextureSet(
            std::vector<std::string>{MUTANT_1_0, MUTANT_1_1, MUTANT_1_2, MUTANT_1_3, MUTANT_1_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Mutant_2, new TextureSet(
            std::vector<std::string>{MUTANT_2_0, MUTANT_2_1, MUTANT_2_2, MUTANT_2_3, MUTANT_2_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Mutant_3, new TextureSet(
            std::vector<std::string>{MUTANT_3_0, MUTANT_3_1, MUTANT_3_2, MUTANT_3_3, MUTANT_3_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Mutant_4, new TextureSet(
            std::vector<std::string>{MUTANT_4_0, MUTANT_4_1, MUTANT_4_2, MUTANT_4_3, MUTANT_4_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Mutant_5, new TextureSet(
            std::vector<std::string>{MUTANT_5_0, MUTANT_5_1, MUTANT_5_2, MUTANT_5_3, MUTANT_5_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Mutant_6, new TextureSet(
            std::vector<std::string>{MUTANT_6_0, MUTANT_6_1, MUTANT_6_2, MUTANT_6_3, MUTANT_6_4},
            this->renderer, this->window_surface, WALKING_TIME));
    dynamic_textures.emplace(Mutant_7, new TextureSet(
            std::vector<std::string>{MUTANT_7_0, MUTANT_7_1, MUTANT_7_2, MUTANT_7_3, MUTANT_7_4},
            this->renderer, this->window_surface, WALKING_TIME));
}
