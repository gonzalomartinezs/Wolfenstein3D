#ifndef WOLFENSTEIN3D_THCLIENT_H_
#define WOLFENSTEIN3D_THCLIENT_H_

#include <atomic>
#include <string>

#include "../common_src/Thread.h"
#include "../common_src/Peer.h"
#include "../common_src/ProtectedQueue.h"
#include "../common_src/BlockingQueue.h"

class ThClient : public Thread {
private:
    std::atomic<bool> is_connected;
    Peer peer;
    ProtectedQueue<uint8_t> RecvQueue;
    BlockingQueue<std::string> SendQueue;
    std::string name;

public:
    /* Constructor */
    explicit ThClient(Peer& _peer);

    /* Lanza los threads que iteran la cola protegida y la cola bloquante,
     * para luego joinearlos*/
    void run() override;

    /* Devuelve true si la cola del Recv esta vacia, false
     * en caso contrario */
    bool isEmpty() const;

    /* Popea un elemento de la cola del Recv */
    uint8_t pop();

    /* Agrega a la cola bloqueante (Send) el contenido de buffer */
    void push(uint8_t* buffer, int bytes_to_send);

    /* Termina la ejecución de los threads del Send y Recv, y
     * cierra el Socket */
    void stop() override;

    /* Devuelve true si finalizó la conexión con el cliente */
    bool finished() override;

    /* Guarda el nombre del jugador */
    void setName(std::string name);

    /* Devuelve el nombre del jugador */
    std::string getName() const;

    /* Destructor */
    ~ThClient();
private:
    /* Itera sobre la función Recv y acola en una cola protegida
     * los bytes que recibe */
    void recv();

    /* Itera sobre la función Send, desacola los bytes de la cola
     * bloqueante y los envía */
    void send();
};

#endif  // WOLFENSTEIN3D_THCLIENT_H_
