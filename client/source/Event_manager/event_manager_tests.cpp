#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define private public
#include "event_manager.hpp"
#include "event.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_game_context : public base_module {
 public:
    explicit mock_game_context() : base_module() {};
    MOCK_METHOD0(on_event, int());
};

class mock_event_manager : public event_manager {
 public:
    explicit mock_event_manager() : event_manager() {};
};

TEST(event_manager_test, on_event_menu_builder) {
    mock_event_manager m_event_manager();
    EXPECT_CALL(m_event_manager.menu_bldr, main_menu()).Times(AtLeast(1));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
