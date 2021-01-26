#include "map.h"

Map::Map(QWidget *parent) : QWidget(parent)
{
    Q_INIT_RESOURCE(editor);
    setAcceptDrops(true);
    //ver esto
    setMinimumSize(500, 500);
    setMaximumSize(500, 500); //carguemos 5x5 de vacios.

}

