#pragma once

#include <stdio.h>

/**
 * This is similiar to a UDP packet where we just have the destination ip
 * and the destination port. 
 * 
 * This is used to easily send payloads to master and forward them to the correct clients
 */ 
struct Payload {
    char src_ip[15];
    int src_port;
    char dst_ip[15];
    int dst_port;
    char payload[512];
};

/**
 * Prints the values in Payload
 * 
 */ 
void print_payload(Payload p) {
    printf("src ip = %s:%d\n", p.src_ip, p.src_port);
    printf("dst ip = %s:%d\n", p.dst_ip, p.dst_port);
    printf("payload = \"%s\"\n", p.payload);
}

/**
 * Gets the Payload size as it is represented as a string.
 * Nothing really fancy needed since chars are sinlge bytes anyway :)
 */
int payload_size() {
    return sizeof(Payload);
}

/**
 * Serializes the payload into a char array array so that it 
 * can be sent over a web socket
 */ 
char* serialize_payload(Payload* payload) {
    return reinterpret_cast<char*>(payload);
}

/**
 * Gets the string representation that was sent over the 
 * websocket and deserializes it so that it can be used as a payload 
 */ 
Payload* deserialize_payload(char* payload) {
    return reinterpret_cast<Payload*>(payload);
}