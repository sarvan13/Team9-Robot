#define LEVIOSA_H

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
    private:
        int reg_speed;
        double current_position;
        enum qrd_state base_state;
};



