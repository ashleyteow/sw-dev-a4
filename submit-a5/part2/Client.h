#pragma once
#include "ClientID.h"
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#include "Payload.h"




class ClientID;

/*
 * Houses a client and it's functions for conencting and sending packets to a master
 */ 
class Client {
    public:
    ClientID* id;
    bool _wait_for_response;

    char response_from_server[MAX_PACKET_SIZE] = {0};

    // constructs a Client object
    Client(ClientID& id) {
        
    }

    ~Client() {
        //TODO delete id;
    }
    /**
     * Sends a packet to a given ip and port provided
     * Function adaptived from - https://www.geeksforgeeks.org/socket-programming-cc/
     */ 
    int send_packet_to(const char* ip, unsigned int port, char* packet, unsigned int packet_size) {
        int sock = 0, valread; 
        struct sockaddr_in serv_addr; 
        char buffer[MAX_PACKET_SIZE] = {0}; 
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
        send(sock , packet , packet_size , 0 ); 
        printf("Hello message sent\n"); 
        if (this->_wait_for_response) {
            valread = read( sock , buffer, MAX_PACKET_SIZE); 
            printf("%s\n",buffer ); 
            memcpy ( response_from_server, buffer, MAX_PACKET_SIZE);
            // strncpy(response_from_server, buffer, payload_size());
        }
    }

    /**
     * builds a payload packet that uses this client to populate 
     * the src and detination fields
     * 
     * dst_ip is formatted like "byte_0.byte_1.byte_2.byte_3:Port"
     */ 
    Payload* build_payload_packet(char* dst_ip, char* packet) {
        //TODO implement
    }

    /**
     * Sends a Payload to master.
     * 
     * Allows the user to choose whether or not they want to wait for
     * a response or not. 
     */ 
    void send_message_to_master(Payload p, bool wait = false) {
        //TODO Assert that the payload src is the same as this clients source
        this->_wait_for_response = wait;
        this->send_packet_to(MASTER_IP, 
            MASTER_PORT,
            serialize_payload(&p), 
            payload_size());
    }

    /**
     * Gets a reference to the response for our latest sent connection
     */ 
    char* get_reponse() {
        return response_from_server;
    }

    /**
     * This function is meant to be overwritten by any child server 
     * so that the user can easily process the response of the client
     * 
     * The response packets are stored in bufffer.
     */ 
    virtual void process_response() {

    }
};