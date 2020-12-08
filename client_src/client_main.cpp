#include <iostream>
#include <SDL2/SDL.h>
#include "Client.h"
#include "Window.h"
#include "Raycaster.h"
#include "PlayerView.h"
#include "textures/TexturesContainer.h"
#include "login/ClientLoginScreen.h"
#include "../common_src/Map.h"
#include "../common_src/PlayerPosition.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define IS_NOT_MOVING 0
#define IS_MOVING_FORWARDS 1
#define IS_MOVING_BACKWARDS 2
#define IS_TURNING_LEFT 3
#define IS_TURNING_RIGHT 4
#define REFRESH_RATE 10

int main(int argc, char *argv[]) {
    ClientLoginScreen log;
    log(); //  genera la nueva pestaña.
    bool quit = false;
    SDL_Event event;
    try {
        Client client(log.getHost(), log.getPort());

        Window window("Wolfenstein 3D", WINDOW_WIDTH, WINDOW_HEIGHT,
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = window.getRenderer();
        TexturesContainer tex(renderer);

        Map map("../../common_src/config.yaml");
        Raycaster raycaster(map, WINDOW_WIDTH, WINDOW_HEIGHT, *renderer, tex);
        PlayerPosition player;
        PlayerView view;

        int flag = IS_NOT_MOVING;
        while (!quit) {
            std::vector<PlayerPosition> players;
            const Uint8 *keys = SDL_GetKeyboardState(NULL);

            float old_pos_x = player.getPosX();
            float old_pos_y = player.getPosY();
            float old_dir_x = player.getDirX();
            float old_dir_y = player.getDirY();
            float old_plane_x = view.getPlaneX();
            float old_plane_y = view.getPlaneY();

            while (SDL_PollEvent(&event) != 0) {
                if (event.type == SDL_QUIT) {
                    quit = true;
                }
                if (keys[SDL_SCANCODE_UP]){
                    if (flag != IS_MOVING_FORWARDS){
                        flag = IS_MOVING_FORWARDS;
                        client.sendInstruction(IS_MOVING_FORWARDS);
                    }
                } else if (keys[SDL_SCANCODE_DOWN]) {
                    if (flag != IS_MOVING_BACKWARDS) {
                        flag = IS_MOVING_BACKWARDS;
                        client.sendInstruction(IS_MOVING_BACKWARDS);
                    }
                } else if (keys[SDL_SCANCODE_RIGHT]) {
                    if (flag != IS_TURNING_RIGHT) {
                        flag = IS_TURNING_RIGHT;
                        client.sendInstruction(IS_TURNING_RIGHT);
                    }
                } else if (keys[SDL_SCANCODE_LEFT]) {
                    if (flag != IS_TURNING_LEFT) {
                        flag = IS_TURNING_LEFT;
                        client.sendInstruction(IS_TURNING_LEFT);
                    }
                } else if (!keys[SDL_SCANCODE_UP] && !keys[SDL_SCANCODE_DOWN]
                            && !keys[SDL_SCANCODE_RIGHT]
                            && !keys[SDL_SCANCODE_LEFT]) {
                    if (flag != IS_NOT_MOVING) {
                        flag = IS_NOT_MOVING;
                        client.sendInstruction(IS_NOT_MOVING);
                    }
                }
            }
            client.receiveCoordenates(player, view, players);
            float step_pos_x = (player.getPosX() - old_pos_x)/REFRESH_RATE;
            float step_pos_y = (player.getPosY() - old_pos_y)/REFRESH_RATE;
            float step_dir_x = (player.getDirX() - old_dir_x)/REFRESH_RATE;
            float step_dir_y = (player.getDirY() - old_dir_y)/REFRESH_RATE;
            float step_plane_x = (view.getPlaneX() - old_plane_x)/REFRESH_RATE;
            float step_plane_y = (view.getPlaneY() - old_plane_y)/REFRESH_RATE;

            for (int i=0; i<REFRESH_RATE; i++){
                PlayerPosition aux(old_pos_x, old_pos_y, old_dir_x, old_dir_y);
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);

                aux.moveHorizontally(step_pos_x * i);
                aux.moveVertically(step_pos_y * i);
                aux.setDirX(old_dir_x + step_dir_x * i);
                aux.setDirY(old_dir_y + step_dir_y * i);

                raycaster.draw(aux, old_plane_x + i * step_plane_x, old_plane_y + i * step_plane_y);
                window.render();
            }
        }
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch(...) {
        std::cout << "Unknown error.\n";
    }

    return  0;
}
