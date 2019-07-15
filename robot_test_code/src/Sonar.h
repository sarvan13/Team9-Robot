#ifndef SONAR_H
#define SONAR_H

#include "PinNames.h"

enum sonar_state 
{
    NO_DETECTION,
    PLUSHIE_LEFT,
    PLUSHIE_RIGHT,
    PLUSHIE_FRONT,
    COLLISION_SIDE,
    COLLISION_FRONT,
};

enum side
{
    LEFT,
    RIGHT
};

class Sonar 
{
    public:
        Sonar();
        sonar_state check_sonar();
        sonar_state sonar_value;
    private:
        sonar_state front_sonar();
        sonar_state side_sonar(PinName trigpin, PinName echopin, side side);
        float pulse(PinName trigpin, PinName echopin);
};



#endif //SONAR_H