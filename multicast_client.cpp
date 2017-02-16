#define LOG_TAG "multicast_client"
#include <utils/Log.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MCAST_PORT 8888
#define MCAST_ADDR "224.224.224.224"
#define MCAST_INTERVAL 5
#define BUFF_SIZE 256 

struct ip_mreq mreq;

int datalen;
int databuf[1024];
int main(int __unused  argc, char __unused  **argv) 
{
    int s; 
    struct sockaddr_in local_addr; 
    int err = -1; 
      
    s = socket(AF_INET, SOCK_DGRAM, 0); 
    if (s == -1) 
    { 
        perror("socket()"); 
        return -1; 
    } 
      
   
    int reuse = 1;
    if(setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
    {
        perror("Setting SO_REUSEADDR error");
        close(s);
        exit(1);
    }
    else
        ALOGI("Setting SO_REUSEADDR...OK.\n");
      


    memset(&local_addr, 0, sizeof(local_addr)); 
    local_addr.sin_family = AF_INET; 
    local_addr.sin_addr.s_addr = INADDR_ANY; 
    local_addr.sin_port = htons(MCAST_PORT); 
      
    err = bind(s,(struct sockaddr*)&local_addr, sizeof(local_addr)) ; 
    if(err < 0) 
    { 
        ALOGE("bind()"); 
        return -2; 
    } else
        ALOGI("bind ...OK.\n");


   
    mreq.imr_multiaddr.s_addr = inet_addr(MCAST_ADDR); 
    mreq.imr_interface.s_addr = INADDR_ANY;                                                  
    err = setsockopt(s, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mreq, sizeof (mreq)); 
    if (err < 0) 
    { 
        ALOGE("setsockopt():IP_ADD_MEMBERSHIP %d", err); 
        return -4; 
    } else
        ALOGI("IP_ADD_MEMBERSHIP ...OK.\n");
      
    socklen_t addr_len = sizeof(local_addr);
    char buff[BUFF_SIZE]; 
    int n = 0; 

    while(1)
    { 
        addr_len = sizeof(local_addr); 
        memset(buff, 0, BUFF_SIZE);        
        ALOGI("recvfrom()");
        n = recvfrom(s, buff, BUFF_SIZE, 0,(struct sockaddr*)&local_addr, 
        &addr_len); 
        if( n== -1) 
        { 
            perror("recvfrom()"); 
        } 

        ALOGI("Recv message from server:%s\n", buff); 
    } 
    return 0; 
}
