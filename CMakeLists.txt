cmake_minimum_required(VERSION 3.16)
project(WolfensteinClient)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2 -std=c++11 -pthread -lyaml-cpp -I/usr/include/lua5.3/ -llua5.3 -ggdb")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${WolfensteinClient_SOURCE_DIR}/cmake")

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

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
        client_src/Client.cpp
        client_src/Window.cpp common_src/Exceptions/WindowException.cpp
        client_src/Raycaster.cpp
        client_src/PlayerView.cpp
        common_src/Socket.cpp common_src/AddrInfo.cpp
        common_src/Exceptions/ErrorSocket.cpp
        common_src/Peer.cpp
        common_src/DirectedPositionable.cpp
        common_src/Map.cpp
        common_src/SlidingSurface.cpp common_src/Collider.cpp common_src/RectCollider.cpp
        common_src/ManualDoor.cpp common_src/Doors.cpp
        server_src/Exceptions/GameException.cpp
        common_src/GameConstants.h
        client_src/textures/TexturesContainer.cpp
        client_src/textures/Texture.cpp
        client_src/textures/DynamicTexture.cpp
        client_src/Exceptions/SDLException.cpp
        client_src/EventHandler.cpp
        common_src/Positionable.cpp
        common_src/Exceptions/ErrorMap.h common_src/Exceptions/ErrorMap.cpp
        common_src/Timer.cpp
        client_src/SpriteRenderer.cpp
        client_src/UI_Info.cpp
        client_src/GameInterface.cpp
        common_src/Thread.cpp
        common_src/Exceptions/WolfensteinException.cpp
        common_src/Configuration.cpp
        client_src/UI_Handler.cpp
        common_src/Exceptions/ConfigurationException.cpp
        client_src/textures/FontTexture.cpp
        client_src/RaycastingRenderer.cpp
        client_src/sound/Music.cpp
        client_src/sound/SoundEffect.cpp
        client_src/sound/SoundsContainer.cpp
        client_src/SoundHandler.cpp
        client_src/textures/TextureSet.cpp
        client_src/SpriteSelector.cpp
        client_src/clientWindow/clientwindow.cpp
        client_src/clientWindow/clientwindow.ui
        client_src/clientWindow/ResolutionList.cpp
        client_src/clientWindow/StringList.cpp
        client_src/clientWindow/Resolution.cpp
        client_src/LeaderboardRenderer.cpp
        client_src/ClientData.cpp
        client_src/InstructionLooper.cpp)

add_executable(serverW3D server_src/server_main.cpp
        server_src/Game.cpp server_src/Bots/Bot.cpp
        server_src/Bots/Destripador.lua
        server_src/Player.cpp
        common_src/Collider.cpp common_src/RectCollider.cpp
        common_src/Timer.cpp
        server_src/ThClient.cpp
        server_src/GameManager.cpp
        server_src/GamesHandler.cpp
        server_src/ClientHandler.cpp
        server_src/ClientManager.cpp server_src/Lobby.cpp
        server_src/MapsReader.cpp server_src/DirectoryWalker.cpp
        common_src/ProtectedQueue.h
        common_src/Socket.cpp common_src/AddrInfo.cpp
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
        server_src/Items/Item.cpp
        server_src/Items/Items.cpp server_src/Exceptions/ItemsException.cpp
        server_src/Items/BulletItem.cpp server_src/Items/BulletItem.h
        server_src/Items/MachineGunItem.cpp server_src/Items/MachineGunItem.h
        server_src/Items/ChainGunItem.cpp server_src/Items/ChainGunItem.h
        server_src/Exceptions/ItemException.cpp server_src/Exceptions/ItemException.h
        server_src/Items/RocketLauncherItem.cpp server_src/Items/RocketLauncherItem.h
        server_src/Items/Treasure.cpp
        server_src/Items/HealthRecover.cpp server_src/Exceptions/HealthRecoverException.cpp
        server_src/Items/Blood.cpp
        server_src/Items/KeyItem.cpp
        common_src/Exceptions/WolfensteinException.cpp
        common_src/Configuration.cpp
        server_src/PlayerActions.cpp server_src/LeaderBoard.cpp
        server_src/Weapons/Weapons.cpp
        server_src/Weapons/Weapon.cpp server_src/Weapons/Knife.cpp
        server_src/Weapons/Pistol.cpp server_src/Weapons/ChainGun.cpp
        server_src/Weapons/MachineGun.cpp
        server_src/Weapons/RocketLauncher.cpp
        server_src/Key.cpp
        server_src/Sound.cpp
        common_src/Exceptions/ConfigurationException.cpp
        server_src/Sound.cpp
        server_src/Weapons/RocketLauncher.cpp
        server_src/Weapons/Rocket.cpp
        server_src/RandomPosition.cpp)

target_compile_options(serverW3D PRIVATE -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -std=c++11 -DDEBUG -fno-inline)

target_link_libraries(serverW3D PRIVATE ${YAMLCPP_LIBRARIES} ${LUA_LIBRARIES} -ldl)

target_link_options(serverW3D PRIVATE -pthread)

target_link_libraries(Wolfenstein3D PRIVATE SDL2 Qt5::Widgets ${YAMLCPP_LIBRARIES}
                        ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES}
                        ${SDL2_MIXER_LIBRARIES})

install(TARGETS serverW3D
    RUNTIME DESTINATION "/usr/games/Wolfenstein3D/server/executable/")

install(DIRECTORY "server_src/Maps"
    DESTINATION "/usr/games/Wolfenstein3D/server/server_src/Maps"
    COMPONENT serverW3D)

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_PACKAGE_NAME "Wolfenstein3DServer")
set(CPACK_PACKAGE_FILE_NAME "W3DServer")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Grupo 4 - Taller - 2c2020")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION "Wolfenstein3D server.")
set(CPACK_PACKAGE_ICON "logo.png")

install(FILES server_src/Bots/Destripador.lua DESTINATION /usr/games/Wolfenstein3D/server/server_src/Bots/ COMPONENT serverW3D)
install(FILES executable/logo.png DESTINATION share/icons/Wolfenstein3D/ COMPONENT serverW3D)
install(FILES executable/Editor.desktop DESTINATION /usr/share/applications/ COMPONENT serverW3D) 

#install(TARGETS Wolfenstein3D
#    RUNTIME DESTINATION "/usr/games/Wolfenstein3D/client/executable")

#install(DIRECTORY "client_src/fonts"
#    DESTINATION "/usr/games/Wolfenstein3D/client/client_src"
#    COMPONENT Wolfenstein3D)

#install(DIRECTORY "client_src/login"
#    DESTINATION "/usr/games/Wolfenstein3D/client/client_src"
#    COMPONENT Wolfenstein3D)

#install(DIRECTORY "client_src/textures"
#    DESTINATION "/usr/games/Wolfenstein3D/client/client_src"
#    COMPONENT Wolfenstein3D)

#set(CPACK_GENERATOR "DEB")
#set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
#set(CPACK_PACKAGE_NAME "Wolfenstein3D")
#set(CPACK_PACKAGE_FILE_NAME "W3DClient")
#set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Grupo 4 - Taller - 2c2020")
#set(CPACK_PACKAGE_VERSION_MAJOR "1")
#set(CPACK_PACKAGE_VERSION_MINOR "0")
#set(CPACK_PACKAGE_VERSION_PATCH "0")
#set(CPACK_PACKAGE_DESCRIPTION "Wolfenstein3D cliente.")
#set(CPACK_PACKAGE_ICON "logo.png")

#install(FILES executable/logo.png DESTINATION share/icons/Wolfenstein3D/ COMPONENT Wolfenstein3D)
#install(FILES executable/Editor.desktop DESTINATION /usr/share/applications/ COMPONENT Wolfenstein3D) 


INCLUDE(CPack)