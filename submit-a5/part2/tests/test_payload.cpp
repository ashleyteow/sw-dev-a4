#include "../Payload.h"
#include <string.h>
#include <assert.h>





/**
 * Test the serialize and deserialize functionality
 * Test by copying bytes to a char list and then deserializing it back
 */ 
void test1 () {
    Payload p;
    strcpy(p.dst_ip, "127.168.1.1");
    char* serial = serialize_payload(&p);
    char buffer[payload_size()];
    memcpy(buffer, serial, payload_size());
    Payload* de_serialized = deserialize_payload(serial);
    assert(strcmp(de_serialized->dst_ip,"127.168.1.1") == 0);
}

int main() {
    test1();

}