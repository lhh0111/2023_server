#include "define.h"
#include "structure.h"
#include <stdint.h>
#include <stdlib.h>
#include "sql_request.h"
#include "send_response.h"
#include "get_request.h"
#include "unix_wrapper.h"
#include "validation_check.h"
#include <stdio.h>

static char check_message_type_from_stream(int sd){
      char temp;
      Read(sd, &temp, 1);
      return temp;
}

void protocol_implementation(int sd){
   char message_type = check_message_type_from_stream(sd);
   if (message_type == MESSAGE_A_START){
      struct MessageARequest req = {{0}};
      _get_req(sd, &req, sizeof(req));


      struct MessageAResponse res;
      res.safe_m_err = _sql_a_req(&req);
      res.type = message_type;
      res.end = MESSAGE_A_LAST;
      _send_res(sd, &res, sizeof(res));
      printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
   }
   else if(message_type==MESSAGE_B_START){
      struct MessageBRequest req={{0}};
      _get_req(sd, &req, sizeof(req));
      struct MessageBResponse res;
      res.safe_m_err = _sql_b_req(&req, &res);
      res.type = message_type;
      res.end = MESSAGE_B_LAST;
      _send_res(sd, &res, sizeof(res));
      printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
   }
   else if(message_type==MESSAGE_C_START){
      struct MessageCRequest req={{0}};
      _get_req(sd, &req, sizeof(req));
      if(check_req_c_validation(&req)){
         struct MessageCResponse res;
         res.safe_m_err = _sql_c_req(&req);
         res.type = message_type;
         _send_res(sd, &res, sizeof(res));
         printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
      }
      else{
         printf("m_type : %c, validation check failed..\r\n", message_type);
      }
   }
   else if(message_type==MESSAGE_D_START){
      struct MessageDRequest req={{0}};
      _get_req(sd, &req, sizeof(req));
      if(check_req_d_validation(&req)){
         struct MessageDResponse res;
         res.safe_m_err = _sql_d_req(&req, &res);
         res.type = message_type;
         _send_res(sd, &res, sizeof(res));
         printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
      }
      else{
         printf("m_type : %c, validation check failed..\r\n", message_type);
      }

   }
   else if(message_type==MESSAGE_E_START){
      struct MessageERequest req;
      _get_req(sd, &req, sizeof(req));
      if(check_req_e_validation(&req)){
         char (*power_list)[8] = NULL;
         struct MessageEResponse res;
         uint32_t power_number = 0;
         res.safe_m_err = _sql_e_req(&req, &power_list, &power_number);
         res.type = message_type;
         res.power_number = power_number;
         _send_res(sd, &res, sizeof(res));
         _send_res(sd, power_list, power_number * U_ID_LENGTH);
         free(power_list);
         printf("m_type : %c, safe_m_err : %d\r\n, power_number : %d", message_type, res.safe_m_err, res.power_number);
      }
      else{
         printf("m_type : %c, validation check failed..\r\n", message_type);
      }
   }
   else if(message_type==MESSAGE_F_START){
      struct MessageFRequest req;
      _get_req(sd, &req, sizeof(req));
      if(check_req_f_validation(&req)){
         struct MessageFResponse res;
         res.safe_m_err = _sql_f_req(&req);
         res.type = message_type;
         _send_res(sd, &res, sizeof(res));
         printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
      }
      else{
         printf("m_type : %c, validation check failed..\r\n", message_type);
      }
   }
   else if(message_type==MESSAGE_G_START){
      struct MessageGRequest req;
      _get_req(sd, &req, sizeof(req));
      if(check_req_g_validation(&req)){
         struct MessageGResponse res;
         res.safe_m_err = _sql_g_req(&req, &res);
         res.type = message_type;
         _send_res(sd, &res, sizeof(res));
         printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
      }
      else{
         printf("m_type : %c, validation check failed..\r\n", message_type);
      }
   }
   else if(message_type==MESSAGE_H_START){
      struct MessageHRequest req;
      _get_req(sd, &req, sizeof(req));
      if(check_req_h_validation(&req)){
         struct MessageHResponse res;
         res.safe_m_err = _sql_h_req(&req, &res);
         res.type = message_type;
         _send_res(sd, &res, sizeof(res));
         printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
      }
      else{
         printf("m_type : %c, validation check failed..\r\n", message_type);
      }
   }
   else if(message_type==MESSAGE_I_START){
      struct MessageIRequest req;
      _get_req(sd, &req, sizeof(req));
      if(check_req_i_validation(&req)){
         struct MessageIResponse res;
         res.safe_m_err = _sql_i_req(&req, &res);
         res.type = message_type;
         _send_res(sd, &res, sizeof(res));
         printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
      }
      else{
         printf("m_type : %c, validation check failed..\r\n", message_type);
      }
      
   }
   else if(message_type==MESSAGE_J_START){
      struct MessageJRequest req={{0}};
      _get_req(sd, &req, sizeof(req));
      if(check_req_j_validation(&req)){
         struct MessageJResponse res;
         res.safe_m_err = _sql_j_req(&req);
         res.start = message_type;
         _send_res(sd, &res, sizeof(res));
         printf("m_type : %c, safe_m_err : %d\r\n", message_type, res.safe_m_err);
      }
      else{
         printf("m_type : %c, validation check failed..\r\n", message_type);
      }
   }
   return;
}