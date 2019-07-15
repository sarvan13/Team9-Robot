#ifndef TAPE_DETECTION_H
#define TAPE_DETECTION_H

#include <PID.h>

enum branch_state
    {
        NO_BRANCH,
        RIGHT_BRANCH,
        LEFT_BRANCH
    };

enum marker_state
    {
        NO_MARKER,
        LEFT_MARKER,
        RIGHT_MARKER
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
        int branch_side;
        int marker_side;
        
    private:
        float error = 0;
        float previous_error = 0;
        PID pid;
    
};


#endif