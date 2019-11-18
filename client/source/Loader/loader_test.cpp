#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

#include "event.hpp"
#include "loader_abst.hpp"
#include "loader_manager.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_loader : public loader_abst {
 public:
    MOCK_METHOD0(load_all, int());
};

TEST(load_manager_test, load_all) {
    mock_loader m_loader;
    EXPECT_CALL(m_loader, load_all()).Times(1);

    loader_manager loader_mngr(&m_loader);
    EXPECT_EQ(loader_mngr.on_event(event(application_run, { .empty = {} })), 0);
}
