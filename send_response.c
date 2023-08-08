#include "unix_wrapper.h"

void _send_res(int sd, void * res, int size){
    char * start = res;
    char * move = start;
    while(move < start + size){
        Write(sd, move, 1);
        move++;
    }
}
