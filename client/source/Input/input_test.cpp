#include "gtest/gtest.h"
#include "gmock/gmock.h"

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

TEST(input_manager_test, on_event) {
    mock_input m_input;
    EXPECT_CALL(m_input, start_control()).Times(AtLeast(1));
    EXPECT_CALL(m_input, end_control()).Times(AtLeast(1));
    
    input_manager input_mngr(&m_input);

    union event_data data = { .empty = { } };
    event_type type = race_start;
    event e(type, data);
    input_mngr.on_event(e);
    
    data = { .empty = { } };
    type = game_end;
    event e2(type, data);
    input_mngr.on_event(e2);
}
