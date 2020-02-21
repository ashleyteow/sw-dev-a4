






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
    p.t = REQUEST_LIST;
    strcpy(p.src_ip, "127.0.0.1");
    p.src_port = 8082;
    strcpy(p.dst_ip, "127.0.0.1");
    p.dst_port = 8081;
    print_payload(p);
    strcpy(p.payload, "asdfghjkl");
    c.send_message_to_master(p, true);
    // Wait for server to get the message
    std::this_thread::sleep_for (std::chrono::seconds(1));
    printf(deserialize_payload(c.get_reponse())->payload);
    
    assert(
        strcmp(
            deserialize_payload(c.get_reponse())->payload, 
            "127.0.0.1:8082,")==0);

    

    t->detach();    
}