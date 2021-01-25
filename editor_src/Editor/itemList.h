#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QListWidget>

class ItemList : public QListWidget
{
    Q_OBJECT
public:
    explicit ItemList(int pieceSize, QWidget *parent = nullptr);
private:
    void add(const QPixmap &pixmap);
    int itemSize;
};

#endif // ITEMLIST_H
