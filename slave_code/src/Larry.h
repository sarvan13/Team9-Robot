#define LARRY_H

class Larry
{
    public:
        void move_larry(int distance); //mm
        void go_far_larry();
        void go_home_larry();
    private:
        int reg_speed;
};

#endif //Larry