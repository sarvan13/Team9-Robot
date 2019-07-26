#ifndef COMMUNICATION_H
#define COMMUNICATION_H

enum request
{
    NOT_DONE,
    FINISHED
};

enum transmit
{
    LEFT_POLE_PICKUP,
    RIGHT_POLE_PICKUP,
    GAUNTLET_PICKUP
};
class Communication
{
    public:
        Communication();
        void master_transmit_stone_left();
        void master_transmit_stone_right();
        void master_transmit_gauntlet();
        void master_request();
};

#endif //COMMUNICATION_H