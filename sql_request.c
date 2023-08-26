#include "sql_request.h"
#include "time.h"
#include <stdlib.h>
#include "sql_basic.h"
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include <stdint.h>
#include "sql_wrapper.h"
#include "sql_error.h"

#define CHECK_SQL_API_ERROR() if(get_sql_api_err()!=0){\
                                return SAFE_M_SQL_API_FAIL;\
                            }

char _sql_a_req(struct MessageARequest * req)
{
    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, U_ID_LENGTH);
    u_id[sizeof(u_id) - 1] = '\0';

    create_table_REG();
    CHECK_SQL_API_ERROR();
    delete_from_table_REG(u_id);
    CHECK_SQL_API_ERROR();
    insert_into_table_REG(u_id);
    CHECK_SQL_API_ERROR();

    return SAFE_M_SUCCESS;
}

/* 요청메시지 B에 있는 내용들을 데이터 베이스에 저장함. U_ID의 RELAY_REQ 테이블에서 릴레이 모듈 제어 예약 정보를 얻어 *relay_status에 저장하는 함수
mysql 작업 중 오류가 발생하면 SQL_ERROR를 반환함. */
char _sql_b_req(struct MessageBRequest * req, struct MessageBResponse * res)
{
    char u_id[sizeof(req->u_id) + 1];
    memcpy(u_id, req->u_id, sizeof(req->u_id));
    u_id[sizeof(u_id) - 1] = '\0';

    char safe_m_err = SAFE_M_SUCCESS;
    create_table_POWER_LIST();
    CHECK_SQL_API_ERROR();
    
    if(check_valid_u_id(u_id)){
        CHECK_SQL_API_ERROR();
        // ENERGY
        create_table_ENERGY(u_id);
        CHECK_SQL_API_ERROR();
        insert_into_table_ENERGY(u_id, req->hole_2_energy, req->hole_1_energy, req->hole_0_energy, req->energy_interval);
        CHECK_SQL_API_ERROR();
        // TEMPERATURE
        create_table_TEM(u_id);
        CHECK_SQL_API_ERROR();
        insert_into_table_TEM(u_id, req->tem);
        CHECK_SQL_API_ERROR();

        // HUM
        create_table_HUM( u_id);
        CHECK_SQL_API_ERROR();
        insert_into_table_HUM(u_id, req->hum);
        CHECK_SQL_API_ERROR()

        // DUST
        create_table_DUST(u_id);CHECK_SQL_API_ERROR();
        insert_into_table_DUST(u_id, req->dust);CHECK_SQL_API_ERROR();
        
    
        // get relay_request information
        create_table_RELAY_REQ( u_id);
        CHECK_SQL_API_ERROR();
        res->relay_req = get_relay_req(u_id);
        CHECK_SQL_API_ERROR();

    }
    else{
        safe_m_err = SAFE_M_U_ID_NOT_EXISTS;
    }

    return safe_m_err;
    
}

char _sql_c_req(struct MessageCRequest *req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, USER_ID_LENGTH);
    id[sizeof(id) - 1] = '\0';

    char pw[USER_PW_LENGTH + 1];
    memcpy(pw, req->pw, USER_PW_LENGTH);
    pw[sizeof(pw) - 1] = '\0';

    char safe_m_err = SAFE_M_SUCCESS;

    create_table_ID_PW();
    CHECK_SQL_API_ERROR();
    

    if(check_duplicated_id_from_table_ID_PW(id)){
        CHECK_SQL_API_ERROR();
        safe_m_err = SAFE_M_DUPLICATED_ID;
    }
    else{
        CHECK_SQL_API_ERROR();
        insert_into_table_ID_PW(id, pw);
        CHECK_SQL_API_ERROR();
    }

    return safe_m_err;

    
}

// *token ~ *(token + token_size - 1) 까지 무작위 A~Z로 채우는 함수 
void set_token(char * token_buffer, int token_buffer_size)
{
    srand(time(NULL));
    char * temp = token_buffer;
    while(temp < token_buffer + token_buffer_size){
        *temp = rand()%26 + 65; // 알파벳 대문자 저장
        temp++;
    }
    return;
}

char _sql_d_req(struct MessageDRequest *req, struct MessageDResponse * res)
{
    set_token(res->token, sizeof(res->token)); 

    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    char pw[USER_PW_LENGTH + 1];
    memcpy(pw, req->pw, sizeof(pw) - 1);
    pw[sizeof(pw) - 1] = '\0';

    char token_buffer[sizeof(res->token) + 1];
    memcpy(token_buffer, res->token, sizeof(token_buffer)-1);
    token_buffer[sizeof(token_buffer) - 1] = '\0';

    char safe_m_err = SAFE_M_SUCCESS;
    create_table_ID_PW();
    CHECK_SQL_API_ERROR();
    
    
    if(check_valid_id_pw(id, pw)){
        CHECK_SQL_API_ERROR();
        create_table_LOGIN_TOKEN();
        CHECK_SQL_API_ERROR();
        delete_from_table_LOGIN_TOKEN(id);
        CHECK_SQL_API_ERROR();
        insert_into_table_LOGIN_TOKEN(id, token_buffer);
        CHECK_SQL_API_ERROR();
    }
    else{
        safe_m_err = SAFE_M_INVALID_ID_PW;
    }

    return safe_m_err;
}

char _sql_e_req(struct MessageERequest * req, char **power_list, uint32_t * power_number)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, USER_ID_LENGTH);
    id[sizeof(id) - 1] = '\0';

    char token[TOKEN_SIZE + 1];
    memcpy(token, req->token, TOKEN_SIZE);
    token[sizeof(token) - 1] = '\0';

    create_table_ID_PW();
    CHECK_SQL_API_ERROR();
 


    
    if(check_duplicated_id_from_table_ID_PW(id)){
        CHECK_SQL_API_ERROR();
        create_table_LOGIN_TOKEN();
        CHECK_SQL_API_ERROR();
        if(check_valid_token_from_LOGIN_TOKEN(id, token)){
            CHECK_SQL_API_ERROR();
            update_token_from_LOGIN_TOKEN(id);
            CHECK_SQL_API_ERROR();
            create_table_POWER_TO_USER();
            CHECK_SQL_API_ERROR();
            select_from_table_POWER_TO_USER(id, power_list, power_number);
            CHECK_SQL_API_ERROR();
            return SAFE_M_SUCCESS;
        }
        else{
            return SAFE_M_INVALID_TOKEN;
        }
    }
    else{
        return SAFE_M_ID_NOT_EXISTS;
    }
}

char _sql_j_req(struct MessageJRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    char token_buffer[TOKEN_SIZE + 1];
    memcpy(token_buffer, req->token, sizeof(token_buffer) - 1);
    token_buffer[sizeof(token_buffer) - 1] = '\0';

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    u_id[sizeof(u_id) - 1] = '\0';


    // + id 확인
    create_table_ID_PW();
    CHECK_SQL_API_ERROR();

    bool dup_id = check_duplicated_id_from_table_ID_PW(id);
    CHECK_SQL_API_ERROR();

    if(!dup_id){
        return SAFE_M_ID_NOT_EXISTS;
    }

    // + token 확인
    create_table_LOGIN_TOKEN();
    CHECK_SQL_API_ERROR();
    
    bool valid_token = check_valid_token_from_LOGIN_TOKEN(id, token_buffer);
    CHECK_SQL_API_ERROR();

    if(!valid_token){
        return SAFE_M_INVALID_TOKEN;
    }

    update_token_from_LOGIN_TOKEN(id);
    CHECK_SQL_API_ERROR();

    // + u_id 확인

    create_table_POWER_LIST();
    CHECK_SQL_API_ERROR();
    
    bool valid_u_id=check_valid_u_id(u_id);
    CHECK_SQL_API_ERROR();

    if(!valid_u_id){
        return SAFE_M_U_ID_NOT_EXISTS;
    }

    /*
    create_table_REG();
    CHECK_SQL_API_ERROR();
    bool reg_sync=check_sync_with_REG(u_id);
    CHECK_SQL_API_ERROR();
    */

    bool reg_sync = true;
    if(!reg_sync){
        return SAFE_M_NOT_SYNC_WITH_REG;
    }

    create_table_POWER_TO_USER();
    CHECK_SQL_API_ERROR();
    delete_from_table_POWER_TO_USER(u_id);
    CHECK_SQL_API_ERROR();
    insert_into_table_POWER_TO_USER(u_id, id);
    CHECK_SQL_API_ERROR();

    return SAFE_M_SUCCESS;
}

char _sql_f_req(struct MessageFRequest * req)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    char token_buffer[TOKEN_SIZE + 1];
    memcpy(token_buffer, req->token, sizeof(token_buffer) - 1);
    token_buffer[sizeof(token_buffer) - 1] = '\0';

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    u_id[sizeof(u_id) - 1] = '\0';


    char relay_req = req->relay_req;

    // + id 확인
    create_table_ID_PW();
    CHECK_SQL_API_ERROR();

    bool dup_id = check_duplicated_id_from_table_ID_PW(id);
    CHECK_SQL_API_ERROR();

    if(!dup_id){
        return SAFE_M_ID_NOT_EXISTS;
    }

    // + token 확인
    create_table_LOGIN_TOKEN();
    CHECK_SQL_API_ERROR();
    
    bool valid_token = check_valid_token_from_LOGIN_TOKEN(id, token_buffer);
    CHECK_SQL_API_ERROR();

    if(!valid_token){
        return SAFE_M_INVALID_TOKEN;
    }
    update_token_from_LOGIN_TOKEN(id);
    CHECK_SQL_API_ERROR();

    // + u_id 확인

    create_table_POWER_LIST();
    CHECK_SQL_API_ERROR();
    
    bool valid_u_id=check_valid_u_id(u_id);
    CHECK_SQL_API_ERROR();

    if(!valid_u_id){
        return SAFE_M_U_ID_NOT_EXISTS;
    }

    // + RELAY_REQ 테이블 생성
    create_table_RELAY_REQ(u_id);
    CHECK_SQL_API_ERROR();

    // + RELAY_REQ에 예약 후 리턴
    insert_into_table_RELAY_REQ(u_id, relay_req);
    CHECK_SQL_API_ERROR();

    return SAFE_M_SUCCESS;
}

char _sql_g_req(struct MessageGRequest * req, struct MessageGResponse * res)
{

    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    char token_buffer[TOKEN_SIZE + 1];
    memcpy(token_buffer, req->token, sizeof(token_buffer) - 1);
    token_buffer[sizeof(token_buffer) - 1] = '\0';

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    u_id[sizeof(u_id) - 1] = '\0';

    // + id 확인
    create_table_ID_PW();
    CHECK_SQL_API_ERROR();

    bool dup_id = check_duplicated_id_from_table_ID_PW(id);
    CHECK_SQL_API_ERROR();

    if(!dup_id){
        return SAFE_M_ID_NOT_EXISTS;
    }

    // + token 확인
    create_table_LOGIN_TOKEN();
    CHECK_SQL_API_ERROR();
    
    bool valid_token = check_valid_token_from_LOGIN_TOKEN(id, token_buffer);
    CHECK_SQL_API_ERROR();

    if(!valid_token){
        return SAFE_M_INVALID_TOKEN;
    }
    update_token_from_LOGIN_TOKEN(id);
    CHECK_SQL_API_ERROR();

    // + u_id 확인

    create_table_POWER_LIST();
    CHECK_SQL_API_ERROR();
    
    bool valid_u_id=check_valid_u_id(u_id);
    CHECK_SQL_API_ERROR();

    if(!valid_u_id){
        return SAFE_M_U_ID_NOT_EXISTS;
    }

    // + ENERGY 테이블 생성
    create_table_ENERGY(u_id);
    CHECK_SQL_API_ERROR();
    
    // + ENERGY 테이블에서 날짜로 행 가져와서 특정 기간동안의 평균 전력 구하기
    get_average_power_month(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_power_week(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_power_day(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_power_now(u_id, res);
    CHECK_SQL_API_ERROR();
   
    return SAFE_M_SUCCESS;
}   

char _sql_h_req(struct MessageHRequest * req, struct MessageHResponse * res)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    char token_buffer[TOKEN_SIZE + 1];
    memcpy(token_buffer, req->token, sizeof(token_buffer) - 1);
    token_buffer[sizeof(token_buffer) - 1] = '\0';

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    u_id[sizeof(u_id) - 1] = '\0';

    // + id 확인
    create_table_ID_PW();
    CHECK_SQL_API_ERROR();

    bool dup_id = check_duplicated_id_from_table_ID_PW(id);
    CHECK_SQL_API_ERROR();

    if(!dup_id){
        return SAFE_M_ID_NOT_EXISTS;
    }

    // + token 확인
    create_table_LOGIN_TOKEN();
    CHECK_SQL_API_ERROR();
    
    bool valid_token = check_valid_token_from_LOGIN_TOKEN(id, token_buffer);
    CHECK_SQL_API_ERROR();

    if(!valid_token){
        return SAFE_M_INVALID_TOKEN;
    }
    update_token_from_LOGIN_TOKEN(id);
    CHECK_SQL_API_ERROR();

    // + u_id 확인

    create_table_POWER_LIST();
    CHECK_SQL_API_ERROR();
    
    bool valid_u_id=check_valid_u_id(u_id);
    CHECK_SQL_API_ERROR();

    if(!valid_u_id){
        return SAFE_M_U_ID_NOT_EXISTS;
    }


    // + TEM, HUM, DUST 테이블 생성
    create_table_TEM(u_id);
    CHECK_SQL_API_ERROR();
    create_table_HUM(u_id);
    CHECK_SQL_API_ERROR();
    create_table_DUST(u_id);
    CHECK_SQL_API_ERROR();

    // + TEM, HUM, DUST 테이블에서 날짜로 행 가져와서 1달, 1주, 1일, 현재 평균 구하기
    get_average_tem_month(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_tem_week(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_tem_day(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_tem_now(u_id, res);
    CHECK_SQL_API_ERROR();

    get_average_hum_month(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_hum_week(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_hum_day(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_hum_now(u_id, res);
    CHECK_SQL_API_ERROR();

    get_average_dust_month(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_dust_week(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_dust_day(u_id, res);
    CHECK_SQL_API_ERROR();
    get_average_dust_now(u_id, res);
    CHECK_SQL_API_ERROR();



    return SAFE_M_SUCCESS;
}

char _sql_i_req(struct MessageIRequest * req, struct MessageIResponse * res)
{
    char id[USER_ID_LENGTH + 1];
    memcpy(id, req->id, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';

    char token_buffer[TOKEN_SIZE + 1];
    memcpy(token_buffer, req->token, sizeof(token_buffer) - 1);
    token_buffer[sizeof(token_buffer) - 1] = '\0';

    char u_id[U_ID_LENGTH + 1];
    memcpy(u_id, req->u_id, sizeof(u_id) - 1);
    u_id[sizeof(u_id) - 1] = '\0';

    // + id 확인
    create_table_ID_PW();
    CHECK_SQL_API_ERROR();

    bool dup_id = check_duplicated_id_from_table_ID_PW(id);
    CHECK_SQL_API_ERROR();

    if(!dup_id){
        return SAFE_M_ID_NOT_EXISTS;
    }

    // + token 확인
    create_table_LOGIN_TOKEN();
    CHECK_SQL_API_ERROR();
    
    bool valid_token = check_valid_token_from_LOGIN_TOKEN(id, token_buffer);
    CHECK_SQL_API_ERROR();

    if(!valid_token){
        return SAFE_M_INVALID_TOKEN;
    }
    update_token_from_LOGIN_TOKEN(id);
    CHECK_SQL_API_ERROR();

    // + u_id 확인

    create_table_POWER_LIST();
    CHECK_SQL_API_ERROR();
    
    bool valid_u_id=check_valid_u_id(u_id);
    CHECK_SQL_API_ERROR();

    if(!valid_u_id){
        return SAFE_M_U_ID_NOT_EXISTS;
    }

    create_table_RELAY_REQ(u_id);
    CHECK_SQL_API_ERROR();
    res->relay_req = get_relay_req(u_id);
    CHECK_SQL_API_ERROR();
    
    return SAFE_M_SUCCESS;
}