#pragma once
#include <stddef.h>

int Read(int fd, void * buf, size_t nbytes);
int Write(int fd, void * buf, size_t nbytes);