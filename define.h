#pragma once

#define MYSQL_CONN_HOST "database-1.calntuogtly7.ap-northeast-2.rds.amazonaws.com"
#define MYSQL_CONN_USER "root"
#define MYSQL_CONN_PW "2023project"

#define DATA_BUFFER_LENGTH 10
//
#define SAFE_M_SUCCESS '0'
#define SAFE_M_DUPLICATED_ID '1'
#define SAFE_M_INVALID_ID_PW '2'
#define SAFE_M_ID_NOT_EXISTS '3'
#define SAFE_M_INVALID_TOKEN '4'
#define SAFE_M_U_ID_NOT_EXISTS '5'
#define SAFE_M_NOT_POWER_OWNER '6'
#define SAFE_M_NOT_SYNC_WITH_REG '7'
#define SAFE_M_SQL_REQ_FAIL '8'
//
#define MONTH_TO_SEC 2629800.0
#define WEEK_TO_SEC 604800.0
#define DAY_TO_SEC 86400.0
#define MINUTE_TO_SEC 60.0
//
#define SQL_API_SUCCESS 0
#define SQL_API_FAIL -1

//
#define REG_COL_0_NAME "u_id"
#define REG_COL_0_TYPE "CHAR(" U_ID_LENGTH_S ") NOT NULL"
#define REG_COL_1_NAME "time"
#define REG_COL_1_TYPE "TIMESTAMP NOT NULL"
//
#define ENERGY_COL_0_NAME "hole_2"
#define ENERGY_COL_0_TYPE "DOUBLE NOT NULL"
#define ENERGY_COL_1_NAME "hole_1"
#define ENERGY_COL_1_TYPE "DOUBLE NOT NULL"
#define ENERGY_COL_2_NAME "hole_0"
#define ENERGY_COL_2_TYPE "DOUBLE NOT NULL"
#define ENERGY_COL_3_NAME "time_interval"
#define ENERGY_COL_3_TYPE "DOUBLE NOT NULL"
#define ENERGY_COL_4_NAME "time"
#define ENERGY_COL_4_TYPE "TIMESTAMP NOT NULL"

#define TEM_COL_0_NAME "tem"
#define TEM_COL_0_TYPE "DOUBLE NOT NULL"
#define TEM_COL_1_NAME "time"
#define TEM_COL_1_TYPE "TIMESTAMP NOT NULL"

#define HUM_COL_0_NAME "hum"
#define HUM_COL_0_TYPE "DOUBLE NOT NULL"
#define HUM_COL_1_NAME "time"
#define HUM_COL_1_TYPE "TIMESTAMP NOT NULL"

#define DUST_COL_0_NAME "dust"
#define DUST_COL_0_TYPE "DOUBLE NOT NULL"
#define DUST_COL_1_NAME "time"
#define DUST_COL_1_TYPE "TIMESTAMP NOT NULL"

#define RELAY_REQ_COL_0_NAME "relay_req"
#define RELAY_REQ_COL_0_TYPE "CHAR(1)"

#define ID_PW_COL_0_NAME "id"
#define ID_PW_COL_0_TYPE "CHAR(" USER_ID_LENGTH_S ") NOT NULL"
#define ID_PW_COL_1_NAME "pw"
#define ID_PW_COL_1_TYPE "CHAR(" USER_PW_LENGTH_S ") NOT NULL"

#define LOGIN_TOKEN_COL_0_NAME "id"
#define LOGIN_TOKEN_COL_0_TYPE "CHAR(" USER_ID_LENGTH_S ") NOT NULL"
#define LOGIN_TOKEN_COL_1_NAME "token"
#define LOGIN_TOKEN_COL_1_TYPE "char("TOKEN_SIZE_S") NOT NULL"
#define LOGIN_TOKEN_COL_2_NAME "time"
#define LOGIN_TOKEN_COL_2_TYPE "TIMESTAMP NOT NULL"

#define POWER_TO_USER_COL_0_NAME "u_id"
#define POWER_TO_USER_COL_0_TYPE "CHAR("U_ID_LENGTH_S") NOT NULL"
#define POWER_TO_USER_COL_1_NAME "id"
#define POWER_TO_USER_COL_1_TYPE "CHAR("USER_ID_LENGTH_S") NOT NULL"

#define POWER_LIST_COL_0_NAME "u_id"
#define POWER_LIST_COL_0_TYPE "CHAR("U_ID_LENGTH_S") NOT NULL"
//
#define RESPONSE_SQL_ERROR "Z&"

#define U_ID_LENGTH 8
#define U_ID_LENGTH_S "8"
#define USER_ID_LENGTH 8
#define USER_ID_LENGTH_S "8"
#define USER_ID_MIN_LENGTH 5
#define USER_PW_LENGTH 16
#define USER_PW_LENGTH_S "16"
#define USER_PW_MIN_LENGTH 8

#define TOKEN_SIZE 8
#define TOKEN_SIZE_S "8"

#define MESSAGE_A 0
#define MESSAGE_B 1
#define MESSAGE_C 2
#define MESSAGE_D 3
#define MESSAGE_E 4
#define MESSAGE_F 5
#define MESSAGE_G 6
#define MESSAGE_H 7
#define MESSAGE_I 8
#define MESSAGE_J 9

#define MESSAGE_A_START '0'
#define MESSAGE_A_LAST '&'
#define MESSAGE_B_START '1'
#define MESSAGE_B_LAST '&'
#define MESSAGE_C_START '2'
#define MESSAGE_D_START '3'
#define MESSAGE_E_START '5'
#define MESSAGE_F_START '6'
#define MESSAGE_G_START '7'
#define MESSAGE_H_START '8'
#define MESSAGE_I_START '9'
#define MESSAGE_J_START 'A'
#define MESSAGE_N_START 'E'


#define RELAY_NO_REQ '8'