#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement
{
    public:
        Movement();
        void turn_left();
        void turn_right();
        void u_turn();
        void reverse();
        void forward();
        void apply_pid(int pid);
        void grab_plushie_left();
        void grab_plushie_right();
        void grab_plushie_front();
        void stop();
        void set_speed(int speed);
        void rotate_forward();
        void rotate_backward();
    
    private:
        int reg_speed;
};

enum movement_amount
{
    CONTINUOUS = -1, 
    NINETY_DEGREES = 1230,
};
#endif //MOVEMENT_H