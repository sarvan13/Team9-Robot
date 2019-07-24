#define TALONS_H

class Talons
{
    public:
        Talons();
        void open_claw();
        void close_claw();
        int get_current_angle();
    private:
        int angle; // NOT IN DEGREES/RADIANS - This is just controlling the duty cycle sent to servo which controls the angle. 30 is closed, 120 is about 200 degree angle
        void set_current_angle(int newAngle);
};

