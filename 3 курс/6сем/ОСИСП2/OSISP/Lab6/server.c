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
#include <pthread.h>

#define COUNT 5

int socket_fd[COUNT];

void pthread_function(int client_fd){
	char message[1500];
	char buf[1024];
	int i,recvbytes;
	char name[20];

	recvbytes = recv(client_fd, name, 20, 0);

	name[recvbytes]=':';	
	name[recvbytes+1]='\0';
	
	while(1){
		if((recvbytes = recv(client_fd, buf, 1024, 0))==-1){
			perror("recv error");
			exit(1);
		}
		
		if(recvbytes==0){
			printf("%sbye!\n",name);
			break;		
		}
		
		buf[recvbytes]='\0';
		
		for(i = 0; i < COUNT; ++i){
			if(socket_fd[i]==-1 || socket_fd[i] == client_fd) { 
				continue;
			}
			else {
				message[0]='\0';
				strcat(message,name);
				strcat(message,buf);
				
				if(send(socket_fd[i], message, strlen(message), 0) == -1){
					perror("send error");
					exit(1);
				}			
			}
		}
	}
	
	close(client_fd);
	
	for(i=0;i<COUNT;i++){
		if(socket_fd[i]==client_fd){
			socket_fd[i]=-1;
		}
	}
	pthread_exit(NULL);
}

int main(){

	int i;
	for(i=0;i<COUNT;i++){
		socket_fd[i]=-1;
	}
	pthread_t id;	
	int sockfd,client_fd;
	socklen_t sin_size;
	struct sockaddr_in my_addr;
	struct sockaddr_in remote_addr;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(12345); 
	my_addr.sin_addr.s_addr=INADDR_ANY;
	bzero(&(my_addr.sin_zero),8);
	
	int yes = 1;
	
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
    		perror("setsockopt");
    		exit(1);
	}
	
	if(bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(1);
	}
	
	if(listen(sockfd,10)==-1){
		perror("listen");
		exit(1);
	}
	
	i=0;
	while(1){
		sin_size=sizeof(struct sockaddr_in);
		if((client_fd=accept(sockfd,(struct sockaddr *)&remote_addr,&sin_size))==-1){
			perror("accept");
			exit(1);
		}

		while(socket_fd[i]!=-1)
			i=(i+1)%COUNT;

		socket_fd[i]=client_fd;
		pthread_create(&id,NULL,(void *)pthread_function,(int *)client_fd);
	}
}