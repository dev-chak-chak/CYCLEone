#include <gtest/gtest.h>

#include "processor/echo.hpp"

using namespace cycleon;

TEST(EchoTest, IsConstructed) {
  ::processor::Echo echo_processor;

  std::vector<unsigned char> input = {'H','e','l','l','o','!'};
  auto output = echo_processor.Process(input);

  std::vector<unsigned char> expected_output = {
    'E','c','h','o',':',' ', 'H','e','l','l','o','!'};

  EXPECT_EQ(output, expected_output);
}
