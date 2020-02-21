
// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include "Payload.h"
   

int send_packet_to(char* ip, unsigned int port, char* packet) {
    int sock = 0, valread; 
    struct sockaddr_in serv_addr; 
    char buffer[1024] = {0}; 
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(port); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } 
    send(sock , packet , sizeof(Payload) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer ); 

}


int main(int argc, char const *argv[]) 
{ 
    Payload p;
    strcpy(p.dst_ip, "127.0.0.1");
    p.dst_port = 8081;
    print_payload(p);
    strcpy(p.payload, "asdfghjkl");
    // p.dst_ip[0] = 127;
    send_packet_to("127.0.0.1", 8080, serialize_payload(&p));

    return 0; 
} 