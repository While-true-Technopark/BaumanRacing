#include <thread>
#include "server.hpp"

const std::string MAIN = "print 'info' or 'stop'";

int main() {
    server srv(PORT, IP);
    std::thread srv_manager(
        [&srv]() {
            std::cout << MAIN << std::endl << std::flush;
            while (true) {
                std::string command;
                std::cin >> command;
                if (command == "info") {
                    json info = srv.get_info();
                    std::cout << info["guests"] << " guests" << std::endl;
                    std::map<std::string, size_t> rooms_info = info["rooms"];
                    for(auto& room: rooms_info) {
                        std::cout << "room: " << room.first << ", size: " << room.second << std::endl;
                    }
                } else if (command == "stop") {
                    std::cout << "server is stopped" << std::endl;
                    srv.stop();
                    return;
                } else {
                    std::cout << MAIN << std::endl;
                }
                std::cout << std::flush;
            }
        });
    srv.run();
    srv_manager.join();
    return EXIT_SUCCESS;
}
