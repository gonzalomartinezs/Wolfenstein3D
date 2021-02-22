

#ifndef WOLFENSTEINCLIENT_RESOLUTIONLIST_H
#define WOLFENSTEINCLIENT_RESOLUTIONLIST_H

#include <QListWidget>
#include "Resolution.h"

class ResolutionList : public QListWidget {
Q_OBJECT

public:
    explicit ResolutionList (QWidget *parent = nullptr);
    void addItem(const Resolution& in );
    Resolution getSelected();
};

#endif //WOLFENSTEINCLIENT_RESOLUTIONLIST_H
