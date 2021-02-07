// C program to demonstrate  
// socket programming in finding ip address  
// and port number of connected client 
// on Server Side 
#include<stdio.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<sys/un.h> 
#include<string.h> 
#include<netdb.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<string.h> 
#define MAX 256
  
int main() 
{ 
    // Two buffers for message communication 
    char buffer1[256], buffer2[256]; 
    int server = socket(AF_INET, SOCK_STREAM, 0); 
    if (server < 0) 
        perror("Error in server creating\n"); 
    else
        printf("Server Created\n"); 
          
    struct sockaddr_in my_addr, peer_addr; 
    my_addr.sin_family = AF_INET; 
    my_addr.sin_addr.s_addr = INADDR_ANY; 
      
    // This ip address will change according to the machine 
    my_addr.sin_addr.s_addr = inet_addr("192.168.1.102"); 
    my_addr.sin_port = htons(12001); 
  
    if (bind(server, (struct sockaddr*) &my_addr, sizeof(my_addr)) == 0) 
        printf("Binded Correctly\n"); 
    else
        perror("Unable to bind\n"); 
          
    if (listen(server, 3) == 0) 
        printf("Listening ...\n"); 
    else
        perror(" listen failed:\n"); 
      
    socklen_t addr_size; 
    addr_size = sizeof(struct sockaddr_in); 
      
    // Ip character array will store the ip address of client 
    //char *ip; 
      
    // while loop is iterated infinitely to  
    // accept infinite connection one by one 
   // { 
        int acc = accept(server, (struct sockaddr*) &peer_addr, &addr_size); 
        if(acc<0)
	{
	   perror("accept failed:");
	   return 1;
	}
	else
	{
	   printf("Connection Accepted\n"); 
	}
	char ip[INET_ADDRSTRLEN]; 
        inet_ntop(AF_INET, &(peer_addr.sin_addr), ip, INET_ADDRSTRLEN); 
      
        // "ntohs(peer_addr.sin_port)" function is  
        // for finding port number of client 
        printf("connection established with IP : %s and PORT : %d\n", ip, ntohs(peer_addr.sin_port)); 
        printf("Server PORT : %d\n", ntohs(my_addr.sin_port)); 
        printf("Client PORT : %d\n", htons(peer_addr.sin_port)); 
	
  
    while (1){ 
	bzero(buffer2, MAX);
	bzero(buffer1, MAX);
       
       	recv(acc, buffer2, 256, 0); 
        printf("FromClient : %s\n", buffer2); 
	bzero(buffer2, MAX);
	int n = 0;
	printf("toClient:");
        // copy server message in the buffer
        while ((buffer1[n++] = getchar()) != '\n');

       // strcpy(buffer1, "yogesh"); 
        send(acc, buffer1, 256, 0);
//	bzero(buffer1, MAX);

 	// if msg contains "Exit" then server exit and chat ended.
        if (strncmp("exit", buffer1, 4) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }  
    return 0; 
} 
