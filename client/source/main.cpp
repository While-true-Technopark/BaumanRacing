#include <iostream>
#include "application.hpp"
#include "event.hpp"

int main(int argc, const char * argv[]) {
    application& app = application::get_instance();
    app.run();

    // union event_data data = { .lap = {1} };
    // event_type type = main_menu;
    // event e(type, data);

    return 0;
}
