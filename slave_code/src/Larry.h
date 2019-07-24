#define LARRY_H

class Larry
{
    public:
        Larry();
        void move_larry(double distance); //mm
        void go_far_larry();
        void go_home_larry();
        double current_position;
        int state;
    private:
        int reg_speed;
};

