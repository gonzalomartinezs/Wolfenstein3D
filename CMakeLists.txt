cmake_minimum_required(VERSION 3.16)
project(WolfensteinClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -std=c++11 -pthread -lyaml-cpp -I/usr/include/lua5.3/ -llua5.3 -ggdb")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${WolfensteinClient_SOURCE_DIR}/cmake")

find_package(PkgConfig)
pkg_check_modules(YAMLCPP REQUIRED yaml-cpp>=0.5)

find_package(Lua REQUIRED)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(SDL2 REQUIRED SDL2)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

add_executable(Wolfenstein3D client_src/client_main.cpp
        client_src/Client.h client_src/Client.cpp
        client_src/Window.h client_src/Window.cpp common_src/Exceptions/WindowException.cpp
        client_src/Raycaster.h client_src/Raycaster.cpp
        client_src/PlayerView.h client_src/PlayerView.cpp
        common_src/Socket.h common_src/Socket.cpp
        common_src/Exceptions/ErrorSocket.h common_src/Exceptions/ErrorSocket.cpp
        common_src/Peer.h common_src/Peer.cpp
        common_src/DirectedPositionable.h common_src/DirectedPositionable.cpp
        common_src/Map.h common_src/Map.cpp
        common_src/SlidingSurface.cpp common_src/Collider.cpp
        common_src/GameConstants.h
        client_src/textures/TexturesContainer.h client_src/textures/TexturesContainer.cpp
        client_src/textures/Texture.h client_src/textures/Texture.cpp
        client_src/textures/DynamicTexture.cpp
        client_src/Exceptions/TextureLoadingException.cpp
        client_src/Exceptions/FontLoadingException.cpp
        client_src/login/ClientLoginScreen.h client_src/login/ClientLoginScreen.cpp
        client_src/login/Login.h client_src/login/Login.cpp
        client_src/login/ui_Login.h
        client_src/EventHandler.cpp client_src/EventHandler.h
        common_src/Positionable.cpp common_src/Positionable.h
        common_src/Exceptions/ErrorMap.h common_src/Exceptions/ErrorMap.cpp
        common_src/Timer.cpp
        client_src/SpriteRenderer.cpp client_src/SpriteRenderer.h
        client_src/UI_Info.cpp client_src/UI_Info.h
        client_src/GameInterface.cpp client_src/GameInterface.h
        common_src/Thread.cpp
        common_src/Exceptions/WolfensteinException.cpp
        common_src/Configuration.cpp
        client_src/UI_Handler.cpp
        common_src/Exceptions/ConfigurationException.cpp
        client_src/textures/FontTexture.cpp
        client_src/RaycastingRenderer.cpp
        client_src/Exceptions/RaycastingException.cpp client_src/sound/Music.cpp client_src/sound/Music.h client_src/Exceptions/SoundLoadingException.cpp client_src/Exceptions/SoundLoadingException.h client_src/sound/SoundEffect.cpp client_src/sound/SoundEffect.h client_src/sound/SoundsContainer.cpp client_src/sound/SoundsContainer.h client_src/sound/SoundID.h client_src/SoundHandler.cpp client_src/SoundHandler.h client_src/textures/TextureSet.cpp client_src/textures/TextureSet.h client_src/SpriteSelector.cpp client_src/SpriteSelector.h)

add_executable(server server_src/server_main.cpp
        server_src/Game.cpp server_src/Bots/Bot.cpp
        server_src/Bots/Destripador.lua
        server_src/Player.cpp server_src/Sound.cpp
        common_src/Collider.cpp common_src/RectCollider.cpp
        common_src/Timer.cpp
        server_src/ThClient.cpp
        server_src/GameManager.cpp
        server_src/GamesHandler.cpp
        server_src/ClientHandler.cpp
        server_src/ClientManager.cpp server_src/Lobby.cpp
        server_src/MapsReader.cpp server_src/DirectoryWalker.cpp
        common_src/ProtectedQueue.h
        common_src/Socket.cpp
        common_src/Peer.cpp
        common_src/Exceptions/ErrorSocket.cpp
        common_src/Thread.cpp
        server_src/Exceptions/GameException.cpp
        common_src/Positionable.cpp common_src/Positionable.h
        common_src/DirectedPositionable.h common_src/DirectedPositionable.cpp
        common_src/Map.h common_src/Map.cpp
        common_src/Exceptions/ErrorMap.h common_src/Exceptions/ErrorMap.cpp
        common_src/ManualDoor.cpp common_src/Doors.cpp common_src/SlidingSurface.cpp
        common_src/GameConstants.h
        common_src/Item.cpp
        common_src/Items.cpp common_src/Exceptions/ItemsException.cpp
        common_src/BulletItem.cpp common_src/BulletItem.h
        common_src/MachineGunItem.cpp common_src/MachineGunItem.h
        common_src/ChainGunItem.cpp common_src/ChainGunItem.h
        common_src/Exceptions/ItemException.cpp common_src/Exceptions/ItemException.h
        common_src/RocketLauncherItem.cpp common_src/RocketLauncherItem.h
        common_src/Treasure.cpp
        common_src/HealthRecover.cpp common_src/Exceptions/HealthRecoverException.cpp
        common_src/Blood.cpp
        common_src/KeyItem.cpp
        common_src/Exceptions/WolfensteinException.cpp
        common_src/Configuration.cpp
        server_src/PlayerActions.cpp server_src/LeaderBoard.cpp
        server_src/Weapons/Weapons.cpp
        server_src/Weapons/Weapon.cpp server_src/Weapons/Knife.cpp
        server_src/Weapons/Pistol.cpp server_src/Weapons/ChainGun.cpp
        server_src/Weapons/MachineGun.cpp server_src/Weapons/Rocket.cpp
        server_src/Key.cpp
        server_src/Sound.cpp
        common_src/Exceptions/ConfigurationException.cpp)

target_compile_options(server PRIVATE -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -std=c++11 -DDEBUG -fno-inline)

target_link_libraries(server PRIVATE ${YAMLCPP_LIBRARIES} ${LUA_LIBRARIES} -ldl)

target_link_options(server PRIVATE -pthread)

target_link_libraries(Wolfenstein3D PRIVATE SDL2 Qt5::Widgets ${YAMLCPP_LIBRARIES}
                        ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES}
                        ${SDL2_MIXER_LIBRARIES})
