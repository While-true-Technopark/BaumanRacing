#include "game_manager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;
using testing::_;

class mock_game_manager : public game_manager {
 public:
    explicit mock_game_manager(const map& _map) : game_manager(_map) {};
    MOCK_METHOD2(make_move, void(const command& comm, size_t player_id));
    MOCK_METHOD1(throw_side_object, void(size_t));
    MOCK_METHOD0(get_players_coord, std::vector<point>());
    MOCK_METHOD0(get_side_objects_coord, std::vector<point>());
};

bool operator==(const command & left, const command & right) {
    return left.forward == right.forward && left.back == right.back && 
    left.right_turn == right.right_turn && left.left_turn == right.left_turn &&
    left.throw_side_object == right.throw_side_object && left.run_sprint == right.run_sprint;
}

TEST(game_manager, game_builder) {
    mock_game_manager m(standard_maps::get_map(0));

    command comm{true, false, true, false, true, true};
    EXPECT_CALL(m, make_move(comm, 0)).Times(AtLeast(1));
    EXPECT_CALL(m, throw_side_object(0)).Times(AtLeast(1));
    m.game_builder(comm, 0);

    comm = {false, false, false, false, false, true};
    EXPECT_CALL(m, make_move(comm, 0)).Times(AtLeast(0));
    EXPECT_CALL(m, throw_side_object(0)).Times(AtLeast(1));
    m.game_builder(comm, 0);

    comm = {true, false, false, false, false, false};
    EXPECT_CALL(m, make_move(comm, 0)).Times(AtLeast(1));
    EXPECT_CALL(m, throw_side_object(0)).Times(AtLeast(0));
    m.game_builder(comm, 0);
}

TEST(game_manager, get_coord) {
    mock_game_manager m(standard_maps::get_map(0));

    EXPECT_CALL(m, get_players_coord()).Times(AtLeast(1));
    EXPECT_CALL(m, get_side_objects_coord()).Times(AtLeast(0));
    m.get_coord(game_manager::players_coord);
    
    EXPECT_CALL(m, get_players_coord()).Times(AtLeast(0));
    EXPECT_CALL(m, get_side_objects_coord()).Times(AtLeast(1));
    m.get_coord(game_manager::side_objects_coord);

    EXPECT_CALL(m, get_players_coord()).Times(AtLeast(1));
    EXPECT_CALL(m, get_side_objects_coord()).Times(AtLeast(1));
    m.get_coord();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
