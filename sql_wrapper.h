#pragma once

#include "mysql.h"

void Mysql_query(MYSQL * conn, const char *q);
MYSQL_RES * Mysql_store_result(MYSQL * conn);
MYSQL * Mysql_init(void);
void Mysql_close(MYSQL * conn);
MYSQL * Mysql_real_connect(MYSQL * mysql);