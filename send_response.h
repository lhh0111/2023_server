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



void _send_b_res(int sd, char relay_status);
void _send_c_res(int sd, char safe_m_err);
void _send_d_res(int sd, char safe_m_err, const char * token_buffer);
void _send_j_res(int sd, char safe_m_err);