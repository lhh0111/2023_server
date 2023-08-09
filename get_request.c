#include <errno.h>
#include "get_request.h"
#include "unix_wrapper.h"

// 에러 처리 코드 추가 필요
// req는 요청 메시지를 저장할 구조체를 가리키는 포인터, size는 그 구조체의 크기(sizeof)
int _get_req(int sd, void * req, int size) 
{
    char * temp = (char *)req;
    while(temp < (char *)req + size){
        Read(sd, temp, 1);
        temp++
    }
    return 0;
}

void _get_req_mcu(int sd, void * req, int type)
{
    if(type==MESSAGE_A){
        ;
    }
    else if(type==MESSAGE_B){
        char double_s_temp[100];
        char * temp = double_s_temp;
        while(true){
            Read(sd, temp, 1);
            if(*temp == ' '){
                *temp = '\0';
            }
            temp++;
        } 
    }
}