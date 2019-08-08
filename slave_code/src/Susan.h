#define SUSAN_H


class Susan
{
    public:
        Susan();
        void turn_susan(int step);
        void go_home_susan();
        float point_to_min_distance();
        float get_sonar_distance();
        void go_home_susan_CW();
        void set_sweep_angle(int steps);
    private:
        double current_position; //ticks
        void send_step();
        void set_dir(int dir);
        int sweep_angle;
};

