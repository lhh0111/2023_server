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

    create_table_POWER_LIST(sd, conn);
    if(check_valid_u_id(sd, conn, u_id)){
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

        select_from_table_RELAY_REQ(sd, conn, u_id, &result);
        MYSQL_ROW row;
        if(mysql_num_rows(result)>0){ // 로컬 api들은 errno을 초기화하지 않음.
            row = mysql_fetch_row(result);
            *relay_req=*(row[0]);
        }
        else{
            *relay_req=RELAY_NO_REQ;
        }
        mysql_free_result(result);
    }

    mysql_close(conn);
    mysql_library_end();

    return;
}

char _sql_c_req(int sd, struct MessageCRequest *req)
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

// *token ~ *(token + token_size - 2) 까지 무작위 A~Z로 채우고 *(token + token_size - 1)을 '\0'으로 채우는 함수 
void set_token(char * token_buffer, int token_buffer_size)
{
    srand(time(NULL));
    char * temp = token_buffer;
    while(temp < token_buffer + token_buffer_size - 1){
        *temp = rand()%26 + 65; // 알파벳 대문자 저장
        temp++;
    }
    *temp = '\0';
    return;
}

char _sql_d_req(int sd, struct MessageDRequest *req, char * token_buffer, int token_buffer_size)
{
    set_token(token_buffer, token_buffer_size); // token_buffer will be null-terminated

    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, USER_ID_LENGTH);
    id[sizeof(id) - 1] = '\0';

    char pw[USER_PW_LENGTH + 1];
    memcpy(pw, req->pw, USER_PW_LENGTH);
    pw[sizeof(pw) - 1] = '\0';

    


    char safe_m_err = SAFE_M_SUCCESS;

    mysql_library_init(0, NULL, NULL);
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);

    create_table_ID_PW(sd, conn);
    

    if(check_valid_id_pw(sd, conn, id, pw)){
        safe_m_err = SAFE_M_SUCCESS;
        
        create_table_LOGIN_TOKEN(sd, conn);

        delete_from_table_LOGIN_TOKEN(sd, conn, id);

        insert_into_table_LOGIN_TOKEN(sd, conn, id, token_buffer);
    }
    else{
        safe_m_err = SAFE_M_INVALID_ID_PW;
    }

    
    mysql_close(conn);
    mysql_library_end();

    return safe_m_err;
}

char _sql_e_req(int sd, struct MessageERequest * req, char (**power_list)[U_ID_LENGTH], uint32_t * power_number)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, USER_ID_LENGTH);
    id[sizeof(id) - 1] = '\0';

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, TOKEN_SIZE);
    token[sizeof(token) - 1] = '\0';

    mysql_library_init(0, NULL, NULL);
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);


    char safe_m_err = SAFE_M_SUCCESS;

    create_table_ID_PW(sd, conn);
    if(check_duplicated_id_from_table_ID_PW(sd, conn, id)){
        create_table_LOGIN_TOKEN(sd, conn);
        if(check_valid_token_from_LOGIN_TOKEN(sd, conn, id, token)){
            create_table_POWER_TO_USER(sd, conn);
            printf("here");
            select_from_table_POWER_TO_USER(sd, conn, id, power_list, power_number);
        }
        else{
            safe_m_err = SAFE_M_INVALID_TOKEN;
        }
    }
    else{
        safe_m_err = SAFE_M_ID_NOT_EXISTS;
    }

    mysql_close(conn);
    mysql_library_end();

    return safe_m_err;

}

char _sql_j_req(int sd, struct MessageJRequest * req)
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

    
    mysql_library_init(0, NULL, NULL);
    MYSQL *conn = mysql_init(NULL);
    mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);

    char temp_query[300];

    create_table_ID_PW(sd, conn);

    bool id_exists = check_duplicated_id_from_table_ID_PW(sd, conn, id);

    char safe_m_err = SAFE_M_SUCCESS;
    if(!id_exists){
        safe_m_err = SAFE_M_ID_NOT_EXISTS;
    }
    else{ // check login token
        create_table_LOGIN_TOKEN(sd,conn);

        if(!check_valid_token_from_LOGIN_TOKEN(sd, conn, id, token)){
            safe_m_err = SAFE_M_INVALID_TOKEN;
        }
        else{
            update_token_from_LOGIN_TOKEN(sd, conn, id);

            create_table_POWER_LIST(sd, conn);
            if(check_valid_u_id(sd, conn, u_id)){
                create_table_REG(sd, conn);
                
                if(check_sync_with_REG(sd, conn, u_id)){
                    create_table_POWER_TO_USER(sd, conn);

                    delete_from_table_POWER_TO_USER(sd, conn, u_id);
                
                    insert_into_table_POWER_TO_USER(sd, conn, u_id, id);
                }
                else{
                    safe_m_err = SAFE_M_NOT_SYNC_WITH_REG;
                }
            }
            else{
                safe_m_err = SAFE_M_U_ID_NOT_EXISTS;
            }
        }
    }

    mysql_close(conn);
    mysql_library_end();

    return safe_m_err;
}