#ifndef PLAYERPOSITION_H
#define PLAYERPOSITION_H

class PlayerPosition {
private:
    float pos_x;
    float pos_y;
    float dir_x;
    float dir_y;

public:
    explicit PlayerPosition(float pos_x=0.0, float pos_y=0.0,
                            float dir_x=.707, float dir_y=.707);

    PlayerPosition operator=(const PlayerPosition& other);

    void moveHorizontally(float movement);
    void moveVertically(float movement);
    float getPosX() const;
    float getPosY() const;

    void setDirX(float new_dir);
    void setDirY(float new_dir);
    float getDirX() const;
    float getDirY() const;

    ~PlayerPosition(){}

};


#endif //PLAYERPOSITION_H
