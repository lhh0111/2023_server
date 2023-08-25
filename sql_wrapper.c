#include "sql_wrapper.h"
#include "mysql.h"
#include <stdio.h>
#include "define.h"
#include "unix_wrapper.h"
#include "sql_error.h"

/*
static void send_exit_with_sql_error(int sd)
{
    char res[] = RESPONSE_SQL_ERROR;
    char * temp = res;
    while(temp < res + sizeof(res)){
        Write(sd, temp, 1);
        temp++;
    }
    char test;
    while(true){
        Read(sd, &test, 1);
    }
}
*/

static void sql_output_error(MYSQL * conn)
{
    if(mysql_errno(conn)!=0){ // mysql_store_result()의 반환값이 NULL일 때, 정말 MYSQL 측의 에러인지, 아니면 이전 SQL문에 의한 정상적인 반환인지 판단하기 위한 조건문.
        fprintf(stderr, "%s, %d, %s\n", mysql_error(conn), mysql_errno(conn), mysql_sqlstate(conn));
    }
    return;
}

void Mysql_query(MYSQL * conn, const char *q)
{
    if(mysql_query(conn, q)!=0){
        set_sql_api_err();
        sql_output_error(conn);
    }
}

MYSQL_RES * Mysql_store_result(MYSQL * conn)
{
    MYSQL_RES * temp = mysql_store_result(conn);
    if(temp==NULL){ 
        set_sql_api_err();
        sql_output_error(conn);
    }
    return temp;
}

MYSQL * Mysql_init(void)
{
    MYSQL * temp = mysql_init(NULL);
    if(temp==NULL){
        set_sql_api_err();
    }
    return temp;
}

void Mysql_close(MYSQL * conn)
{
    mysql_close(conn);
    mysql_library_end();
}


MYSQL * Mysql_real_connect(MYSQL * mysql)
{
    MYSQL * temp = mysql_real_connect(mysql, MYSQL_CONN_HOST, MYSQL_CONN_USER, MYSQL_CONN_PW, NULL, 0, NULL, 0);
    if(temp == NULL){
        set_sql_api_err();
    }
    return temp;
}