#ifndef WOLFENSTEINCLIENT_STRINGLIST_H
#define WOLFENSTEINCLIENT_STRINGLIST_H

#include <QListWidget>

class StringList : public QListWidget {
Q_OBJECT

public:
    explicit StringList(QWidget *parent = nullptr);
    void addItem(uint8_t key, const std::string& string);
    uint8_t getSelected();

};


#endif //WOLFENSTEINCLIENT_STRINGLIST_H
