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


void select_from_table_RELAY_REQ(int sd, MYSQL * conn, const char * u_id, MYSQL_RES * result);

void create_table_ID_PW(int sd, MYSQL * conn);

bool check_duplicated_id_from_table_ID_PW(int sd, MYSQL * conn, const char * id);

void insert_into_table_ID_PW(int sd, MYSQL * conn, const char * id, const char * pw);
