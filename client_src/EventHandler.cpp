#include "EventHandler.h"

#define IS_NOT_MOVING 0
#define IS_MOVING_FORWARDS 1
#define IS_MOVING_BACKWARDS 2
#define IS_TURNING_LEFT 3
#define IS_TURNING_RIGHT 4

void EventHandler::run(bool &quit, int &flag, const Uint8 *keys) {
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            quit = true;
        }
        if (keys[SDL_SCANCODE_UP]){
            if (flag != IS_MOVING_FORWARDS){
                flag = IS_MOVING_FORWARDS;
                this->client.sendInstruction(IS_MOVING_FORWARDS);
            }
        } else if (keys[SDL_SCANCODE_DOWN]) {
            if (flag != IS_MOVING_BACKWARDS) {
                flag = IS_MOVING_BACKWARDS;
                this->client.sendInstruction(IS_MOVING_BACKWARDS);
            }
        } else if (keys[SDL_SCANCODE_RIGHT]) {
            if (flag != IS_TURNING_RIGHT) {
                flag = IS_TURNING_RIGHT;
                this->client.sendInstruction(IS_TURNING_RIGHT);
            }
        } else if (keys[SDL_SCANCODE_LEFT]) {
            if (flag != IS_TURNING_LEFT) {
                flag = IS_TURNING_LEFT;
                this->client.sendInstruction(IS_TURNING_LEFT);
            }
        } else if (!keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]
                   && !keys[SDL_SCANCODE_RIGHT]
                   && !keys[SDL_SCANCODE_LEFT]) {
            if (flag != IS_NOT_MOVING) {
                flag = IS_NOT_MOVING;
                this->client.sendInstruction(IS_NOT_MOVING);
            }
        }
    }
}
