#ifndef TAPE_DETECTION_H
#define TAPE_DETECTION_H

#include <PID.h>

#define RIGHT_ON 0b000001
#define ALL_ON 0b000111

enum branch_state
{
    NO_BRANCH,
    RIGHT_BRANCH,
    LEFT_BRANCH
};
    
class Tape_Detection
{
    public:
        Tape_Detection();
        int get_pid();
        int get_path_error();
        int get_marker_error();
        branch_state branch_exists();
        int marker_exists();
        int branch_side;
        int marker_side;
        
    private:
        float path_error = 0;
        float previous_path_error = 0;
        int marker_error = 0;
        float previous_marker_error = 0;
};


#endif