#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define private public
#include <SFML/Graphics.hpp>
#include "network_manager.hpp"
#include "network_abst.hpp"
#include "event.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_network : public network_abst {
 public:
    MOCK_METHOD0(get_last_package, event());
    MOCK_METHOD1(keys_send, void(struct keys_pressed));
    MOCK_METHOD1(name_car_send, void(struct player_info));
};

bool operator==(const struct keys_pressed & left, const struct keys_pressed & right) {
    return left.up == right.up && left.down == right.down &&
    left.left == right.left && left.right == right.right
    && left.enter == right.enter && left.esc == right.esc;
}

bool operator==(const struct player_info & left, const struct player_info & right) {
    return left.player_id == right.player_id && left.car_id == right.car_id;
}

TEST(network_manager_test, on_event) {
    mock_network m_network;
    
    struct keys_pressed keys = { .up = true, .down = false, .left = true, .right = true,
    .enter = true, .esc = true };
    
    struct player_info player = { .player_id = 1, .car_id = 1 };
    
    EXPECT_CALL(m_network, keys_send(keys)).Times(AtLeast(1));
    EXPECT_CALL(m_network, name_car_send(player)).Times(AtLeast(1));
    network_manager network_mngr(&m_network);

    union event_data data = { .keys = keys };
    event_type type = key_pressed;
    event e(type, data);
    network_mngr.on_event(e);

    data.player = player;
    type = car_chosen;
    event e2(type, data);
    network_mngr.on_event(e2);
}
