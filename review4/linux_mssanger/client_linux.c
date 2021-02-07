// C program to demonstrate socket programming 
// as well as explicitly assigning a port number 
// on Client Side 
#include<stdio.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<sys/un.h> 
#include<string.h> 
#include<netdb.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<stdlib.h> 
  
int main() 
{ 
    // Two buffer are for message communication 
    char buffer1[256], buffer2[256]; 
    struct sockaddr_in my_addr, my_addr1;

    int client = socket(AF_INET, SOCK_STREAM, 0); 
    if (client < 0) 
        printf("Error in client creating\n"); 
    else
        printf("Client Created\n"); 
          
    my_addr.sin_family = AF_INET; 
    my_addr.sin_addr.s_addr = INADDR_ANY; 
    my_addr.sin_port = htons(12000); 
      
    // This ip address will change according to the machine 
    my_addr.sin_addr.s_addr = inet_addr("192.168.1.102"); 
  
    // Explicitly assigning port number 12010 by  
    // binding client with that port  
    my_addr1.sin_family = AF_INET; 
    my_addr1.sin_addr.s_addr = INADDR_ANY; 
    my_addr1.sin_port = htons(12001); 
      
    // This ip address will change according to the machine 
    my_addr1.sin_addr.s_addr = inet_addr("192.168.1.102"); 
    
   // if (bind(client, (struct sockaddr*) &my_addr, sizeof(struct sockaddr_in)) == 0) 
   //     printf("Binded Correctly\n"); 
    //else
    //    perror("Unable to bind\n"); 
      
    socklen_t addr_size = sizeof my_addr; 
    int con = connect(client, (struct sockaddr*) &my_addr1, sizeof my_addr); 
    if (con == 0) 
        printf("Client Connected\n"); 
    else
        perror("connect failed:Error in Connection\n"); 
  
    while(1)
    {
	bzero(buffer2, sizeof(buffer2));
	bzero(buffer1, sizeof(buffer1));
	printf("Client:Enter the string : ");
	int n = 0;
        while ((buffer2[n++] = getchar()) != '\n');
        //strcpy(buffer2, "Hello"); 
        send(client, buffer2, 256, 0);
//	bzero(buffer2, sizeof(buffer2));
 	if ((strncmp(buffer2, "exit", 4)) == 0)
       	{
            printf("Client Exited...\n");
            break;
        }
       
       	recv(client, buffer1, 256, 0); 
        //printf("Server : %s\n", buffer1); 
	printf("From Server : %s", buffer1);
	//bzero(buffer1, sizeof(buffer1));
       
 	if ((strncmp(buffer1, "exit", 4)) == 0)
       	{
            printf("Client exited because Exit from server\n");
            break;
        }
    }
    return 0; 
} 
