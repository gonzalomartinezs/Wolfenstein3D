#include <SDL2/SDL.h>
#include <unistd.h>
#include <QApplication>
#include "Client.h"
#include "Raycaster.h"
#include "PlayerView.h"
#include "UI_Handler.h"
#include "SoundHandler.h"
#include "GameInterface.h"
#include "textures/TexturesContainer.h"
#include "sound/SoundsContainer.h"
#include "clientWindow/clientwindow.h"

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    ClientWindow w;
    w.show();
    return a.exec();

}
