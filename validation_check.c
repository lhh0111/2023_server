#include "structure_message.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 인자로 들어온 char가 의미하는 문자가 id에 들어가기에 적합한지를 문자들의 아스키 코드를 사용하여 테스트함. 
static bool check_char_in_id_validation(char c)
{
    if( (   (   47  <   c   )   &&  (   c   <   58  )   )   ||  (   (   64  <   c   )   &&  (   c   <   91  )   )   ||  (   (   96  <   c   )   &&  (   c   <   123 )   )   ){
        return true;
    }
    else return false;
}

// id에 있는 문자들이 id에 들어가기에 적합한지를 테스트함.
static bool check_id_validation(const char * id)
{
    char * temp = id;
    while((*temp)!='\0'){
        if(!check_char_in_id_validation(*(temp++))){
            return false;
        }
    }
    return true;
}

static bool check_char_in_pw_validation(char c)
{
    if( (   (   32  <   c   )   &&  (   c   <   127  )   )   ){
        if( (   c   ==  34  )  ||  (   c   ==  39  )  ||  (   c   ==  92  )   ){
            return false;
        } // ' 또는 " 또는 백슬래시인지 아스키 값으로 확인함
        else{
            return true;
        }
    }
    else return false;
}

static bool check_pw_validation(const char * pw)
{
    char * temp = pw;
    while((*temp)!='\0'){
        if(!check_char_in_pw_validation(*(temp++))){
            return false;
        }
    }
    return true;
}

bool check_req_c_validation(struct MessageCRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    if(!check_id_validation(id)){
        return false;
    }

    char pw[USER_PW_LENGTH + 1];
    memcpy(pw, req->pw, sizeof(pw) - 1);
    pw[sizeof(pw) - 1] = '\0';

    if(!check_pw_validation(pw)){
        return false;
    }

    return true;

}

