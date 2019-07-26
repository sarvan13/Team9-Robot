#define LARRY_H
#define CLAW_LIMIT_PIN PB13

enum larry_success
{
    PASS,
    FAIL
};
class Larry
{
    public:
        Larry();
        void move_larry(double distance); //mm
        larry_success go_far_larry();
        void go_home_larry();
        double current_position;
        int state;
    private:
        int reg_speed;
};

