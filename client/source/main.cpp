#include <iostream>
#include "application.hpp"
#include "event.hpp"

int main(int argc, const char * argv[]) {
    std::cout << "Hello, World!\n";
    application& app = application::get_instance();
    app.run();

    //struct lap_event lap = { 1 };
    //data.lap = {1};

    union event_data data = { .lap = {1} };
    event_type type = main_menu;
    event e(type, data);

    //renderer rend;
    return 0;
}
