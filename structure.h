#pragma once
#include "define.h"
#include "structure.h"
#include <stdint.h>

#pragma pack(push, 1)

struct MessageARequest{
    char u_id[U_ID_LENGTH];
};

struct MessageAResponse{
    char type;
    char safe_m_err;
    char end;
};

struct MessageBRequest{
    char u_id[U_ID_LENGTH];
    /*
    double hole_2_energy;
    double hole_1_energy;
    double hole_0_energy;
    double energy_interval;
    */
    double tem;

    double hum;

    double dust;
};

struct MessageBResponse{
    char type;
    char safe_m_err;
    /*
    char relay_req;
    char end;
    */
};

struct MessageCRequest{
    char id[USER_ID_LENGTH ];
    char pw[USER_PW_LENGTH ];
};

struct MessageCResponse{
    char type;
    char safe_m_err;
};

struct MessageDRequest{
    char id[USER_ID_LENGTH];
    char pw[USER_PW_LENGTH];
};


struct MessageDResponse{
    char type;
    char safe_m_err;
    char token[TOKEN_SIZE];
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

struct MessageIRequest{
    char id[USER_ID_LENGTH];
    char token[TOKEN_SIZE];
    char u_id[U_ID_LENGTH];
};

struct MessageIResponse{
    char type;
    char safe_m_err;
    char relay_req;
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

struct MessageNRequest{
    char u_id[U_ID_LENGTH];
};

struct MessageNResponse{
    char type;
    char safe_m_err;
    char relay_req;
};
#pragma pack(pop)