#include "sql_basic.h"
#include "structure_message.h"
#include "unix_wrapper.h"

void error_occured(int sd, MYSQL * conn)
{
    if(mysql_errno(conn)!=0){ // mysql_store_result()의 반환값이 NULL일 때, 정말 MYSQL 측의 에러인지, 아니면 이전 SQL문에 의한 정상적인 반환인지 판단하기 위한 조건문.
        fprintf(stderr, "%s, %d, %s\n", mysql_error(conn), mysql_errno(conn), mysql_sqlstate(conn));
        char res[] = RESPONSE_SQL_ERROR;
        char * temp = res;
        while(temp < res + sizeof(res)){
            Write(sd, temp, 1);
            temp++;
        }
        mysql_close(conn);
        mysql_library_end();
        exit(1);
    }
}

int Mysql_query(int sd, MYSQL * conn, const char *q)
{
    int n;
    if((n = mysql_query(conn, q))!=0){
        error_occured(sd, conn);
        return n;
    }
    else{
        return n;
    }
}

MYSQL_RES * Mysql_store_result(int sd, MYSQL * conn)
{
    MYSQL_RES * result;
    if((result = mysql_store_result(conn))==NULL){ // 이전 쿼리문이 result set을 주지 않는 쿼리문이거나, 오류가 났을 때 true
        error_occured(sd, conn); // 만약 프로세스 종료 없이 이 함수에서 return한다면 이전 쿼리문의 특성에 의해 NULL이 반환된 것임.
        return result;
    }
    else{
        return result;
    }
}

void create_table_REG(int sd, MYSQL * conn)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS power_info.REG("REG_COL_0_NAME" "REG_COL_0_TYPE", "REG_COL_1_NAME" "REG_COL_1_TYPE")");
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void delete_from_table_REG(int sd, MYSQL * conn, const char * u_id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "DELETE FROM power_info.REG WHERE " REG_COL_0_NAME " = '%s'", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void insert_into_table_REG(int sd, MYSQL * conn, const char * u_id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO power_info.REG VALUES('%s', now())", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void create_table_ENERGY(int sd, MYSQL * conn, const char * u_id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_ENERGY (" ENERGY_COL_0_NAME " " ENERGY_COL_0_TYPE 
    ", " ENERGY_COL_1_NAME " " ENERGY_COL_1_TYPE ", " ENERGY_COL_2_NAME " " ENERGY_COL_2_TYPE 
    ", " ENERGY_COL_3_NAME " " ENERGY_COL_3_TYPE ", " ENERGY_COL_4_NAME " " ENERGY_COL_4_TYPE")",u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void insert_into_table_ENERGY(int sd, MYSQL * conn, const char * u_id, double h2, double h1, double h0, double interval)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO power_info.%s_ENERGY VALUES(%.2f, %.2f, %.2f, %.2f, now())", u_id, h2, h1, h0, interval);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);


}

void create_table_TEM(int sd, MYSQL * conn, const char * u_id)
{
    int sql_err = SQL_SUCCESS;

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_TEM (" TEM_COL_0_NAME " " TEM_COL_0_TYPE ", " TEM_COL_1_NAME " " TEM_COL_1_TYPE ")", u_id); 
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void insert_into_table_TEM(int sd, MYSQL * conn, const char * u_id, double tem)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO power_info.%s_TEM VALUES(%.2f, now())", u_id, tem);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void create_table_HUM(int sd, MYSQL * conn, const char * u_id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_HUM (" HUM_COL_0_NAME " " HUM_COL_0_TYPE ", " HUM_COL_1_NAME " " HUM_COL_1_TYPE ")", u_id); 
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void insert_into_table_HUM(int sd, MYSQL * conn, const char * u_id, double hum)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO power_info.%s_HUM VALUES(%.2f, now())", u_id, hum);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void create_table_DUST(int sd, MYSQL * conn, const char * u_id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_DUST (" DUST_COL_0_NAME " " DUST_COL_0_TYPE ", " DUST_COL_1_NAME " " DUST_COL_1_TYPE ")", u_id); 
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void insert_into_table_DUST(int sd, MYSQL * conn, const char * u_id, double dust)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO power_info.%s_DUST VALUES(%.2f, now())", u_id, dust);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void create_table_RELAY_REQ(int sd, MYSQL * conn, const char * u_id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_RELAY_REQ (" RELAY_REQ_COL_0_NAME " " RELAY_REQ_COL_0_TYPE ")",u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

void select_from_table_RELAY_REQ(int sd, MYSQL * conn, const char * u_id, MYSQL_RES * result)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM power_info.%s_RELAY_REQ", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);

    result = mysql_store_result(conn); // 에러가 일어났다면 result에는 NULL이 저장됨.
    error_occured(sd, conn);
}

void create_table_ID_PW(int sd, MYSQL * conn)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS user_info.ID_PW (" ID_PW_COL_0_NAME " " ID_PW_COL_0_TYPE ", " ID_PW_COL_1_NAME " " ID_PW_COL_1_TYPE")");
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

bool check_duplicated_id_from_table_ID_PW(int sd, MYSQL * conn, const char * id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.ID_PW WHERE " ID_PW_COL_0_NAME " = '%s'", id); 
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);
    error_occured(sd, conn);

    MYSQL_RES * result = mysql_store_result(conn);
    error_occured(sd, conn);

    bool duplicated;
    if(mysql_num_rows(result)>0){
        duplicated = true;
    }
    else{
        duplicated = false;
    }

    return duplicated;
}

void insert_into_table_ID_PW(int sd, MYSQL * conn, const char * id, const char * pw)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO user_info.ID_PW VALUES('%s', '%s')", id, pw);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    error_occured(sd, conn);
}

bool check_valid_id_pw(int sd, MYSQL * conn, const char * id, const char * pw)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.ID_PW WHERE "ID_PW_COL_0_NAME" = '%s' AND "ID_PW_COL_1_NAME" = '%s'", id, pw);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    MYSQL_RES *result = Mysql_store_result(sd, conn);
    if(mysql_num_rows(result)==0){
        mysql_free_result(result);
        return false;
    }
    else{
        mysql_free_result(result);
        return true;
    }
}

void create_table_LOGIN_TOKEN(int sd, MYSQL * conn)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.LOGIN_TOKEN ("LOGIN_TOKEN_COL_0_NAME" "LOGIN_TOKEN_COL_0_TYPE
    ", "LOGIN_TOKEN_COL_1_NAME" "LOGIN_TOKEN_COL_1_TYPE
    ", "LOGIN_TOKEN_COL_2_NAME" "LOGIN_TOKEN_COL_2_TYPE")");
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    return;
}

void delete_from_table_LOGIN_TOKEN(int sd, MYSQL * conn, const char * id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "DELETE FROM user_info.LOGIN_TOKEN WHERE "LOGIN_TOKEN_COL_0_NAME" = '%s'", id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    return;
}

void insert_into_table_LOGIN_TOKEN(int sd, MYSQL * conn, const char * id, const char * token_buffer)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO user_info.LOGIN_TOKEN VALUES('%s', '%s', now())", id, token_buffer);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    return;
}

bool check_valid_token_from_LOGIN_TOKEN(int sd, MYSQL * conn, const char * id, const char * token_buffer)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.LOGIN_TOKEN WHERE ("LOGIN_TOKEN_COL_0_NAME" = '%s') AND ("LOGIN_TOKEN_COL_1_NAME" = '%s') AND ("LOGIN_TOKEN_COL_2_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 30 MINUTE) AND NOW())", id, token_buffer);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    MYSQL_RES *result = Mysql_store_result(sd, conn);
    if(mysql_num_rows(result)==0){
        mysql_free_result(result);
        return false;
    }
    else{
        mysql_free_result(result);
        return true;
    }
}

void update_token_from_LOGIN_TOKEN(int sd, MYSQL * conn, const char * id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"UPDATE user_info.LOGIN_TOKEN SET "LOGIN_TOKEN_COL_2_NAME"=now() WHERE "LOGIN_TOKEN_COL_0_NAME"='%s'", id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    return;
}

void create_table_POWER_TO_USER(int sd, MYSQL * conn)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.POWER_TO_USER("POWER_TO_USER_COL_0_NAME" "POWER_TO_USER_COL_0_TYPE", "POWER_TO_USER_COL_1_NAME" "POWER_TO_USER_COL_1_TYPE")");
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    return;
}

void delete_from_table_POWER_TO_USER(int sd, MYSQL * conn, const char * u_id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "DELETE FROM user_info.POWER_TO_USER WHERE "POWER_TO_USER_COL_0_NAME" = '%s'", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    return;
}

void insert_into_table_POWER_TO_USER(int sd, MYSQL * conn, const char * u_id, const char * id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO user_info.POWER_TO_USER VALUES('%s', '%s')", u_id, id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);

    return;
}

// u_id의 멀티탭으로부터 30분 이내에 등록 요청이 왔는 지 확인하는 함수
bool check_sync_with_REG(int sd, MYSQL * conn, const char * u_id)
{
    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT * FROM power_info.REG WHERE ("REG_COL_0_NAME" = '%s') AND("REG_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 30 MINUTE) AND NOW())", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(sd, conn, temp_query);
    
    MYSQL_RES *result = Mysql_store_result(sd, conn);
    if(mysql_num_rows(result)==0){
        mysql_free_result(result);
        return false;
    }
    else{
        mysql_free_result(result);
        return true;
    }
}