#ifndef TRASHBIN_H
#define TRASHBIN_H

#include <QWidget>
#include  <QVector>

class TrashBin : public QWidget
{
    Q_OBJECT
public:
    explicit TrashBin(QWidget *parent = nullptr);

signals:

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    /*
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    */
};

#endif // TRASHBIN_H
