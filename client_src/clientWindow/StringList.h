#ifndef WOLFENSTEINCLIENT_STRINGLIST_H
#define WOLFENSTEINCLIENT_STRINGLIST_H

#include <QListWidget>

class StringList : public QListWidget {
Q_OBJECT
 /*Clase Stringlist, Usada para mostrar una lista de strings Por pantalla,
    Seleccionable. */
public:
    //Constructor, recibe el widget padre.
    explicit StringList(QWidget *parent = nullptr);
    // Agrega item a la lista, cada item tiene un id y un string.
    // El string es el que se ve por pantalla.
    void addItem(uint8_t key, const std::string& string);
    // Develvue el icono seleccionado por el usuario.
    uint8_t getSelected();
};

#endif //WOLFENSTEINCLIENT_STRINGLIST_H
