#ifndef WOLFENSTEIN3D_CLIENTMANAGER_H_
#define WOLFENSTEIN3D_CLIENTMANAGER_H_

#include <atomic>
#include <vector>

#include "ThClient.h"
#include "Lobby.h"
#include "../common_src/Socket.h"
#include "../common_src/Configuration.h"
#include "GamesHandler.h"

class ClientHandler;

class ClientManager {
private:
    Configuration& config;
	Socket socket;
	std::atomic<bool> is_connected;

public:
    /* Constructor */
	explicit ClientManager(Configuration& config);

	/* Pone el socket aceptador a la espera de conexiones entrantes de manera permanente
	 * y los deriva con un clientHandler que se encarga de la comunicacion inicial */
	void operator()(GamesHandler& games);

	/* Hace que se dejen de aceptar nuevas conexiones entrantes */
	void stop();

	/* Destructor */
	~ClientManager();

private:
    /* Crea e inicializa un nuevo ThClient usando el peer */
    ThClient* _createClient(Peer& peer) const;

    /* Elimina los clientHandlers que hayan finalizado su ejecucion y
     * libera los recursos correspondientes */
    void _deleteFinishedChoosingClients(
    							std::vector<ClientHandler*>& choosingClients);
};

#endif  // WOLFENSTEIN3D_CLIENTMANAGER_H_
