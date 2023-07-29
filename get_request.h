#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include "structure_message.h"

#define DATA_BUFFER_LENGTH 10

#define GET_REQ_ERROR

int _get_req(int sd, void * req, int size);