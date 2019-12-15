#include <thread>
#include "server.hpp"

int main() {
    server srv(PORT, IP);
    std::cout << "server is started and waiting for clients" << std::endl << std::flush;
    std::thread srv_manager(
        [&srv]() {
            while (true) {
                std::string command;
                std::cin >> command;
                if (command == "info") {
                    json info = srv.get_info();
                    std::cout << info["guests"] << " guests" << std::endl;
                    std::map<std::string, size_t> rooms_info = info["rooms"];
                    for(auto& room: rooms_info) {
                        std::cout << "room: " << room.first << " size: " << room.second << std::endl;
                    }
                } else if (command == "stop") {
                    std::cout << "server is stopped" << std::endl;
                    srv.stop();
                    return;
                } else {
                    std::cout << "print 'info' or 'stop'" << std::endl;
                }
                std::cout << std::flush;
            }
        });
    srv.run();
    srv_manager.join();
    return EXIT_SUCCESS;
}
