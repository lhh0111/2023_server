#include "sql_wrapper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "sql_basic.h"
#include "define.h"
#include "structure.h"

#define MYSQL_QUERY(conn_m, q_m, err_m) if((err_m = Mysql_query(conn_m, q_m))!=SQL_API_SUCCESS){return err_m;} 
#define MYSQL_STORE_RESULT(conn_m, result_m, err_m) if((err_m = Mysql_store_result(conn_m, &result_m))!=SQL_API_SUCCESS){return err_m;}


void create_table_REG(void)
{
    MYSQL * conn = Mysql_init();

    if(Mysql_real_connect(conn)){
        char temp_query[300];
        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS power_info.REG("REG_COL_0_NAME" "REG_COL_0_TYPE", "REG_COL_1_NAME" "REG_COL_1_TYPE")");
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);

    }
    Mysql_close(conn);
}

void delete_from_table_REG(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    

    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1, "DELETE FROM power_info.REG WHERE " REG_COL_0_NAME " = '%s'", u_id);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
}

void insert_into_table_REG(const char * u_id)
{
    MYSQL * conn = Mysql_init();

    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO power_info.REG VALUES('%s', now())", u_id);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
}

void create_table_ENERGY(const char * u_id)
{
    MYSQL * conn = Mysql_init();

    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_ENERGY (" ENERGY_COL_0_NAME " " ENERGY_COL_0_TYPE 
        ", " ENERGY_COL_1_NAME " " ENERGY_COL_1_TYPE ", " ENERGY_COL_2_NAME " " ENERGY_COL_2_TYPE 
        ", " ENERGY_COL_3_NAME " " ENERGY_COL_3_TYPE ", " ENERGY_COL_4_NAME " " ENERGY_COL_4_TYPE")",u_id);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);

        
    }
    Mysql_close(conn);
}

void insert_into_table_ENERGY(const char * u_id, double h2, double h1, double h0, double interval)
{
    MYSQL * conn = Mysql_init();

    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO power_info.%s_ENERGY VALUES(%.2f, %.2f, %.2f, %.2f, now())", u_id, h2, h1, h0, interval);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
}

void create_table_TEM(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_TEM (" TEM_COL_0_NAME " " TEM_COL_0_TYPE ", " TEM_COL_1_NAME " " TEM_COL_1_TYPE ")", u_id); 
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
}

void insert_into_table_TEM(const char * u_id, double tem)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO power_info.%s_TEM VALUES(%.2f, now())", u_id, tem);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
}

void create_table_HUM(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_HUM (" HUM_COL_0_NAME " " HUM_COL_0_TYPE ", " HUM_COL_1_NAME " " HUM_COL_1_TYPE ")", u_id); 
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
}

void insert_into_table_HUM(const char * u_id, double hum)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO power_info.%s_HUM VALUES(%.2f, now())", u_id, hum);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
}

void create_table_DUST(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_DUST (" DUST_COL_0_NAME " " DUST_COL_0_TYPE ", " DUST_COL_1_NAME " " DUST_COL_1_TYPE ")", u_id); 
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
   
}

void insert_into_table_DUST(const char * u_id, double dust)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO power_info.%s_DUST VALUES(%.2f, now())", u_id, dust);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }

    Mysql_close(conn);
}

void create_table_RELAY_REQ(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS power_info.%s_RELAY_REQ (" RELAY_REQ_COL_0_NAME " " RELAY_REQ_COL_0_TYPE ")",u_id);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }

    Mysql_close(conn);
}

void create_table_ID_PW(void)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];
        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"CREATE TABLE IF NOT EXISTS user_info.ID_PW (" ID_PW_COL_0_NAME " " ID_PW_COL_0_TYPE ", " ID_PW_COL_1_NAME " " ID_PW_COL_1_TYPE")");
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }
    Mysql_close(conn);
}

bool check_duplicated_id_from_table_ID_PW(const char * id)
{
    MYSQL * conn = Mysql_init();
    bool check = true;
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.ID_PW WHERE " ID_PW_COL_0_NAME " = '%s'", id); 
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
        
        MYSQL_RES * result = Mysql_store_result(conn);
        if(result != NULL){
            if(mysql_num_rows(result)>0){
                check = true;
            }
            else{
                check = false;
            }
            mysql_free_result(result);
        }
    }
    Mysql_close(conn);
    return check;
}

void insert_into_table_ID_PW(const char * id, const char * pw)
{
    MYSQL * conn = Mysql_init();
    if(Mysql_real_connect(conn)){
        char temp_query[300];

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"INSERT INTO user_info.ID_PW VALUES('%s', '%s')", id, pw);
        temp_query[sizeof(temp_query) - 1] = '\0';
        Mysql_query(conn, temp_query);
    }

    Mysql_close(conn);
}

bool check_valid_id_pw(const char * id, const char * pw)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.ID_PW WHERE "ID_PW_COL_0_NAME" = '%s' AND "ID_PW_COL_1_NAME" = '%s'", id, pw);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES *result = Mysql_store_result(conn);
    bool check = true;
    if(result!=NULL){
        if(mysql_num_rows(result)==0){
            check = false;
        }
        else{
            check = true;
        }
        mysql_free_result(result);
    }
    Mysql_close(conn);
    return check;
}

void create_table_LOGIN_TOKEN(void)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.LOGIN_TOKEN ("LOGIN_TOKEN_COL_0_NAME" "LOGIN_TOKEN_COL_0_TYPE
    ", "LOGIN_TOKEN_COL_1_NAME" "LOGIN_TOKEN_COL_1_TYPE
    ", "LOGIN_TOKEN_COL_2_NAME" "LOGIN_TOKEN_COL_2_TYPE")");
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);
    Mysql_close(conn);
}

void delete_from_table_LOGIN_TOKEN(const char * id)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "DELETE FROM user_info.LOGIN_TOKEN WHERE "LOGIN_TOKEN_COL_0_NAME" = '%s'", id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);
    Mysql_close(conn);
}

// token_buffer는 null-terminated여야 한다.
void insert_into_table_LOGIN_TOKEN(const char * id, const char * token_buffer)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO user_info.LOGIN_TOKEN VALUES('%s', '%s', now())", id, token_buffer);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);Mysql_close(conn);
}


bool check_valid_token_from_LOGIN_TOKEN(const char * id, const char * token_buffer)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.LOGIN_TOKEN WHERE ("LOGIN_TOKEN_COL_0_NAME" = '%s') AND ("LOGIN_TOKEN_COL_1_NAME" = '%s') AND ("LOGIN_TOKEN_COL_2_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 30 MINUTE) AND NOW())", id, token_buffer);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES *result = Mysql_store_result(conn);
    bool check = true;

    if(result!=NULL){
        if(mysql_num_rows(result)==0){
            check = false;
        }
        else{
            check = true;
        }
    }
    
    mysql_free_result(result);
    Mysql_close(conn);
    return check;
}

void update_token_from_LOGIN_TOKEN(const char * id)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"UPDATE user_info.LOGIN_TOKEN SET "LOGIN_TOKEN_COL_2_NAME"=now() WHERE "LOGIN_TOKEN_COL_0_NAME"='%s'", id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);Mysql_close(conn);
}

void create_table_POWER_TO_USER(void)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.POWER_TO_USER("POWER_TO_USER_COL_0_NAME" "POWER_TO_USER_COL_0_TYPE", "POWER_TO_USER_COL_1_NAME" "POWER_TO_USER_COL_1_TYPE")");
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);Mysql_close(conn);
}

void delete_from_table_POWER_TO_USER(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "DELETE FROM user_info.POWER_TO_USER WHERE "POWER_TO_USER_COL_0_NAME" = '%s'", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);
    Mysql_close(conn);
}

void insert_into_table_POWER_TO_USER(const char * u_id, const char * id)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO user_info.POWER_TO_USER VALUES('%s', '%s')", u_id, id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);Mysql_close(conn);
}

// u_id의 멀티탭으로부터 30분 이내에 등록 요청이 왔는 지 확인하는 함수
bool check_sync_with_REG(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT * FROM power_info.REG WHERE ("REG_COL_0_NAME" = '%s') AND("REG_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 30 MINUTE) AND NOW())", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);
    
    MYSQL_RES *result = Mysql_store_result(conn);
    bool check = true;
    if(result!=NULL){
        if(mysql_num_rows(result)==0){
            check = false;
        }
        else{
            check= true;
        }
        mysql_free_result(result);
    }
    
    Mysql_close(conn);
    return check;
}

void select_from_table_POWER_TO_USER(const char * id, char **power_list, uint32_t * power_number)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "POWER_TO_USER_COL_0_NAME" FROM user_info.POWER_TO_USER WHERE "POWER_TO_USER_COL_1_NAME" = '%s'", id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        *power_number = mysql_num_rows(result); // 멀티탭 개수
        *power_list = (char *) malloc((*power_number) * U_ID_LENGTH);

        uint32_t count = 0;
        while(count < (*power_number)){
            MYSQL_ROW row = mysql_fetch_row(result);
            memcpy((*power_list) + count * U_ID_LENGTH, row[0], U_ID_LENGTH);
            count++;
        }

        mysql_free_result(result);
    }

    Mysql_close(conn);
}

void create_table_POWER_LIST(void)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS power_info.POWER_LIST("POWER_LIST_COL_0_NAME" "POWER_LIST_COL_0_TYPE")");
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);
    Mysql_close(conn);

}

bool check_valid_u_id(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT * FROM power_info.POWER_LIST WHERE "POWER_LIST_COL_0_NAME" ='%s'", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);
    
    MYSQL_RES *result = Mysql_store_result(conn);
    bool check = true;
    if(result!=NULL){
        if(mysql_num_rows(result)==0){
            check = false;
        }
        else{
            check = true;
        }
        mysql_free_result(result);
    }
    
    Mysql_close(conn);
    return check;
}

void insert_into_table_RELAY_REQ(const char * u_id, const char relay_req)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO power_info.%s_RELAY_REQ VALUES('%c')", u_id, relay_req);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);
    Mysql_close(conn);
}

void get_average_power_month(const char * u_id, struct MessageGResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "ENERGY_COL_0_NAME", "ENERGY_COL_1_NAME", "ENERGY_COL_2_NAME" FROM power_info.%s_ENERGY WHERE "
    ENERGY_COL_4_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 MONTH) AND NOW()", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        double hole_2 = 0.0;double hole_1 = 0.0;double hole_0 = 0.0;
        MYSQL_ROW row = NULL;
        while((row = mysql_fetch_row(result))   !=  NULL){
            char * temp;
            hole_2 += strtod(row[0], &temp);
            hole_1 += strtod(row[1], &temp);
            hole_0 += strtod(row[2], &temp);
        }
        mysql_free_result(result);
        res->hole_2_month = hole_2/MONTH_TO_SEC; // 평균전력 얻기
        res->hole_1_month = hole_1/MONTH_TO_SEC;
        res->hole_0_month = hole_0/MONTH_TO_SEC;
    }
    
    Mysql_close(conn);
}

void get_average_power_week(const char * u_id, struct MessageGResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "ENERGY_COL_0_NAME", "ENERGY_COL_1_NAME", "ENERGY_COL_2_NAME" FROM power_info.%s_ENERGY WHERE "
    ENERGY_COL_4_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 WEEK) AND NOW()", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        double hole_2 = 0.0;double hole_1 = 0.0;double hole_0 = 0.0;
        MYSQL_ROW row = NULL;
        while((row = mysql_fetch_row(result))   !=  NULL){
            char * temp;
            hole_2 += strtod(row[0], &temp);
            hole_1 += strtod(row[1], &temp);
            hole_0 += strtod(row[2], &temp);
        }
        mysql_free_result(result);
        res->hole_2_month = hole_2/WEEK_TO_SEC; // 평균전력 얻기
        res->hole_1_month = hole_1/WEEK_TO_SEC;
        res->hole_0_month = hole_0/WEEK_TO_SEC;
    }
    
    Mysql_close(conn);
}

void get_average_power_day(const char * u_id, struct MessageGResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "ENERGY_COL_0_NAME", "ENERGY_COL_1_NAME", "ENERGY_COL_2_NAME" FROM power_info.%s_ENERGY WHERE "
    ENERGY_COL_4_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 DAY) AND NOW()", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        double hole_2 = 0.0;double hole_1 = 0.0;double hole_0 = 0.0;
        MYSQL_ROW row = NULL;
        while((row = mysql_fetch_row(result))   !=  NULL){
            char * temp;
            hole_2 += strtod(row[0], &temp);
            hole_1 += strtod(row[1], &temp);
            hole_0 += strtod(row[2], &temp);
        }
        mysql_free_result(result);
        res->hole_2_month = hole_2/DAY_TO_SEC; // 평균전력 얻기
        res->hole_1_month = hole_1/DAY_TO_SEC;
        res->hole_0_month = hole_0/DAY_TO_SEC;
    }
    
    Mysql_close(conn);
}

void get_average_power_now(const char * u_id, struct MessageGResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "ENERGY_COL_0_NAME", "ENERGY_COL_1_NAME", "ENERGY_COL_2_NAME" FROM power_info.%s_ENERGY WHERE "
    ENERGY_COL_4_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 MINUTE) AND NOW()", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        double hole_2 = 0.0;double hole_1 = 0.0;double hole_0 = 0.0;
        MYSQL_ROW row = NULL;
        while((row = mysql_fetch_row(result))   !=  NULL){
            char * temp;
            hole_2 += strtod(row[0], &temp);
            hole_1 += strtod(row[1], &temp);
            hole_0 += strtod(row[2], &temp);
        }
        mysql_free_result(result);
        res->hole_2_month = hole_2/MINUTE_TO_SEC; // 평균전력 얻기
        res->hole_1_month = hole_1/MINUTE_TO_SEC;
        res->hole_0_month = hole_0/MINUTE_TO_SEC;
    }
    
    Mysql_close(conn);
}

void get_average_tem_month(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "TEM_COL_0_NAME" FROM power_info.%s_TEM WHERE "
    TEM_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 MONTH) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){

        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double month = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                month += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->tem_month = month/(double)num_rows; // 평균 얻기

        }
        else{
            mysql_free_result(result);
            res->tem_month = 0.0;
        }
    }

    Mysql_close(conn);
}

void get_average_tem_week(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "TEM_COL_0_NAME" FROM power_info.%s_TEM WHERE "
    TEM_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 WEEK) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){

        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double week = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                week += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->tem_week = week/(double)num_rows; // 평균 얻기

        }
        else{
            mysql_free_result(result);
            res->tem_week = 0.0;


        }
    }
    Mysql_close(conn);
}

void get_average_tem_day(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "TEM_COL_0_NAME" FROM power_info.%s_TEM WHERE "
    TEM_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 DAY) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){

    
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double day = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                day += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->tem_day = day/(double)num_rows; // 평균 얻기


        }
        else{
            mysql_free_result(result);
            res->tem_day = 0.0;


        }
    }

    Mysql_close(conn);
}

void get_average_tem_now(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "TEM_COL_0_NAME" FROM power_info.%s_TEM WHERE "
    TEM_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 MINUTE) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result;
    if(result != NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double now = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                now += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->tem_now = now/(double)num_rows; // 평균 얻기


        }
        else{
            mysql_free_result(result);
            res->tem_now = 0.0;
        }
    }
    Mysql_close(conn);
}

void get_average_hum_month(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "HUM_COL_0_NAME" FROM power_info.%s_HUM WHERE "
    HUM_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 MONTH) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double month = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                month += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->hum_month = month/(double)num_rows; // 평균 얻기


        }
        else{
            mysql_free_result(result);
            res->hum_month = 0.0;

        }
    }
    Mysql_close(conn);
}

void get_average_hum_week(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "HUM_COL_0_NAME" FROM power_info.%s_HUM WHERE "
    HUM_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 WEEK) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double week = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                week += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->hum_week = week/(double)num_rows; // 평균 얻기
        }
        else{
            mysql_free_result(result);
            res->hum_week = 0.0;
        }
    }
    Mysql_close(conn);
}

void get_average_hum_day(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "HUM_COL_0_NAME" FROM power_info.%s_HUM WHERE "
    HUM_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 DAY) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double day = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                day += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->hum_day = day/(double)num_rows; // 평균 얻기


        }
        else{
            mysql_free_result(result);
            res->hum_day = 0.0;


        }
    }
    Mysql_close(conn);
}

void get_average_hum_now(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "HUM_COL_0_NAME" FROM power_info.%s_HUM WHERE "
    HUM_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 MINUTE) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double now = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                now += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->hum_now = now/(double)num_rows; // 평균 얻기


        }
        else{
            mysql_free_result(result);
            res->hum_now = 0.0;


        }
    }

    Mysql_close(conn);
}

<<<<<<< HEAD
void get_average_dust_month(const char * u_id, struct MessageHResponse * res)
=======

int get_average_dust_month(MYSQL * conn, const char * u_id, struct MessageHResponse * res)
>>>>>>> 53799736b7b2b6484fd0410ab51d390332008adb
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "DUST_COL_0_NAME" FROM power_info.%s_DUST WHERE "
    DUST_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 MONTH) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double month = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                month += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->dust_month = month/(double)num_rows; // 평균 얻기


        }
        else{
            mysql_free_result(result);
            res->dust_month = 0.0;


        }
    }
    Mysql_close(conn);  
}

void get_average_dust_week(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "DUST_COL_0_NAME" FROM power_info.%s_DUST WHERE "
    DUST_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 WEEK) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result != NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double week = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                week += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->dust_week = week/(double)num_rows; // 평균 얻기

        }
        else{
            mysql_free_result(result);
            res->dust_week = 0.0;

        }
    }
    Mysql_close(conn);
}

void get_average_dust_day(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "DUST_COL_0_NAME" FROM power_info.%s_DUST WHERE "
    DUST_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 DAY) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double day = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                day += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->dust_day = day/(double)num_rows; // 평균 얻기

        }
        else{
            mysql_free_result(result);
            res->dust_day = 0.0;

        }
    }
    Mysql_close(conn);
    
}

void get_average_dust_now(const char * u_id, struct MessageHResponse * res)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "SELECT "DUST_COL_0_NAME" FROM power_info.%s_DUST WHERE "
    DUST_COL_1_NAME" BETWEEN DATE_SUB(NOW(), INTERVAL 1 MINUTE) AND NOW()", u_id);

    temp_query[sizeof(temp_query) - 1] = '\0';
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    if(result!=NULL){
        uint64_t num_rows = 0;
        if((num_rows = mysql_num_rows(result))!=0){
            double now = 0.0;
            MYSQL_ROW row = NULL;
            while((row = mysql_fetch_row(result))   !=  NULL){
                char * temp;
                now += strtod(row[0], &temp);
            }
            mysql_free_result(result);

            res->dust_now = now/(double)num_rows; // 평균 얻기


<<<<<<< HEAD
        }
        else{
            mysql_free_result(result);
            res->dust_month = 0.0;
=======
    }
    else{
        mysql_free_result(result);
        res->dust_now = 0.0;
>>>>>>> 53799736b7b2b6484fd0410ab51d390332008adb


        }
    }
    Mysql_close(conn);
}

char get_relay_req(const char * u_id)
{
    MYSQL * conn = Mysql_init();
    conn = Mysql_real_connect(conn);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM power_info.%s_RELAY_REQ", u_id);
    temp_query[sizeof(temp_query) - 1] = '\0';
<<<<<<< HEAD
    Mysql_query(conn, temp_query);

    MYSQL_RES * result = Mysql_store_result(conn);
    char relay_req = RELAY_NO_REQ;
    if(result != NULL){
        int num_rows = 0;
        if((num_rows = mysql_num_rows(result))  !=  0){
            MYSQL_ROW row;
            while((row = mysql_fetch_row(result))!=NULL){
                relay_req = row[0][0];
            }
        }
    }
    Mysql_close(conn);
    return relay_req;
=======
    int err;
    MYSQL_QUERY(conn, temp_query, err);

    MYSQL_RES * result;
    MYSQL_STORE_RESULT(conn, result, err);
    int num_rows = 0;
    if((num_rows = mysql_num_rows(result))  !=  0){
        MYSQL_ROW row;
        while((row = mysql_fetch_row(result))!=NULL){
            *p_relay_req = row[0][0];
        }
    }
    else{
        *p_relay_req = RELAY_NO_REQ;
    }
  
    return err;
>>>>>>> 53799736b7b2b6484fd0410ab51d390332008adb
}