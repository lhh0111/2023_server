

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include "mysql.h"
#include "structure_message.h"
#include "sql_request.h"
#include "sql_constant.h"
#include "send_response.h"
#include "get_request.h"


#define BUF_SIZE 30





#define INIT_STATE 0
#define A_REQUEST_UNIQUE_ID_STATE 1
#define A_REQUEST_UNIQUE_PW_STATE 2
#define A_REQUEST_USER_ID_STATE 3


#define ERROR_DUPLICATED_ID 1

void error_handling(char* message);
void read_childproc(int sig);

void _get_user_id_pw(int sd, char *user_id_buffer, char *user_pw_buffer);
int _insert_id_pw(const char* id, const char* pw);
int check_message_type_from_stream(int sd);
void protocol_implementation(int sd, int message_type);


int main(int argc, char* argv[])
{
   int serv_sock, clnt_sock;
   struct sockaddr_in serv_adr, clnt_adr;

   pid_t pid;
   socklen_t adr_sz;
   int str_len;
   char buf[BUF_SIZE];
   if(argc != 2)
   {
      printf("Usage : %s <port> \n", argv[0]);
      exit(1);
   }

   signal(SIGCHLD, read_childproc);

   serv_sock = socket(PF_INET, SOCK_STREAM, 0);
   memset(&serv_adr, 0, sizeof(serv_adr));
   serv_adr.sin_family = AF_INET;
   serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
   serv_adr.sin_port = htons(atoi(argv[1]));

   if(bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
      error_handling("bind() error");

   if(listen(serv_sock, 5) == -1)
      error_handling("listen() error");
   while(1)
   {
      adr_sz = sizeof(clnt_adr);
      clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz); // accept 함수 호출한 후에 밑의 fork 함수 호출
                                 // 때문에 이 구문에서 만들어진 소켓(클라이언트의 연결요청 수락과정에서 만들어진) 파일 디스크립터를
                                 // 부모 프로세스와 자식 프로세스가 동시에 하나씩 갖게 됨
      if(clnt_sock == -1)
         continue;
      else
         puts("new client connected....");
      pid = fork();
      if(pid == -1)
      {
         close(clnt_sock);
         continue;
      }
      if(pid == 0)  // 자식 프로세스 실행 영역
                    // 자식 프로세스가 실행되면서 클라이언트에게 에코 서비스가 제공됨.
                    // 그런데 close로 위의 socket을 닫고있는데 이는 자식 프로세스로 서버 소켓의 파일 디스크립터까지 복사되기 때문이다.
      {
         close(serv_sock);  // 자식 영역에서는 서버 소켓을 닫음(필요없는 소켓을 열어둘필요가 없기때문)

         // new code section
         puts("here0");
         int message_type = check_message_type_from_stream(clnt_sock);
         protocol_implementation(clnt_sock, message_type);
         // new code section

         while(true){
            char temp;
            if(read(clnt_sock, &temp, 1)<=0){
               break;
            }
         }                  // 클라이언트 소켓 닫음
         puts("client disconnected...");
         return 0;
      }
      else
         close(clnt_sock);  // accept 함수 호출을 통해 만들어진 소켓의 파일 디스크립터가 자식 프로세스에게 복사되었으니
                            // 서버는 자신이 소유하고있는 파일 디스크립터를 소멸시켜야함.
   }
   close(serv_sock);        // 부모 프로세스에서 모든 클라이언트와의 연결이 끝났으니 서버소켓을 닫아줌
   return 0;
}

void read_childproc(int sig)
{
   pid_t pid;
   int status;
   while((pid = waitpid(-1, &status, WNOHANG))> 0){
      printf("removed proc id : %d \n", pid);
   }
}

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

/* sd가 가리키는 소켓에서 한 바이트를 읽어서 그 값(char 형)을 리턴한다. 소켓에 읽을 수 있는 바이트가 들어올 때까지 블로킹되는 함수. */
// read 반환이 에러인 경우(TCP 연결로가 끊김)를 처리하는 코드 추가 필요


/* sd가 가리키는 스트림(소켓)에 프로토콜의 어떤 메시지가 왔는지를 리턴함. 메시지를 찾을 때까지 블로킹되는 함수.*/
int check_message_type_from_stream(int sd){
      char temp;
      read(sd, &temp, 1);
      if(temp==MESSAGE_A_START){
         return MESSAGE_A;
      }
      else if(temp==MESSAGE_B_START){
         return MESSAGE_B;
      }
      else if(temp==MESSAGE_C_START){
         return MESSAGE_C;
      }
      else if(temp==MESSAGE_D_START){
         return MESSAGE_D;
      }
      else if(temp==MESSAGE_E_START){
         return MESSAGE_E;
      }
      else if(temp==MESSAGE_F_START){
         return MESSAGE_F;
      }
      else ;
}

/* 인자로 소켓 디스크립터, 처리할 메시지 종류를 전해주면, 그 스트림으로부터 그 메시지를 읽고 적절한 처리를 한 뒤 응답메시지를 보냄. */
void protocol_implementation(int sd, int message_type){
   /*
   if(message_type==MESSAGE_A){
 
      char unique_id_buffer[UNIQUE_ID_LENGTH + 1];
      char unique_pw_buffer[UNIQUE_PW_LENGTH + 1];
      char user_id_buffer[USER_ID_LENGTH + 1];

      int index = 0;
      for(;;){
         char temp;
         temp = get_char_from_stream(sd);
         if(temp!=' '){
            unique_id_buffer[index] = temp;
            index++;
         }
         else {
            unique_id_buffer[index] = '\0';
            break;
         }
      }

      index=0;
      for(;;){
         char temp;
         temp = get_char_from_stream(sd);
         if(temp!=' '){
            unique_pw_buffer[index] = temp;
            index++;
         }
         else {
            unique_pw_buffer[index] = '\0';
            break;
         }
      }

      index=0;
      for(;;){
         char temp;
         temp = get_char_from_stream(sd);
         if(temp!=' '){
            user_id_buffer[index] = temp;
            index++;
         }
         else {
            user_id_buffer[index] = '\0';
            break;
         }
      }

      // 디버깅 코드
      printf("unique id: %s \n", unique_id_buffer);
      printf("unique pw: %s \n", unique_pw_buffer);
      printf("user id: %s \n", user_id_buffer);

   }
   */
   if (message_type == MESSAGE_A){
      struct MessageARequest req = {{0}};
      _get_req(sd, &req, sizeof(req));
      int sqlerr = _sql_a_req(&req);
   }
   else if(message_type==MESSAGE_B){
      struct MessageBRequest req={{0}};
      _get_req(sd, &req, sizeof(req));

      char relay_req;
      _sql_b_req(sd, &req, &relay_req);
      _send_b_res(sd, relay_req);
   }
   else if(message_type==MESSAGE_C){
      struct MessageCRequest req={{0}};
      _get_req(sd, &req, sizeof(req));
      char safe_m_err = _sql_c_req(sd, &req);
      _send_c_res(sd, safe_m_err);
   }
   else if(message_type==MESSAGE_D){
      struct MessageDRequest req={{0}};
      _get_req(sd, &req, sizeof(req));
      char token_buffer[TOKEN_SIZE+1] = {0}; // string
      char safe_m_err = _sql_d_req(&req, token_buffer, sizeof(token_buffer) - 1);
      _send_d_res(sd, safe_m_err, token_buffer);
   }
   else if(message_type==MESSAGE_J){
      struct MessageJRequest req={{0}};
      _get_req(sd, &req, sizeof(req));
      char safe_m_err = _sql_j_req(&req);
   }
   /*
   else if(message_type==MESSAGE_C){
      char user_id_buffer[USER_ID_LENGTH + 1];
      char user_pw_buffer[USER_PW_LENGTH + 1];
      _get_user_id_pw(sd, user_id_buffer, user_pw_buffer);
      int err = _insert_id_pw(user_id_buffer, user_pw_buffer);
      if(err==SQL_SUCCESS){
         write(sd, "21", 2);
      }
      else if(err==ERROR_DUPLICATED_ID){
         write(sd, "20", 2);
      }
      return;
   }
   else if(message_type==MESSAGE_D){}
   else if(message_type==MESSAGE_E){}
   else if(message_type==MESSAGE_F){}
   */
  return;
}


/* sd, id 버퍼 시작점, pw 버퍼 시작점을 주면 그 스트림으로부터 유저 id, pw를 읽어 null-terminated로 버퍼에 넣는 함수, 패킷 하나를 전부 읽을 때까지 블로킹됨 */
/*
void _get_user_id_pw(int sd, char *user_id_buffer, char *user_pw_buffer)
{
      int index=0;

      for(;;){
         char temp;
         temp = _get_char_from_stream(sd);
         if(temp!=' '){
            user_id_buffer[index] = temp;
            index++;
         }
         else if(index==8){
            user_id_buffer[index] = '\0';
            break;
         }
         else{
            user_id_buffer[index] = '\0';
            break;
         }
      }
      index=0;
      for(;;){
         char temp;
         temp = _get_char_from_stream(sd);
         if(temp!=' '){
            user_pw_buffer[index] = temp;
            index++;
         }
         else if(index==8){
            user_pw_buffer[index] = '\0';
            break;
         }
         else{
            user_pw_buffer[index] = '\0';
            break;
         }
      }   
      return;
}
*/

/* id, pw가 들어간 버퍼(null-terminated)의 시작점을 받아서 id, pw를 user_info 데이터베이스의 id_pw 테이블에 추가하는 함수
   만약 같은 id가 등록된 경우 ERROR_DUPLICATED_ID를 반환하고, 정상적으로 처리된 경우 SQL_SUCCESS를 반환함. */
// SQL 연결이 도중이 잘못됐을 때를 처리하는 코드 추가 필요

/*
int _insert_id_pw(const char* id, const char* pw)
{
   mysql_library_init(0, NULL, NULL);
   MYSQL *conn = mysql_init(NULL);
   mysql_real_connect(conn, "localhost", "root", "", "user_info", 0, NULL, 0);
   char temp_query[100]={0};
   sprintf(temp_query, "SELECT * FROM id_pw WHERE id = '%s'", id);
   mysql_query(conn, temp_query);
   MYSQL_RES * result = mysql_store_result(conn);
   if(mysql_num_rows(result)!=0){
      return ERROR_DUPLICATED_ID; // 중복된 ID
   }
   sprintf(temp_query, "INSERT INTO id_pw VALUES('%s','%s')", id, pw);
   mysql_query(conn, temp_query);
   mysql_store_result(conn);
   mysql_close(conn);
   mysql_library_end();

   return SQL_SUCCESS;
}

*/