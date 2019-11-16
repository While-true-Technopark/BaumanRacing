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
};

bool operator==(const struct players_info & left, const struct players_info & right) {
    return left.player_1.player_id == right.player_1.player_id && left.player_1.car_id == right.player_1.car_id && left.player_2.player_id == right.player_2.player_id && left.player_2.car_id == right.player_2.car_id && left.player_3.player_id == right.player_3.player_id && left.player_3.car_id == right.player_3.car_id && left.player_4.player_id == right.player_4.player_id && left.player_4.car_id == right.player_4.car_id;
}

TEST(game_context_manager_test, on_event) {
    mock_game_context m_game_context;
    
    struct players_info players = { .player_1 = { .player_id = 1, .car_id = 1 },
    .player_2 = { .player_id = 2, .car_id = 1 },
    .player_3 = { .player_id = 3, .car_id = 2 },
    .player_4 = { .player_id = 4, .car_id = 1 }
    };
    
    EXPECT_CALL(m_game_context, add_players(players)).Times(AtLeast(1));
    game_context_manager game_context_mngr(&m_game_context);

    union event_data data = { .players = players };
    event_type type = car_chosen;
    event e2(type, data);
    game_context_mngr.on_event(e2);
}
