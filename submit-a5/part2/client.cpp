#include "Master.h"
#include <thread>
#include "Network.h"


int main() {

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
    print_payload(*deserialize_payload(c.get_reponse()));
}