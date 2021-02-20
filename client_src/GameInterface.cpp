#include <iostream>
#include "GameInterface.h"

GameInterface::GameInterface(UI_Handler& ui_handler, SoundHandler& sound_handler,
                             ProtectedQueue<UI_Info> &queue,
                             UI_Info initial_info, int refresh_rate):
                        ui_handler(ui_handler), sound_handler(sound_handler),
                        queue(queue), keep_running(true),refresh_rate(refresh_rate),
                        latest_info(initial_info){
    //this->sound_handler.startBackMusic();
}


void GameInterface::run() {
    while(keep_running){
        bool important_found = false;
        UI_Info new_info = this->latest_info;
        UI_Info aux = this->latest_info;
        while(!this->queue.isEmpty()){
            aux = this->queue.pop();
            if (aux.isImportant()) {
                new_info = aux;
                important_found = true;
            }
        }
        if (!important_found) new_info = aux;
        _updateScreen(new_info);
    }
}

void GameInterface::stop() {
    this->keep_running = false;
}

bool GameInterface::finished() {
    return !(this->keep_running);
}

// ------------------------- Metodos privados --------------------------------//
// Refresca la pantalla gradualmente tras un movimiento de camara o del
// jugador, de acuerdo a refresh_rate.
void GameInterface::_updateScreen(UI_Info new_info) {
    DirectedPositionable old_pos = latest_info.getPlayerPos();
    DirectedPositionable new_pos = new_info.getPlayerPos();
    PlayerView old_view = latest_info.getCameraPlanes();

    float old_x = old_pos.getX();
    float old_y = old_pos.getY();
    float old_dir_x = old_pos.getDirX();
    float old_dir_y = old_pos.getDirY();
    float old_plane_x = old_view.getPlaneX();
    float old_plane_y = old_view.getPlaneY();

    float step_pos_x = (new_pos.getX() - old_pos.getX())/refresh_rate;
    float step_pos_y = (new_pos.getY() - old_pos.getY())/refresh_rate;
    float step_dir_x = (new_pos.getDirX() - old_dir_x)/refresh_rate;
    float step_dir_y = (new_pos.getDirY() - old_dir_y)/refresh_rate;
    float step_plane_x = (new_info.getCameraPlanes().getPlaneX() -
                          latest_info.getCameraPlanes().getPlaneX())/refresh_rate;
    float step_plane_y = (new_info.getCameraPlanes().getPlaneY() -
                          latest_info.getCameraPlanes().getPlaneY())/refresh_rate;

    for (int i=0; i<refresh_rate; i++){
        ui_handler.clearScreen();
        ui_handler.loadBackground();
        old_pos.setX(old_x + step_pos_x * i);
        old_pos.setY(old_y + step_pos_y * i);
        old_pos.setDirX(old_dir_x + step_dir_x * i);
        old_pos.setDirY(old_dir_y + step_dir_y * i);
        old_view.movePlaneX(old_plane_x + step_plane_x * i);
        old_view.movePlaneY(old_plane_y + step_plane_y * i);

        ui_handler.raycast(old_pos, old_view, new_info.getStaticObjects(),
                           new_info.getDirectedObjects(),
                           new_info.getDoorStates());
        ui_handler.loadPlayerHUD(new_info.getPlayerInfo());
        ui_handler.render();
    }
    sound_handler.loadGameSfx(new_info.getPlayerInfo(), new_pos,
                              new_info.getDirectedObjects(),
                              new_info.getDoorStates(),
                              new_info.getSounds());
    this->latest_info = new_info;
}


