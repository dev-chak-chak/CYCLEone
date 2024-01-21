#ifndef CONFIG_READER_H_
#define CONFIG_READER_H_

#include <memory>

#include "config/config.hpp"
#include "config/implementation.hpp"

typedef std::shared_ptr<cycleon::config::ImplementationBase> ImplPtr;

namespace cycleon {
namespace config {

class ConfigReader {
 public:
  void setImplementation(ImplPtr implementation);
  Config Open(const std::string& path);

 private:
  ImplPtr implementation_;
};

}  // namespace config
}  // namespace cycleon

#endif  // CONFIG_READER_H_
