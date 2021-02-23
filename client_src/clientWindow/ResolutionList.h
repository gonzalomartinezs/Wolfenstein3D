#ifndef WOLFENSTEINCLIENT_RESOLUTIONLIST_H
#define WOLFENSTEINCLIENT_RESOLUTIONLIST_H

#include <QListWidget>
#include "Resolution.h"

// Lista de resoluciones, interacciona con el usuario.
class ResolutionList : public QListWidget {
Q_OBJECT

public:
    explicit ResolutionList (QWidget *parent = nullptr);
    void addItem(const Resolution& in );
    Resolution getSelected();
};

#endif //WOLFENSTEINCLIENT_RESOLUTIONLIST_H
