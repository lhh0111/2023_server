#pragma once
#include "define.h"
#include "structure.h"
#include <stdint.h>

#include "sql_request.h"
#include "time.h"
#include <stdlib.h>
#include "sql_basic.h"
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include <stdint.h>
#include "sql_wrapper.h"

char _sql_a_req(struct MessageARequest * req);

/* 요청메시지 B에 있는 내용들을 데이터 베이스에 저장함. U_ID의 RELAY_REQ 테이블에서 릴레이 모듈 제어 예약 정보를 얻어 *relay_status에 저장하는 함수
mysql 작업 중 오류가 발생하면 SQL_ERROR를 반환함. */
char _sql_b_req(struct MessageBRequest * req, struct MessageBResponse * res);

char _sql_c_req(struct MessageCRequest *req);


char _sql_d_req(struct MessageDRequest *req, struct MessageDResponse * res);

char _sql_e_req(struct MessageERequest * req, char **power_list, uint32_t * power_number);
char _sql_j_req(struct MessageJRequest * req);

char _sql_f_req(struct MessageFRequest * req);

char _sql_g_req(struct MessageGRequest * req, struct MessageGResponse * res);

char _sql_h_req(struct MessageHRequest * req, struct MessageHResponse * res);

char _sql_i_req(struct MessageIRequest * req, struct MessageIResponse * res);
