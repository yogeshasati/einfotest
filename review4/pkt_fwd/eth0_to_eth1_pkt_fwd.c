// All #includes 
#include <unistd.h>                                                   
#include <stdio.h>                                                    
#include <sys/socket.h>                                               
#include <stdlib.h>                                                   
#include <netinet/in.h>                                               
#include <string.h>                                                   
#include <stdlib.h>                                                   
#include <string.h>                                                   
#include <sys/types.h>                                                
#include <arpa/inet.h>                                                
#include <sys/ioctl.h>                                                
#include <net/if.h> 
#include <sys/socket.h>
#include <linux/if_packet.h>
#include <net/ethernet.h> /* the L2 protocols */

int main()
{
    int saddr_size , data_size, daddr_size, bytes_sent;
    struct sockaddr_ll saddr, daddr;
	
    unsigned char *buffer= malloc(65535);

    int eth0_sock_raw = socket( AF_PACKET , SOCK_RAW , htons(ETH_P_ALL)) ; //For receiving
    int eth1_sock     = socket( PF_PACKET , SOCK_RAW , IPPROTO_RAW) ;      //For sending

    memset(&saddr, 0, sizeof(struct sockaddr_ll));
	
    saddr.sll_family = AF_PACKET;
    saddr.sll_protocol = htons(ETH_P_ALL);
    saddr.sll_ifindex = if_nametoindex("eth0");
    
	if (bind(eth0_sock_raw, (struct sockaddr*) &saddr, sizeof(saddr)) < 0) {
        perror("eth0 bind failed\n");
        close(eth0_sock_raw);
    }else
	   printf("eth0 bind successfully\n");

    memset(&daddr, 0, sizeof(struct sockaddr_ll));
	
    daddr.sll_family = AF_PACKET;
    daddr.sll_protocol = htons(ETH_P_ALL);
    daddr.sll_ifindex = if_nametoindex("eth1");
	
    if (bind(eth1_sock, (struct sockaddr*) &daddr, sizeof(daddr)) < 0) {
      perror("bind failed\n");
      close(eth1_sock);
    }else
	   printf("eth1 bind successfully\n");
	   
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "eth1");
	
    if (setsockopt(eth1_sock, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        perror("bind to eth1");
        }
		else
		printf("eth1 setsockopt successfull\n");

    while(1)
    {
        saddr_size = sizeof (struct sockaddr);
        daddr_size = sizeof (struct sockaddr);
		memset(buffer, 0, 65536 );
        //Receive a packet
        data_size = recvfrom(eth0_sock_raw , buffer , 65536 , 0 ,(struct sockaddr *) &saddr , (socklen_t*)&saddr_size);

        if(data_size <0 )
        {
            printf("Recvfrom error , failed to get packets\n");
            return 1;
        }
        else{
        printf("Received %d bytes\n",data_size);

        //Huge code to process the packet (optional)

        //Send the same packet out
        bytes_sent = write(eth1_sock,  buffer,  data_size);
        printf("Sent %d bytes\n",bytes_sent);
         if (bytes_sent < 0) {
            perror("sendto");
            exit(1);
         }

        }
    }
    close(eth0_sock_raw);
    return 0;
}