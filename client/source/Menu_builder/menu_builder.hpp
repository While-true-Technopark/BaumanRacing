#ifndef MENU_BUILDER_H_
#define MENU_BUILDER_H_

#include "base_builder.hpp"

class menu_builder : public base_builder {
public:
    menu_builder();
    int main_menu();
    int car_choose_menu();
    int wait_scene();
    int lobby_scene();
    int settings_menu();
    int end_game_menu();
};

#endif  // MENU_BUILDER_H_
