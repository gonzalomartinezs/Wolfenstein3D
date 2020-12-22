#include "RaycastingThread.h"
RaycastingThread::RaycastingThread(ProtectedQueue<DrawingInfo> &queue,
                        Raycaster &raycaster, Window &window,
                        DrawingInfo initial_info, int refresh_rate):
                        queue(queue), raycaster(raycaster), window(window),
                        keep_running(true), refresh_rate(refresh_rate),
                        latest_info(initial_info){}


void RaycastingThread::run() {
    while(keep_running){
        if (this->queue.isEmpty()){
            for (int i=0; i<refresh_rate; i++){
                window.clearScreen();
                raycaster.draw(latest_info.getPlayerPos(),
                               latest_info.getCameraPlanes(),
                               latest_info.getStaticObjects(),
                               latest_info.getDirectedObjects());
                window.render();
            }
        } else {
            _updateScreen();
        }
    }
}

void RaycastingThread::stop() {
    this->keep_running = false;
}

bool RaycastingThread::finished() {
    return !(this->keep_running);
}

// ------------------------- Metodos privados --------------------------------//
// Refresca la pantalla gradualmente tras un movimiento de camara o del
// jugador, de acuerdo a refresh_rate.
void RaycastingThread::_updateScreen() {
    DrawingInfo new_info = this->queue.pop();
    DirectedPositionable old_pos = latest_info.getPlayerPos();
    DirectedPositionable new_pos = new_info.getPlayerPos();
    PlayerView old_view = latest_info.getCameraPlanes();

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
        window.clearScreen();

        old_pos.moveX(step_pos_x);
        old_pos.moveY(step_pos_y);
        old_pos.setDirX(old_dir_x + step_dir_x * i);
        old_pos.setDirY(old_dir_y + step_dir_y * i);
        old_view.movePlaneX(old_plane_x + step_plane_x * i);
        old_view.movePlaneY(old_plane_y + step_plane_y * i);

        raycaster.draw(old_pos, old_view, new_info.getStaticObjects(),
                       new_info.getDirectedObjects());
        window.render();
    }
    this->latest_info = new_info;
}

