#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <json/json.h>
#include <stdbool.h>
#define BUFSIZE 1024

int main(void){
  int serv_sock;
  int clnt_sock;
  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;
  int clnt_addr_size, str_len;
  char message[BUFSIZE];
  char *words[2];
  int i;
  bool Node1 = false , Node2 = false , Node3 = false;

  // PF = Protocol Family , AF = Address Family
      printf("TCP Server�� ���� Socket�� �����˴ϴ�.\n");
      serv_sock = socket(PF_INET, SOCK_STREAM, 0); // PF_INET : IPv4   SOCK_STREAM : TCP ���
      if(serv_sock == -1)
        printf("socket() error\n");

      memset(&serv_addr, 0, sizeof(serv_addr)); // bind�� ���� �ּ� �Ҵ�
      serv_addr.sin_family = AF_INET; // IPv4 �޼�ü�踦 ����ϹǷ� �׻� AF_INET���� �����Ѵ�.
      serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
      serv_addr.sin_port = htons(9190);

      if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        printf("bind() error\n");

      if(listen(serv_sock, 9999) == -1) // listen(sockfd, backlog) : backlog = ���Ӱ����� Ŭ���̾�Ʈ �ִ��
        printf("listen() error\n");
      printf("������ ����\n");

      clnt_addr_size = sizeof(clnt_addr);

      while(1){
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock == -1)
          printf("accept() error \n");
        printf("���� ��û ����\n");

        while(1){
         if((str_len = read(clnt_sock, message, BUFSIZE)) != 0){
           printf("message form client : %s\n", message);
         }
         else
            break;
            char* token = NULL;
            char str2[] = "[]'`_*?(){}\",.~:;/@";
            int count = 0;
            token = strtok(message, str2);
            while( token != NULL){
                   words[count] = malloc(strlen(token)+1);
                   strcpy( words[count], token );
                   count++;
                   token = strtok(NULL, str2);
           }

           if(!strcmp(words[1],"true") && !strcmp(words[0], "isNode1On")){
                   system("echo 1 > /sys/class/gpio/gpio28/value");
           }
           else if(!strcmp(words[1],"false") && !strcmp(words[0],"isNode1On")){
                   system("echo 0 > /sys/class/gpio/gpio28/value");
           }
           else if(!strcmp(words[1], "true") && !strcmp(words[0], "isNode2On")){
                   system("echo 1 > /sys/class/gpio/gpio38/value");
           }
           else if(!strcmp(words[1], "false") && !strcmp(words[0], "isNode2On")){
                   system("echo 0 > /sys/class/gpio/gpio38/value");
           }
           else if(!strcmp(words[1], "true") && !strcmp(words[0], "isNode2On")){
                   system("echo 1 > /sys/class/gpio/gpio38/value");
           }
           else if(!strcmp(words[1], "false") && !strcmp(words[0], "isNode2On")){
                   system("echo 0 > /sys/class/gpio/gpio38/value");
           }
        }
        close(clnt_sock);
      }
      close(serv_sock);
    return 0;
}