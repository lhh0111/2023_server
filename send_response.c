#include "send_response.h"
#include "sql_constant.h"
#include "structure_message.h"
#include "unix_wrapper.h"
#include "safe_m_constant.h"

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
    char res[3] = {MESSAGE_B_START, RELAY_NO_REQ, '&'};
    res[1] = relay_status;
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

void _send_d_res(int sd, char safe_m_err, const char * token_buffer)
{
    char res[2+TOKEN_SIZE];
    res[0] = MESSAGE_D_START;
    res[1] = safe_m_err;
    memcpy(&res[2], token_buffer, TOKEN_SIZE);

    char * temp = res;
    while(temp < res + sizeof(res)){
            Write(sd, temp, 1);
            temp++;
    }
    
    return;
}

void _send_e_res(int sd, char safe_m_err, char (*power_list)[U_ID_LENGTH], uint32_t power_number)
{
    struct MessageEResponse res;
    res.type = MESSAGE_E_START;
    res.safe_m_err = safe_m_err;
    res.power_number = power_number;

    char * point = (char *)&res;
    char * temp = point;

    while(temp < point + sizeof(res)){
        Write(sd, temp, 1);
        temp++;
    }

    char (*temp_list)[U_ID_LENGTH] = power_list;

    while(temp_list < power_list + power_number){
        for(int i = 0; i < U_ID_LENGTH; i++){
            Write(sd, *temp_list + i, 1);
        }
        temp_list++;
    }
    free(power_list);
    return;
}

void _send_j_res(int sd, char safe_m_err)
{
    struct MessageJResponse res;
    res.start = MESSAGE_J_START;
    res.safe_m_err = safe_m_err;

    char * point = (char *)&res;
    char * temp = point;

    while(temp < point + sizeof(res)){
        Write(sd, temp, 1);
        temp++;
    }

    return;
}