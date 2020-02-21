#include <thread>
#include <chrono>        
#include <assert.h>

#include "../Network.h"


int main() {
    Master m;
    // m.main_loop();
    std::thread* t = new std::thread([&m] { m.main_loop(); });
    ClientID c_id("127.0.0.1:8082");
    Client c(c_id);

    Payload p;
    strcpy(p.src_ip, "127.0.0.1");
    p.src_port = 8082;
    strcpy(p.dst_ip, "127.0.0.1");
    p.dst_port = 8081;
    print_payload(p);
    strcpy(p.payload, "asdfghjkl");
    c.send_message_to_master(p, false);

    // Wait for server to get the message
    std::this_thread::sleep_for (std::chrono::seconds(1));
    
    ClientID c_id_temp("127.0.0.1");
    // Test Packet was received properly
    assert(deserialize_payload(m.buffer)->src_port ==  8082);
    assert(strcmp(deserialize_payload(m.buffer)->src_ip, "127.0.0.1") == 0);
    assert(strcmp(deserialize_payload(m.buffer)->payload, "asdfghjkl") == 0);

    std::this_thread::sleep_for (std::chrono::seconds(2));
    // Test Client was added
    assert(m.clients[0]->equals(&c_id));

    t->detach();    
}