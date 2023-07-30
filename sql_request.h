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


void _sql_b_req(int sd, struct MessageBRequest * req, char * relay_req);
char _sql_c_req(int sd, struct MessageCRequest *req);
int _sql_d_req(struct MessageDRequest *req, char * token, int token_size);