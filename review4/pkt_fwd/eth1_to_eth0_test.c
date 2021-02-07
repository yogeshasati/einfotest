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
    //struct sockaddr_ll saddr, daddr;
    struct sockaddr_in saddr, daddr, peer_addr;
    int eth1_sock;
    int eth0_sock;
	
    unsigned char *buffer= malloc(65535);

    if ((eth1_sock = socket( AF_INET , SOCK_STREAM , 0)) < 0)	//For sending
    {
	perror("eth1 socket failed");
	return (1);
    }
	
    if ((eth0_sock = socket( AF_INET , SOCK_STREAM , 0)) < 0)   //For receiving
    {
	perror("eth0 socket failed");
	return (1);
    }
	
    memset(&saddr, 0, sizeof(struct sockaddr_in));
	
    saddr.sin_family = AF_INET;
    //saddr.sin_addr.s_addr = inet_addr("192.168.1.111");
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(12000);
	
    //if (bind(eth1_sock, (struct sockaddr_in*) &saddr, sizeof(saddr)) < 0)
    if (bind(eth1_sock, (struct sockaddri_in*) &saddr, sizeof(saddr)) < 0)
    {
        perror("eth1 bind failed\n");
        close(eth1_sock);
    }
    else
    {
       printf("eth1 bind successfully\n");
    }

    memset(&daddr, 0, sizeof(struct sockaddr_in));
	
    daddr.sin_family = AF_INET;
    //daddr.sin_addr.s_addr = inet_addr("192.168.1.112");
    daddr.sin_addr.s_addr = htonl(INADDR_ANY);
    daddr.sin_port = htons(12010);
	
    if (bind(eth0_sock, (struct sockaddr_in*) &daddr, sizeof(daddr)) < 0)
    {
      perror("eth0 bind failed\n");
      close(eth0_sock);
    }
    else
    {
      printf("eth0 bind successfully\n");
    }
	
    //Listening on eth1
    if (listen(eth1_sock, 3) == 0)
    {
	printf("listening on eth1...\n");
    }
    else
    {
	perror("eth1 unable to listen\n");
    }
	
    //accept the connection
    char ip[INET_ADDRSTRLEN]; //to store the client IP address
    socklen_t addr_size;
    int acc_eth1;

    addr_size = sizeof(struct sockaddr_in);
	
    if ((acc_eth1 = accept(eth1_sock, (struct sockaddr_in*) &peer_addr, &addr_size)) < 0)
    {
	perror("eth1 accept failed");
	return (1);
    }

    inet_ntop(AF_INET, &(peer_addr.sin_addr), ip, INET_ADDRSTRLEN);
    printf("Connection established with IP: %s, and port: %d",ip,ntohs(peer_addr.sin_port));
    
   // memset(&daddr, 0, sizeof(struct sockaddr_in));
	
    // daddr.sin_family = AF_INET;
    // daddr.sin_addr.s_addr = inet_addr("192.168.1.112");
    // daddr.sin_port = htons(12010);
	
    // if (bind(eth0_sock, (struct sockaddr*) &daddr, sizeof(daddr)) < 0)
	// {
      // perror("eth0 bind failed\n");
      // close(eth0_sock);
    // }
	// else
	// {
	   // printf("eth0 bind successfully\n");
	// }
		
    // struct ifreq ifr;
    // memset(&ifr, 0, sizeof(ifr));
    // snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "eth1");
	
    // if (setsockopt(eth1_sock, SOL_SOCKET, SO_BINDTODEVICE, (void *)&ifr, sizeof(ifr)) < 0) {
        // perror("bind to eth1");
        // }
		// else
		// printf("eth1 setsockopt successfull\n");

    while(1)
    {
        saddr_size = sizeof (struct sockaddr_in);
        daddr_size = sizeof (struct sockaddr_in);
		memset(buffer, 0, 65536 );
		
        //Receive a packet
        data_size = recvfrom(acc_eth1 , buffer , 65536 , 0 ,(struct sockaddr_in *) &saddr , (socklen_t*)&saddr_size);

        if(data_size < 0)
        {
            perror("Recvfrom error , failed to get data from eth1\n");
			free(buffer);
			close(eth1_sock);
			close(acc_eth1);
            exit(1);
        }
        else
		{
			printf("Received %d bytes from eth1\n",data_size);
		}
        //Huge code to process the packet (optional)

        //Send the same packet out
        bytes_sent = write(eth0_sock,  buffer,  data_size);
        printf("Sent %d bytes to eth0\n",bytes_sent);
         if (bytes_sent < 0)
		 {
            perror("write: write to eth0 failed");
			free(buffer);
			close(eth0_sock);
            exit(1);
         }

    }
    close(eth1_sock);
    return 0;
}
