#include "EventHandler.h"

#define NOT_MOVING 0
#define IS_MOVING_FORWARDS 1
#define IS_MOVING_BACKWARDS 2
#define IS_TURNING_LEFT 3
#define IS_TURNING_RIGHT 4
#define IS_FIRING 5
#define NOT_FIRING 6
#define NEXT_GUN 7
#define PREV_GUN 8

void EventHandler::run(bool &quit, int &flag, const Uint8 *keys) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        if (keys[SDL_SCANCODE_UP]){
            if (flag != IS_MOVING_FORWARDS){
                flag = IS_MOVING_FORWARDS;
                this->instructions.push(IS_MOVING_FORWARDS);
            }
        } else if (keys[SDL_SCANCODE_DOWN]) {
            if (flag != IS_MOVING_BACKWARDS) {
                flag = IS_MOVING_BACKWARDS;
                this->instructions.push(IS_MOVING_BACKWARDS);
            }
        } else if (keys[SDL_SCANCODE_RIGHT]) {
            if (flag != IS_TURNING_RIGHT) {
                flag = IS_TURNING_RIGHT;
                this->instructions.push(IS_TURNING_RIGHT);
            }
        } else if (keys[SDL_SCANCODE_LEFT]) {
            if (flag != IS_TURNING_LEFT) {
                flag = IS_TURNING_LEFT;
                this->instructions.push(IS_TURNING_LEFT);
            }
        } else if (keys[SDL_SCANCODE_LCTRL] || keys[SDL_SCANCODE_RCTRL]) {
            if (flag != IS_FIRING) {
                flag = IS_FIRING;
                this->instructions.push(IS_FIRING);
            }
        } else if (keys[SDL_SCANCODE_E]) {
            if (flag != NEXT_GUN) {
                flag = NEXT_GUN;
                this->instructions.push(NEXT_GUN);
            }
        } else if (keys[SDL_SCANCODE_Q]) {
            if (flag != PREV_GUN) {
                flag = PREV_GUN;
                this->instructions.push(PREV_GUN);
            }
        } else {
            if (flag == IS_FIRING) {
                flag = NOT_FIRING;
                this->instructions.push(NOT_FIRING);
            }
            else if (flag != NOT_MOVING) {
                flag = NOT_MOVING;
                this->instructions.push(NOT_MOVING);
            }
        }
    }
}

