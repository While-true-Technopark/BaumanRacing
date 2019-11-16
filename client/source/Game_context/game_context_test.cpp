#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define private public
#include <SFML/Graphics.hpp>
#include "game_context_manager.hpp"
#include "game_context_abst.hpp"
#include "event.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_game_context : public game_context_abst {
public:
    MOCK_METHOD1(get_name_from_id, int(size_t));
    MOCK_METHOD1(get_car_from_id, int(size_t));
    MOCK_METHOD1(add_players, int(struct players_info));
    MOCK_METHOD1(update_positions, int(struct players_positions_info));
};

bool operator==(const struct players_info & left, const struct players_info & right) {
    return left.player_1.player_id == right.player_1.player_id
    && left.player_1.car_id == right.player_1.car_id
    && left.player_2.player_id == right.player_2.player_id
    && left.player_2.car_id == right.player_2.car_id
    && left.player_3.player_id == right.player_3.player_id
    && left.player_3.car_id == right.player_3.car_id
    && left.player_4.player_id == right.player_4.player_id
    && left.player_4.car_id == right.player_4.car_id;
}

bool operator==(const struct players_positions_info & left,
                const struct players_positions_info & right) {
    return left.player_1.x == right.player_1.x
    && left.player_1.y == right.player_1.y
    && left.player_1.angle == right.player_1.angle
    && left.player_2.x == right.player_2.x
    && left.player_2.y == right.player_2.y
    && left.player_2.angle == right.player_2.angle
    && left.player_3.x == right.player_3.x
    && left.player_3.y == right.player_3.y
    && left.player_3.angle == right.player_3.angle
    && left.player_4.x == right.player_4.x
    && left.player_4.y == right.player_4.y
    && left.player_4.angle == right.player_4.angle;
}

bool operator==(const struct player_id & left, const struct player_id & right) {
    return left.id == right.id;
}

TEST(game_context_manager_test, update_positions) {
    mock_game_context m_game_context;
    
    struct players_positions_info players = {
        .player_1 = { .x = 0.0, .y = 0.0, .angle = 0.0 },
        .player_2 = { .x = 0.0, .y = 0.0, .angle = 0.0 },
        .player_3 = { .x = 0.0, .y = 0.0, .angle = 0.0 },
        .player_4 = { .x = 0.0, .y = 0.0, .angle = 0.0 }
    };
    
    EXPECT_CALL(m_game_context, update_positions(players)).Times(AtLeast(1));
    game_context_manager game_context_mngr(&m_game_context);
    
    union event_data data = { .players_positions = players };
    event_type type = car_chosen;
    event e2(type, data);
    EXPECT_EQ(game_context_mngr.on_event(e2), 0);
}


TEST(game_context_manager_test, add_players) {
    mock_game_context m_game_context;
    
    struct players_info players = {
        .player_1 = { .player_id = 1, .car_id = 1 },
        .player_2 = { .player_id = 2, .car_id = 1 },
        .player_3 = { .player_id = 3, .car_id = 2 },
        .player_4 = { .player_id = 4, .car_id = 1 }
    };
    
    EXPECT_CALL(m_game_context, add_players(players)).Times(AtLeast(1));
    game_context_manager game_context_mngr(&m_game_context);
    
    union event_data data = { .players = players };
    event_type type = car_chosen;
    event e2(type, data);
    EXPECT_EQ(game_context_mngr.on_event(e2), 0);
}

TEST(game_context_manager_test, get_name_from_id) {
    mock_game_context m_game_context;
    
    struct player_id player = { .id = 1 };
    
    EXPECT_CALL(m_game_context, get_name_from_id(1)).Times(AtLeast(1));
    game_context_manager game_context_mngr(&m_game_context);
    
    union event_data data = { .id = player };
    event_type type = car_chosen;
    event e2(type, data);
    EXPECT_EQ(game_context_mngr.on_event(e2), 0);
}

TEST(game_context_manager_test, get_car_from_id) {
    mock_game_context m_game_context;
    
    struct player_id player = { .id = 1 };
    
    EXPECT_CALL(m_game_context, get_car_from_id(1)).Times(AtLeast(1));
    game_context_manager game_context_mngr(&m_game_context);
    
    union event_data data = { .id = player };
    event_type type = car_chosen;
    event e2(type, data);
    EXPECT_EQ(game_context_mngr.on_event(e2), 0);
}
