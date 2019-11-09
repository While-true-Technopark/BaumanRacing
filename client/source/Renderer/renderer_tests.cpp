#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define private public
#include "renderer.hpp"
#include "event.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_menu_builder : public base_builder {
 public:
    explicit mock_menu_builder() : base_builder() {};
    MOCK_METHOD0(main_menu, int());
    MOCK_METHOD0(car_choose_menu, int());
    MOCK_METHOD0(wait_scene, int());
    MOCK_METHOD0(lobby_scene, int());
    MOCK_METHOD0(settings_menu, int());
    MOCK_METHOD0(end_game_menu, int());
};

class mock_renderer : public renderer {
 public:
    explicit mock_renderer() : renderer() {};
    // MOCK_METHOD0(menu_bldr.main_menu, int());
    // menu_bldr mock_menu_builder();
    // mock_menu_builder gmock_menu_bldr;
    // menu_builder gmock_menu_bldr;
    // MOCK_METHOD0(menu_bldr, main_menu, int());
    // MOCK_METHOD0(menu_bldr.car_choose_menu, void());
    // MOCK_METHOD0(menu_bldr.wait_scene, void());
    // MOCK_METHOD0(menu_bldr.lobby_scene, void());
    // MOCK_METHOD0(menu_bldr.settings_menu, void());
    // MOCK_METHOD0(menu_bldr.end_game_menu, void());
};

TEST(renderer_test, on_event_menu_builder) {
    mock_renderer m_renderer();
    EXPECT_CALL(m_renderer.menu_bldr, main_menu()).Times(AtLeast(1));
    // EXPECT_CALL(m_renderer.menu_bldr, car_choose_menu()).Times(AtLeast(1));
    // EXPECT_CALL(m_renderer.menu_bldr, wait_scene()).Times(AtLeast(1));
    // EXPECT_CALL(m_renderer.menu_bldr, lobby_scene()).Times(AtLeast(1));
    // EXPECT_CALL(m_renderer.menu_bldr, settings_menu()).Times(AtLeast(1));
    // EXPECT_CALL(m_renderer.menu_bldr, end_game_menu()).Times(AtLeast(1));

    // union event_data data = {};
    // event_type type = main_menu;
    // event e(type, data);
    // m_renderer.on_event(e);

    // event_type type = show_car;
    // event e(type, data);
    // m_renderer.on_event(e);

    // event_type type = car_chosen;
    // event e(type, data);
    // m_renderer.on_event(e);

    // event_type type = connection_done;
    // event e(type, data);
    // m_renderer.on_event(e);

    // event_type type = settings_menu;
    // event e(type, data);
    // m_renderer.on_event(e);

    // event_type type = game_end;
    // event e(type, data);
    // m_renderer.on_event(e);
}

// TEST(renderer_test, on_event_game_builder) {
//     mock_renderer m_renderer();

//     EXPECT_CALL(m_renderer.game_bldr, build_rating()).Times(AtLeast(1));
//     EXPECT_CALL(m_renderer.game_bldr, build_map()).Times(AtLeast(1));
//     EXPECT_CALL(m_renderer.game_bldr, build_car()).Times(AtLeast(1));
//     EXPECT_CALL(m_renderer.game_bldr, build_cars()).Times(AtLeast(1));

//     union event_data data = {};
//     event_type type = update_position;
//     event e(type, data);
//     m_renderer.on_event(e);

//     event_type type = update_rating;
//     event e(type, data);
//     m_renderer.on_event(e);
// }

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}