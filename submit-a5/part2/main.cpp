#include "Master.h"
#include <thread>
#include "Network.h"


int main() {
    Master m;
    
    // m.main_loop();
    std::thread* t = new std::thread([&m] { m.main_loop(); });
    t->join();
}