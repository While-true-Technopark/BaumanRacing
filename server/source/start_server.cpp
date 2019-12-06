#include "server.hpp"
    
int main() {
    server srv(PORT, LOCAL_IP);
    srv.run();
    return 0;
}
