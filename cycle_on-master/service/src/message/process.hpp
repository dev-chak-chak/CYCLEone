#ifndef MESSAGE_PROCESS_H_
#define MESSAGE_PROCESS_H_

#include <string>
#include <vector>

namespace cycleon {
namespace message {

class Process {
  public:
    std::string command;
    std::vector<std::string> parameters;
};

}  // namespace config
}  // namespace cycleon

#endif  // MESSAGE_PROCESS_H_
