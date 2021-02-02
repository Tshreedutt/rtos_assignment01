#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "netdb.h"
#include "arpa/inet.h"

int main()
{
int socketDescriptor;

struct sockaddr_in serverAddress;
char sendBuffer[1000],recvBuffer[1000];

pid_t cpid;

bzero(&serverAddress,sizeof(serverAddress));

// Creating socket and assigning IP address and port no. 
serverAddress.sin_family=AF_INET;
serverAddress.sin_addr.s_addr=inet_addr("18.222.120.110");
serverAddress.sin_port=htons(5555);

socketDescriptor=socket(AF_INET,SOCK_STREAM,0);

//Server IP address for connection
connect(socketDescriptor,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

cpid=fork();
if(cpid==0)
{
while(1)
{
bzero(&sendBuffer,sizeof(sendBuffer));
printf("\nType ....... ");
fgets(sendBuffer,10000,stdin);
send(socketDescriptor,sendBuffer,strlen(sendBuffer)+1,0);
printf("\nSent!!\n");
}
}
else
{
while(1)
{
bzero(&recvBuffer,sizeof(recvBuffer));
recv(socketDescriptor,recvBuffer,sizeof(recvBuffer),0);
printf("\nSERVER : %s\n",recvBuffer);
}
}
return 0;
}