#define SUSAN_H
#define LIMIT_PIN PA15

class Susan
{
    public:
        Susan();
        void turn_susan(int step);
        void go_home_susan();
        float point_to_min_distance();
        float get_sonar_distance();
    private:
        double current_position; //ticks
        void send_step();
        void set_dir(int dir);
};

