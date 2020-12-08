#ifndef ITEMSLIST_H
#define ITEMSLIST_H

#include <QListWidget>

class ItemsList : public QListWidget
{
    Q_OBJECT
public:
    ItemsList();
    void add(const QPixmap &pixmap, const QPoint &location);
};

#endif // ITEMSLIST_H
