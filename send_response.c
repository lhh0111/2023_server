#include "send_response.h"
#include "sql_constant.h"
#include "structure_message.h"
#include "unix_wrapper.h"

void _send_a_res(int sd)
{
    char res[2] = {MESSAGE_A_START, '&'};
    char * temp = res;
    while(temp < res + sizeof(res)){
        Write(sd, temp, 1);
        temp++;
    }
    return;
}

void _send_b_res(int sd, char relay_status)
{
    char res[3] = {MESSAGE_B_START, relay_status, '&'};
    char * temp = res;
    while(temp < res + sizeof(res)){
        Write(sd, temp, 1);
        temp++;
    }
    return;
}

void _send_c_res(int sd, char safe_m_err)
{
    char res[2] = {MESSAGE_C_START, safe_m_err};
    char * temp = res;
    while(temp < res + sizeof(res)){
        Write(sd, temp, 1);
        temp++;
    }
    return;
}

void _send_d_res(int sd, int sql, char * token)
{
    char res[2+TOKEN_SIZE];
    res[0] = MESSAGE_D_START;
    memcpy(&res[2], token, TOKEN_SIZE);

    if(sql==SQL_SUCCESS){
        res[1] = '0';

    }
    else if(sql==SQL_INVALID_ID_PW){
        res[1] = '1';
    }
    else if(sql==SQL_ERROR){
        res[1] = '2';
    }
    char * temp = res;
    while(temp < res + sizeof(res)){
            write(sd, temp, 1);
            temp++;
    }
    
    return;
}