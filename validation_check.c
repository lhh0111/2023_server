#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "define.h"
#include "structure.h"

// 인자로 들어온 char가 의미하는 문자가 id에 들어가기에 적합한지를 문자들의 아스키 코드를 사용하여 테스트함. 
static bool check_char_in_id_validation(char c)
{
    if( (   (   47  <   c   )   &&  (   c   <   58  )   )   ||  (   (   64  <   c   )   &&  (   c   <   91  )   )   ||  (   (   96  <   c   )   &&  (   c   <   123 )   )   ){
        return true;
    }
    else return false;
}

// id에 있는 문자들이 id에 들어가기에 적합한지를 테스트함.
static bool check_id_validation(char * id)
{
    int count=0;
    char * temp = id;
    while((*temp)!='\0'){
        if(!check_char_in_id_validation(*(temp++))){
            return false;
        }
        count++;
    }
    if(count < USER_ID_MIN_LENGTH){
        return false;
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

static bool check_pw_validation(char * pw)
{
    char * temp = pw;
    int count;
    while((*temp)!='\0'){
        if(!check_char_in_pw_validation(*(temp++))){
            return false;
        }
        count++;
    }
    if(count < USER_PW_MIN_LENGTH){
        return false;
    }
    return true;
}

static bool check_char_in_token_validation(char c)
{
    if( (   (   47  <   c   )   &&  (   c   <   58  )   )   ||  (   (   64  <   c   )   &&  (   c   <   91  )   )){
        return true;
    }
    else return false;
}

static bool check_token_validation(char * token)
{
    char * temp = token;
    while((*temp)!='\0'){
        if(!check_char_in_token_validation(*(temp++))){
            return false;
        }
    }
    return true;
}

static bool check_char_in_u_id_validation(char c)
{
    if( (   (   47  <   c   )   &&  (   c   <   58  )   )   ||  (   (   64  <   c   )   &&  (   c   <   91  )   )){
        return true;
    }
    else return false;
}

static bool check_u_id_validation(char * u_id)
{
    char * temp = u_id;
    while((*temp)!='\0'){
        if(!check_char_in_u_id_validation(*(temp++))){
            return false;
        }
    }
    return true;
}

static bool check_relay_req_validation(const char relay_req)
{
    if((47 < relay_req) && (relay_req < 56)){
        return true;
    }
    else{
        return false;
    }
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

bool check_req_d_validation(struct MessageDRequest * req)
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

bool check_req_e_validation(struct MessageERequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    if(!check_id_validation(id)){
        return false;
    }

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, sizeof(token) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_token_validation(token)){
        return false;
    }
    return true;
}

bool check_req_f_validation(struct MessageFRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    if(!check_id_validation(id)){
        return false;
    }

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, sizeof(token) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_token_validation(token)){
        return false;
    }

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_u_id_validation(u_id)){
        return false;
    }

    char relay_req = req->relay_req;
    if(!check_relay_req_validation(relay_req)){
        return false;
    }
    
    return true;
}
bool check_req_g_validation(struct MessageGRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    if(!check_id_validation(id)){
        return false;
    }

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, sizeof(token) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_token_validation(token)){
        return false;
    }

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_u_id_validation(u_id)){
        return false;
    }

    return true;
}
bool check_req_h_validation(struct MessageHRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    if(!check_id_validation(id)){
        return false;
    }

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, sizeof(token) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_token_validation(token)){
        return false;
    }

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_u_id_validation(u_id)){
        return false;
    }

    return true;
}

bool check_req_i_validation(struct MessageIRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    if(!check_id_validation(id)){
        return false;
    }

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, sizeof(token) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_token_validation(token)){
        return false;
    }

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_u_id_validation(u_id)){
        return false;
    }

    return true;
}

bool check_req_j_validation(struct MessageJRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    if(!check_id_validation(id)){
        return false;
    }

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, sizeof(token) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_token_validation(token)){
        return false;
    }

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    token[sizeof(token) - 1] = '\0';

    if(!check_u_id_validation(u_id)){
        return false;
    }

    return true;
}
