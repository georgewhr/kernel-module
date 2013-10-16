/*-
 * Copyright 2013 George Wang
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	
 */

//https://dl.dropbox.com/u/98138259/client.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

void *listenThread(void *param);

void *listenThread2(void *param);

char buffer[256];


pthread_t tid; 
pthread_attr_t attr; 

pthread_t tid2; 
//pthread_attr_t attr2; 

socklen_t clilen;

struct sockaddr_in serv_addr, cli_addr;

int newsockfd;
int secondSockfd; 
int sockfd, portno;
int m, n;


int main(int argc, char *argv[])
{

     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     bzero((char *) &serv_addr, sizeof(serv_addr));


     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);


     bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr));
             
     listen(sockfd,5);

     clilen = sizeof(cli_addr);

     pthread_attr_init(&attr);
     pthread_create(&tid,&attr,listenThread,argv[1]);

     pthread_attr_init(&attr);
     pthread_create(&tid2,&attr,listenThread2,argv[1]);

     
     pthread_join(tid,NULL);


     close(newsockfd);
     close(sockfd);
     return 0;
}


void *listenThread(void *param)
{
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    printf("1st Connect Sucessfully\n");

    while(1)
    {
        m = read(newsockfd,buffer,255);
        write(secondSockfd,buffer,strlen(buffer));
        printf("%s\n",buffer);
        bzero(buffer,256);
    }
}

void *listenThread2(void *param)
{
    secondSockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    printf("2nd Connect Sucessfully\n");
   
    while(1)
    {
        n = read(secondSockfd,buffer,255);
        write(newsockfd,buffer,strlen(buffer));
        printf("%s\n",buffer);
        bzero(buffer,256);
    }
}

