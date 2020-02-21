

#pragma once
#include "Client.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

class ClientID {
    public:
    unsigned int ip_bytes[4];

    // Default = 0
    unsigned int port;

    // constructs 
    /**
     * xxx.xxx.xxx.xxx:port
     * 
     * where each xxx is a byte in the IP Address
     */ 
    ClientID(const char* ip_address) {
        this->port = 0;
        int curr_byte = 0;
        for(int i = 0; i < strlen(ip_address); i++) {

            assert(curr_byte <= 3); // we should never read more than 3 bytes
            char buffer[10];
            char c = ip_address[i];
            if (c == '.') {
                ip_bytes[curr_byte] = atoi(buffer);
                assert(ip_bytes[curr_byte] <= 255);
                curr_byte++;
                buffer[0] = '\0';
            } else if (c == ':') {
                ip_bytes[curr_byte] = atoi(buffer);
                port = atoi(&ip_address[i + 1]);
                assert(port <= 65535);
                break; // once we get port we can return from the loop
            } else if(isdigit(c)) {
                unsigned int len = strlen(buffer);
                buffer[len] = c;
                buffer[len + 1] = '\0';
                if(strlen(ip_address) == i + 1) { // is last character
                    ip_bytes[curr_byte] = atoi(buffer);
                }
            } else {
                printf("Bad input!");
                assert(0);
            }

        }
    }

    /**
     * Checks if this Client is equal to that clientID
     */ 
    bool equals(ClientID* that) {
        return this->port == that->port &&
            this->ip_bytes[0] == that->ip_bytes[0] &&
            this->ip_bytes[1] == that->ip_bytes[1] &&
            this->ip_bytes[2] == that->ip_bytes[2] &&
            this->ip_bytes[3] == that->ip_bytes[3];
    }

};