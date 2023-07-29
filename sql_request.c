#include "sql_request.h"
#include "sql_constant.h"
#include "time.h"
#include <stdlib.h>
#include "sql_basic.h"
#include "safe_m_constant.h"

void _sql_a_req(int sd, struct MessageARequest * req)
{
    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, U_ID_LENGTH);
    u_id[sizeof(u_id) - 1] = '\0';

    int sql_err = SQL_SUCCESS;

    mysql_library_init(0, NULL, NULL);
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);

    create_table_REG(sd, conn);
    delete_from_table_REG(sd, conn, u_id);
    insert_into_table_REG(sd, conn, u_id);
}

/* 요청메시지 B에 있는 내용들을 데이터 베이스에 저장함. U_ID의 RELAY_REQ 테이블에서 릴레이 모듈 제어 예약 정보를 얻어 *relay_status에 저장하는 함수
mysql 작업 중 오류가 발생하면 SQL_ERROR를 반환함. */
void _sql_b_req(int sd, struct MessageBRequest * req, char * relay_req)
{
    char u_id[sizeof(req->u_id) + 1];
    memcpy(u_id, req->u_id, sizeof(req->u_id));
    u_id[sizeof(u_id) - 1] = '\0';


    mysql_library_init(0, NULL, NULL);
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);

    // ENERGY
    create_table_ENERGY(sd, conn, u_id);
    insert_into_table_ENERGY(sd, conn, u_id, req->hole_2_energy, req->hole_1_energy, req->hole_0_energy, req->energy_interval);

    // TEMPERATURE
    create_table_TEM(sd, conn, u_id);
    insert_into_table_TEM(sd, conn, u_id, req->tem);

    // HUM
    create_table_HUM(sd, conn, u_id);
    insert_into_table_HUM(sd, conn, u_id, req->hum);

   // DUST
    create_table_DUST(sd, conn, u_id);
    insert_into_table_DUST(sd, conn, u_id, req->dust);

   
    // get relay_request information
    create_table_RELAY_REQ(sd, conn, u_id);

    MYSQL_RES * result;

    select_from_table_RELAY_REQ(sd, conn, u_id, result);
    MYSQL_ROW row;
    if(mysql_num_rows(result)>0){ // 로컬 api들은 errno을 초기화하지 않음.
        row = mysql_fetch_row(result);
        *relay_req=*(row[0]);
    }
    else{
        *relay_req=RELAY_NO_REQ;
    }
    mysql_free_result(result);


    mysql_close(conn);
    mysql_library_end();
}

int _sql_c_req(int sd, struct MessageCRequest *req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, USER_ID_LENGTH);
    id[sizeof(id) - 1] = '\0';

    char pw[USER_PW_LENGTH + 1];
    memcpy(pw, req->pw, USER_PW_LENGTH);
    pw[sizeof(pw) - 1] = '\0';

    mysql_library_init(0, NULL, NULL);
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);

    create_table_ID_PW(sd, conn);

    bool duplicated = check_duplicated_id_from_table_ID_PW(sd, conn, id);
    char safe_m_err;
    if(duplicated==false){
        insert_into_table_ID_PW(sd, conn, id, pw);
        safe_m_err = SAFE_M_SUCCESS;
    }
    else{
        safe_m_err = SAFE_M_DUPLICATED_ID;
    }

    mysql_close(conn);
    mysql_library_end();

    return safe_m_err;
}

int _sql_d_req(struct MessageDRequest *req, char * token, int token_size)
{
    srand(time(NULL));
    char * temp = token;
    while(temp < token + token_size){
        *temp = rand()%26 + 65; // 알파벳 대문자 저장
        temp++;
    }
    *temp = '\0';

    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, USER_ID_LENGTH);
    id[sizeof(id) - 1] = '\0';

    char pw[USER_PW_LENGTH + 1];
    memcpy(pw, req->pw, USER_PW_LENGTH);
    pw[sizeof(pw) - 1] = '\0';

    char temp_query[300];


    int sql_err = SQL_SUCCESS;

    mysql_library_init(0, NULL, NULL);
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.ID_PW (id CHAR(8) NOT NULL, pw CHAR(16) NOT NULL)");
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.ID_PW WHERE id = '%s' AND pw = '%s'", id, pw);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    MYSQL_RES *result = mysql_store_result(conn);

    if(mysql_num_rows(result)==0){
        mysql_free_result(result);
        
        sql_err = SQL_INVALID_ID_PW;
    }
    else if(mysql_num_rows(result)>0){
        mysql_free_result(result);

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.LOGIN_TOKEN (id CHAR(8) NOT NULL, token CHAR(8) NOT NULL, time TIMESTAMP NOT NULL)");
        temp_query[sizeof(temp_query) - 1] = '\0';
        mysql_query(conn, temp_query);

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1, "DELETE FROM user_info.LOGIN_TOKEN WHERE id = '%s'", id);
        temp_query[sizeof(temp_query) - 1] = '\0';
        mysql_query(conn, temp_query);


        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO user_info.LOGIN_TOKEN VALUES('%s', '%s', now())", id, token);
        temp_query[sizeof(temp_query) - 1] = '\0';
        mysql_query(conn, temp_query);
    }

    
    mysql_close(conn);
    mysql_library_end();

    return sql_err;
}

int _sql_j_err(struct MessageJRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, USER_ID_LENGTH);
    id[sizeof(id) - 1] = '\0';

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, TOKEN_SIZE);
    token[sizeof(token) - 1] = '\0';

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, U_ID_LENGTH);
    u_id[sizeof(u_id) - 1] = '\0';

    int sql_err = SQL_SUCCESS;

    

    mysql_library_init(0, NULL, NULL);
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);

    char temp_query[300];

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.ID_PW (id CHAR(8) NOT NULL, pw CHAR(16) NOT NULL)");
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    memset(temp_query, 0, sizeof(temp_query));
    snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.ID_PW WHERE id = '%s'", id);
    temp_query[sizeof(temp_query) - 1] = '\0';
    mysql_query(conn, temp_query);

    MYSQL_RES *result = mysql_store_result(conn);

    if(mysql_num_rows(result)==0){
        mysql_free_result(result);
        sql_err = SQL_ID_NOT_EXISTS;
    }
    else{
        mysql_free_result(result);

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.LOGIN_TOKEN (id CHAR(8) NOT NULL, token CHAR(8) NOT NULL, time TIMESTAMP NOT NULL)");
        temp_query[sizeof(temp_query) - 1] = '\0';
        mysql_query(conn, temp_query);

        memset(temp_query, 0, sizeof(temp_query));
        snprintf(temp_query, sizeof(temp_query) - 1,"SELECT * FROM user_info.LOGIN_TOKEN WHERE (id = '%s') AND (token = '%s') AND (time BETWEEN DATE_SUB(NOW(), INTERVAL 30 MINUTE) AND NOW())", id, token);
        temp_query[sizeof(temp_query) - 1] = '\0';
        mysql_query(conn, temp_query);

        result = mysql_store_result(conn);

        if(mysql_num_rows(result)==0){
            mysql_free_result(result);
            sql_err = SQL_INVALID_TOKEN;
        }
        else{
            mysql_free_result(result);

            memset(temp_query, 0, sizeof(temp_query));
            snprintf(temp_query, sizeof(temp_query) - 1, "CREATE TABLE IF NOT EXISTS user_info.POWER_TO_USER(uniq_id CHAR(8) NOT NULL, id CHAR(8) NOT NULL)");
            temp_query[sizeof(temp_query) - 1] = '\0';
            mysql_query(conn, temp_query);

            memset(temp_query, 0, sizeof(temp_query));
            snprintf(temp_query, sizeof(temp_query) - 1, "DELETE FROM user_info.POWER_TO_USER WHERE uniq_id = '%s'", u_id);
            temp_query[sizeof(temp_query) - 1] = '\0';
            mysql_query(conn, temp_query);

            memset(temp_query, 0, sizeof(temp_query));
            snprintf(temp_query, sizeof(temp_query) - 1, "INSERT INTO user_info.POWER_TO_USER VALUES('%s', '%s')", u_id, id);
            temp_query[sizeof(temp_query) - 1] = '\0';
            mysql_query(conn, temp_query);
        }
    }
    mysql_free_result(result);
    mysql_close(conn);
    mysql_library_end();

    return sql_err;

}