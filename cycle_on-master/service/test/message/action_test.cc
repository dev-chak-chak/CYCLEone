#include <gtest/gtest.h>

#include "message/action.hpp"

using namespace cycleon;

TEST(ActionTest, IsConstructed) {
  ::message::Action action;
  ::message::Module module_1;
  module_1.command = "cmd_1";
  module_1.parameters = {"par1", "par2"};
  action.modules.push_back(std::move(module_1));
  ::message::Simulator simulator_1;
  module_1.command = "sim_1";
  module_1.parameters = {"par3", "par4"};
  action.simulators.push_back(std::move(simulator_1));
}
