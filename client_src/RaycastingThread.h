#ifndef RAYCASTINGTHREAD_H
#define RAYCASTINGTHREAD_H

#include <atomic>
#include "../client_src/Raycaster.h"
#include "../client_src/DrawingInfo.h"
#include "../client_src/Window.h"
#include "../common_src/Thread.h"
#include "../common_src/ProtectedQueue.h"
#include "../common_src/Positionable.h"
#include "../common_src/DirectedPositionable.h"

class RaycastingThread: public Thread {
private:
    ProtectedQueue<DrawingInfo>& queue;
    Raycaster& raycaster;
    Window& window;
    DrawingInfo latest_info;
    int refresh_rate;
    std::atomic<bool> keep_running;

public:
    // Crea un hilo de raycasting listo para ser utilizado.
    RaycastingThread(ProtectedQueue<DrawingInfo>& queue, Raycaster& raycaster,
                 Window& window, DrawingInfo initial_info, int refresh_rate);

    // Realiza el renderizado entre 2 transiciones la cantidad de veces
    // indicada en refresh rate.
    void run() override;

    // Detiene la ejecución del hilo.
    void stop() override;

    // Retorna un bool que indica si se finalizo el proceso o no.
    bool finished() override;

    ~RaycastingThread(){}

private:
    void _updateScreen(DrawingInfo new_info);
};

#endif //RAYCASTINGTHREAD_H
