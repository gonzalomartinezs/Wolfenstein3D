#include "Resolution.h"

int Resolution::getX() const {
    return x;
}

int Resolution::getY() const {
    return y;
}

Resolution::Resolution(int _x, int _y) {
    this->x = _x;
    this->y = _y;
}

std::string Resolution::toString() const {
    return ( std::to_string(x) + "X" + std::to_string(y) );
}
