#ifndef WOLFENSTEIN3D_SOUND_H_
#define WOLFENSTEIN3D_SOUND_H_

#include "../common_src/Positionable.h"
#include "../client_src/sound/SoundID.h"

class Sound : public Positionable {
private:
    SoundID sound;

public:
    /* Constructor */
    Sound(float x, float y, SoundID sound);

    /* Retorna el ID del sonido. */
    SoundID getSound();

    /* Destructor */
    ~Sound();
};

#endif  // WOLFENSTEIN3D_SOUND_H_
