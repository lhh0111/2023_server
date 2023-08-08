#pragma once
#pragma pack(push, 1)

#include <stdint.h>

#define RESPONSE_SQL_ERROR "Z&"

#define U_ID_LENGTH 8
#define U_ID_LENGTH_S "8"
#define USER_ID_LENGTH 8
#define USER_ID_LENGTH_S "8"
#define USER_PW_LENGTH 16
#define USER_PW_LENGTH_S "16"

#define TOKEN_SIZE 8
#define TOKEN_SIZE_S "8"

#define MESSAGE_A 0
#define MESSAGE_B 1
#define MESSAGE_C 2
#define MESSAGE_D 3
#define MESSAGE_E 4
#define MESSAGE_F 5
#define MESSAGE_G 6
#define MESSAGE_H 7
#define MESSAGE_I 8
#define MESSAGE_J 9

#define MESSAGE_A_START '0'
#define MESSAGE_A_LAST '&'
#define MESSAGE_B_START '1'
#define MESSAGE_C_START '2'
#define MESSAGE_D_START '3'
#define MESSAGE_E_START '4'
#define MESSAGE_F_START '5'
#define MESSAGE_G_START '6'
#define MESSAGE_H_START '7'
#define MESSAGE_I_START '8'
#define MESSAGE_J_START '9'

#define RELAY_NO_REQ '8'

struct MessageARequest{
    char u_id[U_ID_LENGTH];
};

struct MessageBRequest{
    char u_id[U_ID_LENGTH];
    double hole_2_energy;
    double hole_1_energy;
    double hole_0_energy;
    double energy_interval;

    double tem;

    double hum;

    double dust;
};

struct MessageCRequest{
    char id[USER_ID_LENGTH ];
    char pw[USER_PW_LENGTH ];
};

struct MessageDRequest{
    char id[USER_ID_LENGTH];
    char pw[USER_PW_LENGTH];
};

struct MessageERequest{
    char id[USER_ID_LENGTH];
    char token[TOKEN_SIZE];
};

struct MessageEResponse{
    char type;
    char safe_m_err;
    uint32_t power_number;
};

struct MessageFRequest{
    char id[USER_ID_LENGTH];
    char token[TOKEN_SIZE];
    char u_id[U_ID_LENGTH];
    char relay_req;
};

struct MessageFResponse{
    char type;
    char safe_m_err;
};

struct MessageGRequest{
    char id[USER_ID_LENGTH];
    char token[TOKEN_SIZE];
    char u_id[U_ID_LENGTH];
};

struct MessageGResponse{
    char type;
    char safe_m_err;
    double hole_2_month;
    double hole_1_month;
    double hole_0_month;
    double hole_2_week;
    double hole_1_week;
    double hole_0_week;
    double hole_2_day;
    double hole_1_day;
    double hole_0_day;
    double hole_2_now;
    double hole_1_now;
    double hole_0_now;
};

struct MessageHRequest{
    char id[USER_ID_LENGTH];
    char token[TOKEN_SIZE];
    char u_id[U_ID_LENGTH];
};

struct MessageHResponse{
    char type;
    char safe_m_err;
    double tem_month;
    double hum_month;
    double dust_month;
    double tem_week;
    double hum_week;
    double dust_week;
    double tem_day;
    double hum_day;
    double dust_day;
    double tem_now;
    double hum_now;
    double dust_now;
};

struct MessageJRequest{
    char id[USER_ID_LENGTH];
    char token[TOKEN_SIZE];
    char u_id[U_ID_LENGTH];
};

struct MessageJResponse{
    char start;
    char safe_m_err;
};
#pragma pack(pop)