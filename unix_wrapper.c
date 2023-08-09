#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>


int Read(int fd, void * buf, size_t nbytes)
{
    int n;

    while(1){
        n = read(fd, buf, nbytes);
        if(n>0){
            return n;
        }
        else if(n==0){
            fprintf(stderr, "remote socket was closed\n");
            exit(3);
        }
        else{
            if(errno != EINTR){
                fprintf(stderr, "read failed with error code: %u\n", errno);
                exit(2);
            }
        }
    }
}

int Write(int fd, void * buf, size_t nbytes)
{
    int n;

    while(1){
        n = write(fd, buf, nbytes);
        if(n>0){
            return n;
        }
        else if(n==0){
            fprintf(stderr, "remote socket was closed\n");
            exit(3);
        }
        else{
            if(errno != EINTR){
                fprintf(stderr ,"write failed with error code: %u\n", errno);
                exit(2);
            }
        }
    }
}