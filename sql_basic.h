#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include "mysql.h"
#include "structure_message.h"
#include "sql_constant.h"

#include "sql_basic.h"
#include "structure_message.h"

#define MONTH_TO_SEC 2629800.0
#define WEEK_TO_SEC 604800.0
#define DAY_TO_SEC 86400.0
#define MINUTE_TO_SEC 60.0

void error_occured(int sd, MYSQL * conn);


void create_table_REG(int sd, MYSQL * conn);


void delete_from_table_REG(int sd, MYSQL * conn, const char * u_id);


void insert_into_table_REG(int sd, MYSQL * conn, const char * u_id);


void create_table_ENERGY(int sd, MYSQL * conn, const char * u_id);

void insert_into_table_ENERGY(int sd, MYSQL * conn, const char * u_id, double h2, double h1, double h0, double interval);


void create_table_TEM(int sd, MYSQL * conn, const char * u_id);

void insert_into_table_TEM(int sd, MYSQL * conn, const char * u_id, double tem);


void create_table_HUM(int sd, MYSQL * conn, const char * u_id);


void insert_into_table_HUM(int sd, MYSQL * conn, const char * u_id, double hum);

void create_table_DUST(int sd, MYSQL * conn, const char * u_id);

void insert_into_table_DUST(int sd, MYSQL * conn, const char * u_id, double dust);


void create_table_RELAY_REQ(int sd, MYSQL * conn, const char * u_id);


void select_from_table_RELAY_REQ(int sd, MYSQL * conn, const char * u_id, MYSQL_RES ** result);

void create_table_ID_PW(int sd, MYSQL * conn);

bool check_duplicated_id_from_table_ID_PW(int sd, MYSQL * conn, const char * id);

void insert_into_table_ID_PW(int sd, MYSQL * conn, const char * id, const char * pw);


bool check_valid_id_pw(int sd, MYSQL * conn, const char * id, const char * pw);

void create_table_LOGIN_TOKEN(int sd, MYSQL * conn);

void delete_from_table_LOGIN_TOKEN(int sd, MYSQL * conn, const char * id);

void insert_into_table_LOGIN_TOKEN(int sd, MYSQL * conn, const char * id, const char * token_buffer);

bool check_valid_token_from_LOGIN_TOKEN(int sd, MYSQL * conn, const char * id, const char * token_buffer);

void update_token_from_LOGIN_TOKEN(int sd, MYSQL * conn, const char * id);

void create_table_POWER_TO_USER(int sd, MYSQL * conn);

void delete_from_table_POWER_TO_USER(int sd, MYSQL * conn, const char * u_id);

void insert_into_table_POWER_TO_USER(int sd, MYSQL * conn, const char * u_id, const char * id);

bool check_sync_with_REG(int sd, MYSQL * conn, const char * u_id);

void select_from_table_POWER_TO_USER(int sd, MYSQL * conn, const char * id, char (**power_list)[8], uint32_t * power_number);

void create_table_POWER_LIST(int sd, MYSQL * conn);

bool check_valid_u_id(int sd, MYSQL * conn, const char * u_id);

void insert_into_table_RELAY_REQ(int sd, MYSQL * conn, const char * u_id, const char relay_req);

void get_average_power_month(int sd, MYSQL * conn, const char * u_id, struct MessageGResponse * res);

void get_average_power_week(int sd, MYSQL * conn, const char * u_id, struct MessageGResponse * res);

void get_average_power_day(int sd, MYSQL * conn, const char * u_id, struct MessageGResponse * res);

void get_average_power_now(int sd, MYSQL * conn, const char * u_id, struct MessageGResponse * res);