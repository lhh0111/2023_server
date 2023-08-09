#include "define.h"
#include "structure.h"
#include "mysql.h"

int create_table_REG(MYSQL * conn);

int delete_from_table_REG(MYSQL * conn, const char * u_id);

int insert_into_table_REG(MYSQL * conn, const char * u_id);

int create_table_ENERGY(MYSQL * conn, const char * u_id);
int insert_into_table_ENERGY(MYSQL * conn, const char * u_id, double h2, double h1, double h0, double interval);

int  create_table_TEM(MYSQL * conn, const char * u_id);

int insert_into_table_TEM(MYSQL * conn, const char * u_id, double tem);
int create_table_HUM(MYSQL * conn, const char * u_id);

int insert_into_table_HUM(MYSQL * conn, const char * u_id, double hum);
int create_table_DUST(MYSQL * conn, const char * u_id);

int insert_into_table_DUST(MYSQL * conn, const char * u_id, double dust);
int create_table_RELAY_REQ(MYSQL * conn, const char * u_id);

int create_table_ID_PW(MYSQL * conn);

int check_duplicated_id_from_table_ID_PW( MYSQL * conn, const char * id, bool * p_check);


int insert_into_table_ID_PW(MYSQL * conn, const char * id, const char * pw);

int check_valid_id_pw(MYSQL * conn, const char * id, const char * pw, bool * p_check);

int create_table_LOGIN_TOKEN(MYSQL * conn);
int delete_from_table_LOGIN_TOKEN(MYSQL * conn, const char * id);

int insert_into_table_LOGIN_TOKEN(MYSQL * conn, const char * id, const char * token_buffer);

int check_valid_token_from_LOGIN_TOKEN(MYSQL * conn, const char * id, const char * token_buffer, bool * p_check);

int update_token_from_LOGIN_TOKEN(MYSQL * conn, const char * id);

int create_table_POWER_TO_USER(MYSQL * conn);
int delete_from_table_POWER_TO_USER(MYSQL * conn, const char * u_id);
int insert_into_table_POWER_TO_USER(MYSQL * conn, const char * u_id, const char * id);

// u_id의 멀티탭으로부터 30분 이내에 등록 요청이 왔는 지 확인하는 함수
int check_sync_with_REG(MYSQL * conn, const char * u_id, bool * p_check);

int select_from_table_POWER_TO_USER(MYSQL * conn, const char * id, char (**power_list)[U_ID_LENGTH], uint32_t * power_number);

int create_table_POWER_LIST(MYSQL * conn);

int check_valid_u_id(MYSQL * conn, const char * u_id, bool * p_check);

int insert_into_table_RELAY_REQ(MYSQL * conn, const char * u_id, const char relay_req);

int get_average_power_month(MYSQL * conn, const char * u_id, struct MessageGResponse * res);

int get_average_power_week(MYSQL * conn, const char * u_id, struct MessageGResponse * res);

int get_average_power_day(MYSQL * conn, const char * u_id, struct MessageGResponse * res);

int get_average_power_now(MYSQL * conn, const char * u_id, struct MessageGResponse * res);

int get_average_tem_month(MYSQL * conn, const char * u_id, struct MessageHResponse * res);

int get_average_tem_week(MYSQL * conn, const char * u_id, struct MessageHResponse * res);
int get_average_tem_day(MYSQL * conn, const char * u_id, struct MessageHResponse * res);
int get_average_tem_now(MYSQL * conn, const char * u_id, struct MessageHResponse * res);
int get_average_hum_month(MYSQL * conn, const char * u_id, struct MessageHResponse * res);

int get_average_hum_week(MYSQL * conn, const char * u_id, struct MessageHResponse * res);

int get_average_hum_day(MYSQL * conn, const char * u_id, struct MessageHResponse * res);

int get_average_hum_now(MYSQL * conn, const char * u_id, struct MessageHResponse * res);

int get_average_dust_month(MYSQL * conn, const char * u_id, struct MessageHResponse * res);

int get_average_dust_week(MYSQL * conn, const char * u_id, struct MessageHResponse * res);

int get_average_dust_day(MYSQL * conn, const char * u_id, struct MessageHResponse * res);


int get_average_dust_now(MYSQL * conn, const char * u_id, struct MessageHResponse * res);


int get_relay_req(MYSQL * conn, const char * u_id, char * p_relay_req);
