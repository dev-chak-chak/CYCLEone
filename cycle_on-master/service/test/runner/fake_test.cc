#include "runner/fake.hpp"

#include <gtest/gtest.h>

using namespace cycleon;

class FakeModule : public ::testing::Test {
 protected:
  runner::Fake fake_runner;
};

TEST_F(FakeModule, IsConstructed) {}

TEST_F(FakeModule, CallLaunch) {
  EXPECT_FALSE(fake_runner.isRunning());
  fake_runner.Launch();
  EXPECT_TRUE(fake_runner.isRunning());
}

TEST_F(FakeModule, CallShutdown) {
  EXPECT_FALSE(fake_runner.isRunning());
  fake_runner.Shutdown();
  EXPECT_FALSE(fake_runner.isRunning());
}
