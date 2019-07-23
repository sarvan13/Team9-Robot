#define LEVIOSA_H

class Leviosa
{
    public:
        void wingardium_leviosa(int position); //mm
        void go_home_hermione();
    private:
        int reg_speed;
        int current_position;
        enum qrd_state base_state;
};

enum qrd_state{
    BLACK = 1,
    WHITE = 0,
};

#endif //LEVIOSA_H