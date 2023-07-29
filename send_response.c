#include "send_response.h"
#include "sql_constant.h"
#include "structure_message.h"

void _send_b_res(int sd, int sql, char relay_status)
{
    if(sql==SQL_SUCCESS){
        char buffer[3] = {'1', relay_status, '&'};
        char * temp = buffer;
        while(temp < buffer + sizeof(buffer)){
            write(sd, temp, 1);
            temp++;
        }
    }
    else{
        char buffer[3] = {'1', RELAY_FAIL, '&'};
        char * temp = buffer;
        while(temp < buffer + sizeof(buffer)){
            write(sd, temp, 1);
            temp++;
        }
    }
    return;
}

void _send_c_res(int sd, int sql)
{
    if(sql==SQL_SUCCESS){
        char buffer[2] = {'2', '0'}; 
        char * temp = buffer;
        while(temp < buffer + sizeof(buffer)){
            write(sd, temp, 1);
            temp++;
        }
    }
    else if(sql==SQL_ERROR){
        char buffer[2] = {'2', '2'}; 
        char * temp = buffer;
        while(temp < buffer + sizeof(buffer)){
            write(sd, temp, 1);
            temp++;
        }
    }
    else if(sql==SQL_DUPLICATED_ID){
        char buffer[2] = {'2', '1'}; 
        char * temp = buffer;
        while(temp < buffer + sizeof(buffer)){
            write(sd, temp, 1);
            temp++;
        }
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