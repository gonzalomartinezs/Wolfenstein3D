#ifndef ITEMLIST_H
#define ITEMLIST_H

#include <QListWidget>
#include <vector>
#include "iconscontainer.h"

class ItemList : public QListWidget
{
    Q_OBJECT
public:
    explicit ItemList(QWidget *parent = nullptr);
    static QString editorMimeType() { return QStringLiteral("item"); }
    void loadList(const IconsContainer& list);
    void addIcon(const int& key, const QPixmap& icon);

protected:
    void startDrag(Qt::DropActions supportedActions) override;

private:

};

#endif // ITEMLIST_H
