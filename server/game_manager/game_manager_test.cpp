#include "game_manager.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_game_manager : public game_manager {
 public:
 	explicit mock_game_manager(const map& _map) : game_manager(_map) {};
 	MOCK_METHOD1(throw_side_object, void(size_t));
    MOCK_METHOD2(make_move, void(const command& comm, size_t player_id));
};

bool operator==(const command & left, const command & right) {
    return left.forward == right.forward && left.back == right.back && 
    left.right_turn == right.right_turn && left.left_turn == right.left_turn &&
    left.throw_side_object == right.throw_side_object && left.run_sprint == right.run_sprint;
}

TEST(game_manager, game_builder) {
    mock_game_manager m(standard_maps::get_map(0));
    command comm{true, false, true, false, true, false};
    EXPECT_CALL(m, make_move(comm, 0)).Times(AtLeast(1));
    EXPECT_CALL(m, throw_side_object(0)).Times(AtLeast(1));
    m.game_builder(comm, 0);
}

int main(int argc, char** argv) {
  // ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
