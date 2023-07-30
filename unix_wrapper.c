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
            fprintf("remote socket was closed\n", stderr);
            exit(3);
        }
        else{
            if(errno != EINTR){
                fprintf("read failed with error code: %u\n", stderr, errno);
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
            fprintf("remote socket was closed\n", stderr);
            exit(3);
        }
        else{
            if(errno != EINTR){
                fprintf("write failed with error code: %u\n", stderr, errno);
                exit(2);
            }
        }
    }
}