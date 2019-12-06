#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "event.hpp"
#include "renderer_abst.hpp"
#include "renderer_manager.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_renderer : public renderer_abst {
 public:
    MOCK_METHOD6(init, int(std::vector<sf::Texture*> cars_textures, sf::Texture* map_texture,
                   sf::Texture* logo_texture, sf::Texture* box_texture,
                   sf::Texture* arrow_texture, sf::Font *main_font));
    MOCK_METHOD1(build_game_scene, int(game_render_data data));
    MOCK_METHOD1(connect_to_open, int(size_t box_select));
    //MOCK_METHOD1(create_room, int(const char (*str)[256] = &STR256));
    //MOCK_METHOD1(connect_to_room, int(const char (*str)[256]));
    MOCK_METHOD1(show_wait, int(size_t waiting));
    MOCK_METHOD1(show_car, int(size_t index));
    MOCK_METHOD0(car_choose_menu, int());
    MOCK_METHOD0(end_game_menu, int());
    MOCK_METHOD0(lobby_scene, int());
    MOCK_METHOD1(main_menu, int(size_t box_select));
    MOCK_METHOD0(settings_menu, int());
    MOCK_METHOD0(wait_scene, int());
};

bool operator==(const game_render_data left, const game_render_data right) {
    if (&left != &right) {
        return false;
    }
    return true;
}

TEST(renderer_manager_test, build_game_scene) {
    mock_renderer m_renderer;
    game_render_data data;

    EXPECT_CALL(m_renderer, build_game_scene(data)).Times(5);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.handle_event(event(update_position, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.handle_event(event(update_lap, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.handle_event(event(race_start, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.handle_event(event(game_start, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.handle_event(event(update_timer, { .empty = {} })), 0);
}

TEST(renderer_manager_test, car_choose_menu) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, car_choose_menu()).Times(1);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.handle_event(event(new_game, { .empty = {} })), 0);
}

TEST(renderer_manager_test, end_game_menu) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, end_game_menu()).Times(1);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.handle_event(event(game_end, { .empty = {} })), 0);
}

TEST(renderer_manager_test, lobby_scene) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, lobby_scene()).Times(3);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.handle_event(event(update_lobby_timer, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.handle_event(event(connection_done, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.handle_event(event(new_player_connected, { .empty = {} })), 0);
}

TEST(renderer_manager_test, main_menu) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, main_menu(0)).Times(2);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.handle_event(event(application_run, { .empty = {} })), 0);
    EXPECT_EQ(renderer_mngr.handle_event(event(main_menu, { .empty = {} })), 0);
}

TEST(renderer_manager_test, settings_menu) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, settings_menu()).Times(1);

    renderer_manager renderer_mngr(&m_renderer);

    EXPECT_EQ(renderer_mngr.handle_event(event(settings_menu, { .empty = {} })), 0);
}

TEST(renderer_manager_test, wait_scene) {
    mock_renderer m_renderer;
    EXPECT_CALL(m_renderer, wait_scene()).Times(1);

    renderer_manager renderer_mngr(&m_renderer);
    EXPECT_EQ(renderer_mngr.handle_event(event(car_chosen, { .empty = {} })), 0);
}
