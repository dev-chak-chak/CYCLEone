#include <gtest/gtest.h>

#include "message/response.hpp"

using namespace cycleon;

TEST(ResponseTest, DefaultValues) {
  ::message::Response response;
  EXPECT_EQ(response.action_id, -1);
  EXPECT_EQ(response.type, ::message::ResponseType::RESPONSE_INVALID);
  EXPECT_EQ(response.status, ::message::Status::STATUS_INVALID);
  EXPECT_EQ(response.result.message, "");
  EXPECT_EQ(response.result.type, ::message::ResultType::RESULT_INVALID);
}
