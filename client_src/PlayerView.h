#ifndef BOLUDECES_PLAYERVIEW_H
#define BOLUDECES_PLAYERVIEW_H

class PlayerView {
private:
    float camera_plane_x;
    float camera_plane_y;
public:
    // el vector (plane_x, plane_y) debe ser perpendicular al vector direccion
    // del jugador
    PlayerView(float plane_x=1, float plane_y=-1) : camera_plane_x(plane_x),
                                                    camera_plane_y(plane_y){}
    void movePlaneX(float movement);
    void movePlaneY(float movement);
    float getPlaneX() const;
    float getPlaneY() const;

    ~PlayerView(){}
};


#endif //BOLUDECES_PLAYERVIEW_H
