#pragma once

#include "mysql.h"

int Mysql_query(MYSQL * conn, const char *q);
int Mysql_store_result(MYSQL * conn, MYSQL_RES ** p_result);
int Mysql_init(MYSQL ** p_conn);
void Mysql_close(MYSQL * conn);