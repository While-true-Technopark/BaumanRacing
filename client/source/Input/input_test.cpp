#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define private public
#include <SFML/Graphics.hpp>
#include "input_manager.hpp"
#include "input_abst.hpp"
#include "event.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_input : public input_abst {
 public:
    MOCK_METHOD0(start_control, void());
    MOCK_METHOD0(end_control, void());
    MOCK_METHOD0(get_pressed_key, struct keys_pressed());
};

TEST(input_manager_test, get_pressed_key) {
    mock_input m_input;
    EXPECT_CALL(m_input, get_pressed_key()).Times(AtLeast(1));

    input_manager input_mngr(&m_input);
    input_mngr.throw_event();
}

TEST(input_manager_test, start_control) {
    mock_input m_input;
    EXPECT_CALL(m_input, start_control()).Times(AtLeast(1));

    input_manager input_mngr(&m_input);

    union event_data data = { .empty = { } };
    event_type type = race_start;
    event e(type, data);
    EXPECT_EQ(input_mngr.handle_event(e), 0);
}

TEST(input_manager_test, end_control) {
    mock_input m_input;
    EXPECT_CALL(m_input, end_control()).Times(AtLeast(1));

    input_manager input_mngr(&m_input);

    union event_data data = { .empty = { } };
    event_type type = game_end;
    event e(type, data);
    EXPECT_EQ(input_mngr.handle_event(e), 0);
}
