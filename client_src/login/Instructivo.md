### Mini instructivo de como usar el ClientLoginScreen

## se debe tener instalado el paquete : 
    "qt5-default".
## Agregar al Cmake la linea : 
            find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
## Se deben incluir al proyecto los archivos :
    Login.cpp Login.h ui_Login.h ClientLoginScreen.cpp ClientLoginScreen.h

## Mini ejemplo de uso : 
    #include "ClientLoginScreen.h"                                          
                                                                            
    int main(int argc, char *argv[]) {                                      
       ClientLoginScreen log;                                               
       log(); //  genera la nueva pestaña.                                  
       std::cout << "el nombre ingresado fue " << log.getName() << std::endl
       std::cout << "el host ingresado fue " << log.getHost() << std::endl; 
       std::cout << "el puerto ingresado fue " << log.getPort() << std::endl
    }
                                                                           