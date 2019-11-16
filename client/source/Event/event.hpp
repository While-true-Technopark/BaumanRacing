#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>

enum event_type {
    main_menu,
    new_game,
    name_choose,
    name_chosen,
    settings_menu,
    show_car,
    car_chosen,
    connection_done,
    send_car_info,
    new_player_connected,
    update_lobby_timer,
    game_start,
    update_timer,
    race_start,
    update_lap,
    update_rating,
    update_position,
    game_end,
    key_pressed,
    key_released,
    mouse_click
};

struct player_id {
    int id;
};

struct player_info {
    size_t player_id;
    size_t car_id;
};

struct players_info {
    player_info player_1;
    player_info player_2;
    player_info player_3;
    player_info player_4;
};

struct lobby_timer_event {
    int time;
};

struct start_game_timer_event {
    size_t time;
};

struct players_position_info {
    double x;
    double y;
    double angle;
};

struct players_positions_info {
    players_position_info player_1;
    players_position_info player_2;
    players_position_info player_3;
    players_position_info player_4;
};

struct keys_pressed {
    bool up;
    bool down;
    bool left;
    bool right;
    bool enter;
    bool esc;
};
struct lap_event {
    size_t lap;
};
struct players_rating_event {
    size_t player_1;
    size_t player_2;
    size_t player_3;
    size_t player_4;
};
struct game_results_event {
    bool win;
};
struct empty_event {
    
};

union event_data {
    player_id                id;
    players_info             players;
    player_info              player;
    lobby_timer_event        lobby_timer;
    start_game_timer_event   start_game_timer;
    players_positions_info   players_positions;
    players_position_info    players_position;
    keys_pressed             keys;
    lap_event                lap;
    players_rating_event     players_rating;
    game_results_event       game_results;
    empty_event              empty;
};

class event {
public:
    event() = default;
    event(event_type, event_data);
    event_type type;
    event_data data;
};

#endif  // EVENT_H_
