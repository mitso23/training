#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>

namespace MulticastServer
{


struct in_addr localInterface;
struct sockaddr_in groupSock;

int sd;
char databuf[1024];
int datalen = sizeof(databuf);

int CreateServer(std::string ipAddress)
{

    /* Create a datagram socket on which to send. */
    sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sd < 0)

    {

        perror("Opening datagram socket error");

        exit(1);

    }
    else
    {
        printf("Opening the datagram socket...OK.\n");
    }

    /* Initialize the group sockaddr structure with a */
    /* group address of 225.1.1.1 and port 5555. */
    memset((char *) &groupSock, 0, sizeof(groupSock));
    groupSock.sin_family = AF_INET;
    groupSock.sin_addr.s_addr = inet_addr("238.1.1.1");
    groupSock.sin_port = htons(8082);

    //Disable loopback so you do not receive your own datagrams.
#if 0
     {
         char loopch = 0;
         if(setsockopt(sd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0)
         {
             perror("Setting IP_MULTICAST_LOOP error");
             close(sd);
             exit(1);
         }
         else
         {
             printf("Disabling the loopback...OK.\n");
         }
     }
#endif

    /* Set local interface for outbound multicast datagrams. */
    /* The IP address specified must be associated with a local, */
    /* multicast capable interface. */
    localInterface.s_addr = inet_addr(ipAddress.c_str());
    if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, (char *) &localInterface, sizeof(localInterface)) < 0)
    {

        perror("Setting local interface error");
        exit(1);
    }
    else
    {
        printf("Setting the local interface...OK\n");
    }

    for(unsigned int i=0; i< 10000; ++i)
    {
        sprintf(databuf, "Multicast test message seq number %i", i);

        /* Send a message to the multicast group specified by the*/
        /* groupSock sockaddr structure. */
        /*int datalen = 1024;*/
        if (sendto(sd, databuf, datalen, 0, (struct sockaddr*) &groupSock, sizeof(groupSock)) < 0)
        {
            perror("Sending datagram message error");
        }
        else
        {
            printf("Sending datagram message...OK\n");
        }

        sleep(1);
    }

    //Try the re-read from the socket if the loopback is not disable
#if 0
     if(read(sd, databuf, datalen) < 0)
     {
         perror("Reading datagram message error\n");
         close(sd);
         exit(1);
     }
     else
     {
         printf("Reading datagram message from client...OK\n");
         printf("The message is: %s\n", databuf);
     }

#endif

    return 0;

}

}
