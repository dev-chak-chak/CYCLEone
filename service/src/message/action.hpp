#ifndef MESSAGE_ACTION_H_
#define MESSAGE_ACTION_H_

#include <memory>
#include <vector>

#include "message/module.hpp"
#include "message/simulator.hpp"

namespace cycleon {
namespace message {

class Action {
  public:
    std::vector<Module> modules;
    std::vector<Simulator> simulators;
};

}  // namespace config
}  // namespace cycleon

#endif  // MESSAGE_ACTION_H_
