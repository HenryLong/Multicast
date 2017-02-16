#define LOG_TAG "multicast_server"
#include <utils/Log.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MCAST_PORT 8888
#define MCAST_ADDR "224.224.224.224"
#define MCAST_INTERVAL 5

char databuf[1024] = "Hello all!";
int datalen = sizeof(databuf);

struct in_addr localInterface;

int main(int __unused argc, char __unused **argv) 
{ 

    int s; 
    struct sockaddr_in mcast_addr; 
    s = socket(AF_INET, SOCK_DGRAM, 0); 
    if (s == -1) 
    { 
        perror("socket()"); 
        return -1; 
    } 



    localInterface.s_addr = inet_addr("192.168.43.1");
    if(setsockopt(s, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface)) < 0)
    {
        perror("Setting local interface error");
        exit(1);
    }
    else
        ALOGI("Setting the local interface...OK\n");
  

    memset(&mcast_addr, 0, sizeof(mcast_addr));
    mcast_addr.sin_family = AF_INET;
    mcast_addr.sin_addr.s_addr = inet_addr(MCAST_ADDR);
    mcast_addr.sin_port = htons(MCAST_PORT); 
      
    while(1) { 
        ALOGI("sendto");
        int n = sendto(s, 
                            databuf,
                            datalen,
                            0, 
                            (struct sockaddr*)&mcast_addr, 
                            sizeof(mcast_addr)) ; 
        if( n < 0) 
        { 
            ALOGE("sendto() fail: %d", n); 
            return -2; 
        } 
        sleep(MCAST_INTERVAL);       
    }

    return 0;
}
