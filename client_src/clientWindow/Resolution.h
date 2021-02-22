//
// Created by riedel on 22/2/21.
//

#ifndef WOLFENSTEINCLIENT_RESOLUTION_H
#define WOLFENSTEINCLIENT_RESOLUTION_H

#include <string>

class Resolution {
public:
    Resolution (int x = 480, int y = 320);
    int getX() const;
    int getY() const;
    std::string toString() const;
private:
    int x;
    int y;
};


#endif //WOLFENSTEINCLIENT_RESOLUTION_H
