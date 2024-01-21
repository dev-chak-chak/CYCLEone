#include <gtest/gtest.h>

#include "message/request.hpp"

using namespace cycleon;

TEST(RequestTest, AddAction) {
  ::message::Request request;
  request.type = message::REQUEST_ADD_ACTION;
}
