#include "sql_wrapper.h"
#include "mysql.h"
#include <stdio.h>
#include "define.h"
#include "unix_wrapper.h"

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

int Mysql_query(MYSQL * conn, const char *q)
{
    if(mysql_query(conn, q)!=0){
        sql_output_error(conn);
        return SQL_API_FAIL;
    }
    else{
        return SQL_API_SUCCESS;
    }
}

int Mysql_store_result(MYSQL * conn, MYSQL_RES ** p_result)
{
    if((*p_result = mysql_store_result(conn))==NULL){ // 이전 쿼리문이 result set을 주지 않는 쿼리문이거나, 오류가 났을 때 true
        sql_output_error(conn); // 만약 프로세스 종료 없이 이 함수에서 return한다면 이전 쿼리문의 특성에 의해 NULL이 반환된 것임.
        return SQL_API_FAIL;
    }
    else{
        return SQL_API_SUCCESS;
    }
}

int Mysql_init(MYSQL ** p_conn)
{
    if((*p_conn = mysql_init(NULL))!=NULL){
        return SQL_API_SUCCESS;
    }
    else{
        return SQL_API_FAIL;
    }
}

void Mysql_close(MYSQL * conn)
{
    mysql_close(conn);
    mysql_library_end();
}
