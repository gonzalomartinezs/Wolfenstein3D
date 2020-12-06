
#include <iostream>
#include "ClientLoginScreen.h"

int main(int argc, char *argv[]) {
   ClientLoginScreen log;
   log(); //  genera la nueva pestaña.
   std::cout << "el nombre ingresado fue " << log.getName() << std::endl;
   std::cout << "el host ingresado fue " << log.getHost() << std::endl;
   std::cout << "el puerto ingresado fue " << log.getPort() << std::endl;
}
