#pragma once
#define SQL_SUCCESS 0
#define SQL_ERROR 2

#define SQL_DUPLICATED_ID 3
#define SQL_INVALID_ID_PW 4
#define SQL_ID_NOT_EXISTS 5
#define SQL_INVALID_TOKEN 6
#define SQL_NO_RELAY_REQ 7

#define REG_COL_0_NAME "id"
#define REG_COL_0_TYPE "CHAR(" U_ID_LENGTH_S ") NOT NULL"
#define REG_COL_1_NAME "time"
#define REG_COL_1_TYPE "TIMESTAMP NOT NULL"

#define ENERGY_COL_0_NAME "hole_2"
#define ENERGY_COL_0_TYPE "DOUBLE NOT NULL"
#define ENERGY_COL_1_NAME "hole_1"
#define ENERGY_COL_1_TYPE "DOUBLE NOT NULL"
#define ENERGY_COL_2_NAME "hole_0"
#define ENERGY_COL_2_TYPE "DOUBLE NOT NULL"
#define ENERGY_COL_3_NAME "interval"
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