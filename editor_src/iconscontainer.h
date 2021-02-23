#ifndef ICONSCONTAINER_H
#define ICONSCONTAINER_H

#include <QPixmap>
#include <unordered_map>
#include "iconsPaths.h"
#include "EditorIcon.h"

class ItemList; //Foward declaration.

/* Clase que contiene los pixmaps.
 * Funciona como un hash donde el EditorIcon es la clave.
 */
class IconsContainer {

public:
    // Constructor como argumento el tam de los iconos,
    // es el encargado de cargar los pixmaps desde su respectivo path.
    IconsContainer(const unsigned& size);
    // Devuelve una referencia al pixmap asociado al editorIcon ingresado.
    const QPixmap& getIcon(Editor_icon)const;
    // Inicializa la clase ItemList. Cargando en la misma todos los Iconos a usar.
    void loadItemList(ItemList& list) const;
private:
    void add(const Editor_icon& id, const std::string& path);
    std::map<Editor_icon,QPixmap> icons;
    const unsigned iconSize;
};

#endif // ICONSCONTAINER_H
