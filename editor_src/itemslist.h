#ifndef ITEMSLIST_H
#define ITEMSLIST_H

#include <QListWidget>

class ItemsList : public QListWidget
{
    Q_OBJECT
public:
    ItemsList(QWidget *parent = nullptr);
    void add(const QPixmap &pixmap);
};

#endif // ITEMSLIST_H
