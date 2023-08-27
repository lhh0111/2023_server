#include "define.h"
#include "structure.h"
#include "mysql.h"


void create_table_REG(void);
void delete_from_table_REG(const char * u_id);

void insert_into_table_REG(const char * u_id);

void create_table_ENERGY(const char * u_id);

void insert_into_table_ENERGY(const char * u_id, double h2, double h1, double h0, double interval);

void create_table_TEM(const char * u_id);

void insert_into_table_TEM(const char * u_id, double tem);
void create_table_HUM(const char * u_id);

void insert_into_table_HUM(const char * u_id, double hum);

void create_table_DUST(const char * u_id);

void insert_into_table_DUST(const char * u_id, double dust);

void create_table_RELAY_REQ(const char * u_id);

void create_table_ID_PW(void);
bool check_duplicated_id_from_table_ID_PW(const char * id);
void insert_into_table_ID_PW(const char * id, const char * pw);
bool check_valid_id_pw(const char * id, const char * pw);
void create_table_LOGIN_TOKEN(void);

void delete_from_table_LOGIN_TOKEN(const char * id);

void insert_into_table_LOGIN_TOKEN(const char * id, const char * token_buffer);

bool check_valid_token_from_LOGIN_TOKEN(const char * id, const char * token_buffer);
void update_token_from_LOGIN_TOKEN(const char * id);
void create_table_POWER_TO_USER(void);

void delete_from_table_POWER_TO_USER(const char * u_id);

void insert_into_table_POWER_TO_USER(const char * u_id, const char * id);
bool check_sync_with_REG(const char * u_id);
void select_from_table_POWER_TO_USER(const char * id, char **power_list, uint32_t * power_number);

void create_table_POWER_LIST(void);

bool check_valid_u_id(const char * u_id);

void insert_into_table_RELAY_REQ(const char * u_id, const char relay_req);

void get_average_power_month(const char * u_id, struct MessageGResponse * res);

void get_average_power_week(const char * u_id, struct MessageGResponse * res);
void get_average_power_day(const char * u_id, struct MessageGResponse * res);

void get_average_power_now(const char * u_id, struct MessageGResponse * res);
void get_average_tem_month(const char * u_id, struct MessageHResponse * res);
void get_average_tem_week(const char * u_id, struct MessageHResponse * res);
void get_average_tem_day(const char * u_id, struct MessageHResponse * res);

void get_average_tem_now(const char * u_id, struct MessageHResponse * res);
void get_average_hum_month(const char * u_id, struct MessageHResponse * res);
void get_average_hum_week(const char * u_id, struct MessageHResponse * res);

void get_average_hum_day(const char * u_id, struct MessageHResponse * res);
void get_average_hum_now(const char * u_id, struct MessageHResponse * res);
void get_average_dust_month(const char * u_id, struct MessageHResponse * res);

void get_average_dust_week(const char * u_id, struct MessageHResponse * res);

void get_average_dust_day(const char * u_id, struct MessageHResponse * res);

void get_average_dust_now(const char * u_id, struct MessageHResponse * res);

char get_relay_req(const char * u_id);

bool check_user_registered_power(const char * u_id, const char * id);