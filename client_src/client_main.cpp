#include <SDL2/SDL.h>
#include <iostream>
#include "Client.h"
#include "Window.h"
#include "Raycaster.h"
#include "PlayerView.h"
#include "UI_Handler.h"
#include "SoundHandler.h"
#include "EventHandler.h"
#include "GameInterface.h"
#include "textures/TexturesContainer.h"
#include "login/ClientLoginScreen.h"
#include "sound/SoundsContainer.h"
#include "../common_src/Configuration.h"
#include "../common_src/Map.h"
#include "../common_src/DirectedPositionable.h"
#include "../common_src/Timer.h"

#define WINDOW_WIDTH 320
#define WINDOW_HEIGHT 200

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
        TexturesContainer tex(window.getRenderer(), window.getSurface());
        SoundsContainer sounds;

        Client client(log.getHost(), log.getPort(), instructions, drawing_info);
        client.lobbyInteraction(log.getName());
        Map map(client.receiveMap());

        EventHandler event_handler(instructions);
        Raycaster raycaster(map, WINDOW_WIDTH / 32, (-WINDOW_HEIGHT) / 18,
                            (30 * WINDOW_WIDTH) / 32, (17 * WINDOW_HEIGHT) / 18,
                            tex);
        UI_Handler ui_handler(window.getRenderer(), raycaster, tex,
                              "../client_src/fonts/Vermin Vibes 1989.ttf",
                              WINDOW_WIDTH, WINDOW_HEIGHT);
        SoundHandler sound_handler(sounds);

        DirectedPositionable player(2, 2, -1, 0, None);
        PlayerView view(0,1);
        std::vector<Positionable> static_objects;
        std::vector<DirectedPositionable> directed_objects;
        std::vector<std::pair<int,int>> sliders_changes;

        DrawingInfo initial_info(player, view, std::vector<int>(7,0), static_objects,
                                 directed_objects, sliders_changes);
        GameInterface game_interface(ui_handler, sound_handler, drawing_info, initial_info, REFRESH_RATE);

        int flag = IS_NOT_MOVING;
        Timer time_between_updates;
        double last_tick_time;

        std::thread send_thread(&Client::sendInstruction, &client);
        std::thread recv_thread(&Client::receiveInformation, &client);

        game_interface.start();

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
        game_interface.stop();
        send_thread.join();
        recv_thread.join();
        game_interface.join();
    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch(...) {
        std::cout << "Unknown error.\n";
    }
    return  0;
}
