#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QListWidget>
#include <vector>
#include "iconscontainer.h"

 /* Clase itemList, es la encargada de contener los items que se pueden utilizar
  * en el editor.*/
class ItemList : public QListWidget {
    Q_OBJECT
public:
    // Constructor por defecto.
    explicit ItemList(QWidget *parent = nullptr);

    /*  Metodo usado para el dragNdrop.
     *  devuelve el MimeType que guarda la lista.
     */
    static QString editorMimeType() { return QStringLiteral("item"); }
    /*
     * Recibe un IconContainer previamente incializado,
     * Carga los componentes del mismo en la lista.     */
    void loadList(const IconsContainer& list);
    /* Agrega icono a la lista.
     */
    void addIcon(const int& key, const QPixmap& icon);

protected:
    // Para hacer funcionar Drag And Drop.
    void startDrag(Qt::DropActions supportedActions) override;
};

#endif // ITEMLIST_H
