#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

#include <string>

namespace cycleon {
namespace config {

struct Network {
  std::string address;
  int port;
};

class Config {
 public:
  Network network;
};

}  // namespace config
}  // namespace cycleon

#endif  // CONFIG_CONFIG_H_
