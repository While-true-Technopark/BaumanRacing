#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define private public
#include "application.hpp"
#include "event.hpp"

using ::testing::AtLeast;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgReferee;

class mock_application : public application {
 public:
    mock_application() : application() {};
    MOCK_METHOD0(run, bool());
};

TEST(application_test, run) {
    mock_application m_application;
    EXPECT_CALL(m_application, run()).Times(AtLeast(1));
    m_application.run();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
