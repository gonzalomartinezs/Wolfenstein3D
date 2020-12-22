#include <SDL2/SDL.h>
#include <iostream>
#include "Client.h"
#include "Window.h"
#include "Raycaster.h"
#include "PlayerView.h"
#include "EventHandler.h"
#include "RaycastingThread.h"
#include "textures/TexturesContainer.h"
#include "login/ClientLoginScreen.h"
#include "../common_src/Map.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/Timer.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define REFRESH_RATE 10
#define IS_NOT_MOVING 0


const double TICK_DURATION = 1/256.f; /* miliseconds que tarda en actualizarse el juego */

int main(int argc, char *argv[]) {
    ClientLoginScreen log;
    log(); //  genera la nueva pestaña.
    bool quit = false;

    try {
        ProtectedQueue<DrawingInfo> drawing_info;
        BlockingQueue<int> instructions;

        Window window("Wolfenstein 3D", WINDOW_WIDTH, WINDOW_HEIGHT,
                      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOW_SHOWN);
        TexturesContainer tex(window.getRenderer());

        Map map("../common_src/config.yaml");
        Raycaster raycaster(map, WINDOW_WIDTH, WINDOW_HEIGHT, tex);

        //Client client("localhost", "5875", instructions, drawing_info);
        Client client(log.getHost(), log.getPort(), instructions, drawing_info);
        EventHandler event_handler(instructions);

        DirectedPositionable player(2, 2, -1, 0, None);
        PlayerView view(0,1);
        std::vector<Positionable> static_objects;
        std::vector<DirectedPositionable> directed_objects;

        DrawingInfo initial_info(player,
                                 view, static_objects,
                                 directed_objects);
        RaycastingThread raycasting_thread(drawing_info, raycaster, window, initial_info, REFRESH_RATE);

        int flag = IS_NOT_MOVING;
        Timer time_between_updates;
        double last_tick_time;

        std::thread send_thread(&Client::sendInstruction, &client);
        std::thread recv_thread(&Client::receiveInformation, &client);

        raycasting_thread.start();

        while (!quit) {
            time_between_updates.start();
            directed_objects.clear();
            const Uint8 *keys = SDL_GetKeyboardState(NULL);

            event_handler.run(quit, flag, keys);

            last_tick_time = time_between_updates.getTime();
            if (last_tick_time < TICK_DURATION*1000){
                usleep((TICK_DURATION * 1000 - last_tick_time) * 1000);
            }
        }
        client.shutdown();
        raycasting_thread.stop();
        send_thread.join();
        recv_thread.join();
        raycasting_thread.join();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch(...) {
        std::cout << "Unknown error.\n";
    }
    return  0;
}
