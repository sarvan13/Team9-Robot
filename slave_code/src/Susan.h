#define SUSAN_H

class Susan
{
    public:
        Susan();
        void turn_susan(int step);
        void go_home_susan();
        void point_to_min_distance();
    private:
        double current_position; //ticks
        float get_sonar_distance();

};

