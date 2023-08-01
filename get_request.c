#include <errno.h>
#include "get_request.h"

// 에러 처리 코드 추가 필요
// req는 요청 메시지를 저장할 구조체를 가리키는 포인터, size는 그 구조체의 크기(sizeof)
int _get_req(int sd, void * req, int size) 
{
    char * temp = (char *)req;
    while(temp < (char *)req + size){
        int err = read(sd, temp, 1);
        if(err<0){
            if(errno!=EINTR){
                return -1;
            }
        }
        else if(err==0){ // 요청 메시지를 받는 중 정상 종료가 됐다는 것은 오류 상황.
            return -1;
        }
        else{
            temp++;
        }
    }
    return 0;
}