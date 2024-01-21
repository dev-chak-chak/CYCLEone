#include "server/server.hpp"

#include <gtest/gtest.h>

#include <memory>

TEST(CycleOnServerTest, Constructed) {
  cycleon::Server server;
}
