

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <sys/wait.h>
#include "mysql.h"
#include "sql_request.h"
#include "send_response.h"
#include "get_request.h"
#include "unix_wrapper.h"
#include "safe_m_implementation.h"


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
         protocol_implementation(clnt_sock);
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


/* 인자로 소켓 디스크립터, 처리할 메시지 종류를 전해주면, 그 스트림으로부터 그 메시지를 읽고 적절한 처리를 한 뒤 응답메시지를 보냄. */



