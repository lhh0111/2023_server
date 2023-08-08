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

void _sql_a_req(int sd, struct MessageARequest * req);
void _sql_b_req(int sd, struct MessageBRequest * req, char * relay_req);
char _sql_c_req(int sd, struct MessageCRequest *req);
char _sql_d_req(int sd, struct MessageDRequest *req, char * token_buffer, int token_buffer_size);
char _sql_e_req(int sd, struct MessageERequest * req, char (**power_list)[U_ID_LENGTH], uint32_t * power_number);
char _sql_g_req(int sd, struct MessageGRequest * req, struct MessageGResponse * res);
char _sql_h_req(int sd, struct MessageHRequest * req, struct MessageHResponse * res);
char _sql_j_req(int sd, struct MessageJRequest * req);