#include "../Network.h"


void test1 () {
    ClientID cid("192.168.1.0:8080");
    assert(cid.port == 8080);

    assert(cid.ip_bytes[0] == 192);
    assert(cid.ip_bytes[1] == 168);
    assert(cid.ip_bytes[2] == 1);
    assert(cid.ip_bytes[3] == 0);
}
void test2 () {
    ClientID cid("192.168.1.0");
    assert(cid.port == 0);

    assert(cid.ip_bytes[0] == 192);
    assert(cid.ip_bytes[1] == 168);
    assert(cid.ip_bytes[2] == 1);
    assert(cid.ip_bytes[3] == 0);
}

void test3 () {
    ClientID cid("127.0.0.1:60");
    assert(cid.port == 60);

    assert(cid.ip_bytes[0] == 127);
    assert(cid.ip_bytes[1] == 0);
    assert(cid.ip_bytes[2] == 0);
    assert(cid.ip_bytes[3] == 1);
}

int main() {
    test1();
    test2();
    test3();
}