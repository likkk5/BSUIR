#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/un.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

char recv_buf[1500],send_buf[1024];

// Функция ввода потока, отвечающая за отображение полученной информации
void pthread_function(int sockfd){
	int recvbytes;
	while(1){
		if((recvbytes = recv(sockfd, recv_buf, 1500, 0))==-1){
			perror("recv error");
			exit(1);
		}else{
			recv_buf[recvbytes]='\0';
			printf("%s\n", recv_buf);
		}
	}
}

int main(void){
	pthread_t id;
	int sockfd;
	struct sockaddr_in server_addr;
	// настройки параметров
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12345);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))==-1){
		perror("socket error");
		exit(1);
	}
	// Connect
	if(connect(sockfd, (struct sockaddr*)&server_addr,sizeof(server_addr))==-1){
		perror("connect error");
		exit(1);
	}
	// Введите имя клиента
	char name[20];
	printf("input your name:");
	scanf("%s",name);
	send(sockfd,name,strlen(name),0);
	pthread_create(&id,NULL,(void *)pthread_function,(int *)sockfd);
	while(1){
		gets(send_buf);
		if(send(sockfd,send_buf,strlen(send_buf),0)==-1){
			perror("send error");
			exit(1);
		}
		sleep(1);
	}
	// Закрыть сокет и отменить поток
	close(sockfd);
	pthread_cancel(id);
	return 0;
}