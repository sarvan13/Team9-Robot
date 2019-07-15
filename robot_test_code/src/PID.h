#ifndef PID_H
#define PID_H

class PID
{
    public:
        PID();
        void read_K_values();
        float get_Kp();
        float get_Kd();
    private:
        float Kp = 0;
        float Kd = 0;
        float Kp_prev = 0;
        float Kd_prev = 0;
};
#endif //PID_H