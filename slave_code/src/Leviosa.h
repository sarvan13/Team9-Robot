#define LEVIOSA_H
#define LIMIT_PIN PB3

enum qrd_state{
    BLACKY,
    WHITEY,
};

class Leviosa
{
    public:
        Leviosa();
        void wingardium_leviosa(int position); //mm
        void go_home_hermione();
        void read_leviosa();
        int get_current_position();
        void set_speed(int speed);
    private:
        int reg_speed;
        int current_position;
        enum qrd_state current_state = WHITEY;
        int check_leviosa();
};



