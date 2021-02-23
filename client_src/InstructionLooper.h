#ifndef WOLFENSTEINCLIENT_INSTRUCTIONLOOPER_H
#define WOLFENSTEINCLIENT_INSTRUCTIONLOOPER_H

#include "Client.h"
#include "EventHandler.h"

class InstructionLooper{
private:
    Client* client;
    EventHandler& event_handler;

public:
    // Crea un instruction looper listo para ser utilizado.
    InstructionLooper(Client* client, EventHandler& event_handler);

    // Ejecuta el loop de envio de instrucciones al servidor.
    void run(bool &quit);

    // Libera los recursos uitilizados por el objeto.
    ~InstructionLooper();
};


#endif //WOLFENSTEINCLIENT_INSTRUCTIONLOOPER_H
