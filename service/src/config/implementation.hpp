#ifndef CONFIG_IMPL_H_
#define CONFIG_IMPL_H_

#include <string>
#include "config/config.hpp"

namespace cycleon {
namespace config {

class ImplementationBase {
 public:
  virtual Config Open(const std::string& path) = 0;
};

}  // namespace config
}  // namespace cycleon

#endif  // CONFIG_IMPL_H_
