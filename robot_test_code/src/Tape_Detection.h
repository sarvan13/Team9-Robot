#ifndef TAPE_DETECTION_H
#define TAPE_DETECTION_H



enum branch_state
{
    NO_BRANCH,
    RIGHT_BRANCH,
    LEFT_BRANCH
};

enum marker_state
{
    NO_MARKER,
    RIGHT_MARKER,
    LEFT_MARKER
};
    
class Tape_Detection
{
    public:
        Tape_Detection();
        int get_pid();
        int get_path_error();
        int get_marker_error();
        branch_state branch_exists();
        marker_state marker_exists();
        branch_state branch_side;
        marker_state marker_side;
        int get_marker_val();
        int get_pid(float Kp, float Kd);
        float Kp;
        float Kd;
        void set_Kp(float Kp);
        void set_Kd(float Kd);
        int alternate_get_pid();
        int get_alternate_path_error();
        
    private:
        float path_error = 0;
        float previous_path_error = 0;

       
};


#endif