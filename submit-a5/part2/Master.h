#pragma once
#include "Network.h"
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include "Payload.h"



class Master {
    public:
    ClientID* clients[MAX_CLIENTS] = {NULL};
    char buffer[MAX_PACKET_SIZE] = {0}; 
    unsigned int port = MASTER_PORT;
    int new_socket;
    struct sockaddr_in address; 
    int addrlen;
    int server_fd; 

    Master () {
        //TODO Make this variable and not statically
        // allocated on run time
        
    }

    ~Master () {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] != NULL) {
                delete clients[i];
            }
        }
    }


    /**
     * Bind this object to the MASTER port
     */ 
    void bind_to_port() {
        int opt = 1; 
        addrlen = sizeof(address); 
        // Creating socket file descriptor 
        if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
        { 
            perror("socket failed"); 
            exit(EXIT_FAILURE); 
        } 
        
        // Forcefully attaching socket to the port 8080 
        if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR , &opt, sizeof(opt))) 
        { 
            perror("setsockopt"); 
            exit(EXIT_FAILURE); 
        } 
        address.sin_family = AF_INET; 
        address.sin_addr.s_addr = INADDR_ANY; 
        address.sin_port = htons( port ); 
        
        // Forcefully attaching socket to the port 8080 
        if (bind(server_fd, (struct sockaddr *)&address, 
                                    sizeof(address))<0) 
        { 
            perror("bind failed"); 
            exit(EXIT_FAILURE); 
        } 
        if (listen(server_fd, 3) < 0) 
        { 
            perror("listen"); 
            exit(EXIT_FAILURE); 
        } 


    }

    /**
     * Wait for the client response
     */ 
    void wait_for_client() {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                (socklen_t*)&addrlen))<0) 
        { 
            perror("accept"); 
            exit(EXIT_FAILURE); 
        } 
        int valread = read( new_socket , buffer, MAX_PACKET_SIZE); 
    }

    /**
     * Attempts to add a client ID to the local
     * ClientID list and if this client is already in 
     * the client list then the function wil return -1
     * returns -2 if list is full.
     * 
     * Mutation Note: This steals ownership of c
     */ 
    int add_client(ClientID* c) {
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if(clients[i] != NULL && clients[i]->equals(c)) {
                return -1;
            } else if (clients[i] == NULL) {
                clients[i] = c;;
                return 0;
            }
        }
        return -2;
    }

    /**
     * The main server loop that will handle all incoming connections
     * 
     */ 
    void main_loop() {
        this->bind_to_port();
        while (1) {
            this->wait_for_client();
            Payload p = *deserialize_payload(this->buffer);
            print_payload(p);
            ClientID* to_add = new ClientID(p.src_ip);
            to_add->port = p.src_port;
            
            this->add_client(to_add);
            this->incoming_connection(p);
        }
    }

    /**
     * Creates a client and sends a payload to the 
     * Payload's destination
     */ 
    void forward_payload_to_dst(Payload &p) {
        //TODO unbind the port. rebind as a sender
        // After rebinding as a sender forward the packet 
        // to p.dst_ip and p_port

        

        // UN HARDCODE THIS
        if (p.t == REQUEST_LIST) { 
            int port = 9090;
            ClientID c_id("127.0.0.1:9090");
            Client c(c_id);
            strcpy(p.src_ip, "127.0.0.1");
            p.src_port = port;

            print_payload(p);

            send(new_socket ,serialize_payload(&p), payload_size() , 0 );
            // printf("Sending message to this payload:\n");

            // print_payload(p);


            // printf("####");

            // c.send_packet_to(p.dst_ip, p.dst_port, serialize_payload(&p), payload_size());
        }


        
    }

    /**
     * Sends the a Payload to the dst_ip and dst_port
     * where its payload is a list of IP dimilited by
     * a comma.
     */ 
    void send_client_list (char* dst_ip, int dst_port) {
        Payload p;
        strcpy(p.dst_ip, dst_ip);
        p.dst_port = dst_port;
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] != NULL) {
                char num_buf[100];
                sprintf(num_buf, "%d.%d.%d.%d:%d,", 
                    clients[i]->ip_bytes[0],
                    clients[i]->ip_bytes[1],
                    clients[i]->ip_bytes[2],
                    clients[i]->ip_bytes[3],
                    clients[i]->port);
                strcat(p.payload, num_buf);
            }
        
        }       
        this->forward_payload_to_dst(p); 
    }

    /**
     * Handles all incoming connections to the Master
     */ 
    int incoming_connection(Payload& p) {
        //TODO Handle multiple types of packets based on 
        // the payload type. for now lets just forward the packet
        if (p.t == REQUEST_LIST) {
            this->send_client_list(p.src_ip, p.src_port);
        } else if (p.t == FORWARD_PACKET) {
            this->forward_payload_to_dst(p);
        }

    }


};

