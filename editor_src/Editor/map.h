#ifndef MAP_H
#define MAP_H

#include "mapelement.h"
#include <QWidget>
#include  <QVector>


class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);

signals:
private:
        QVector<MapElement> items;

};

#endif // MAP_H
