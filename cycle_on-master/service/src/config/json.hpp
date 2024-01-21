#ifndef CONFIG_JSON_H_
#define CONFIG_JSON_H_

#include <nlohmann/json.hpp>
#include <string>

#include "config/implementation.hpp"

using json = nlohmann::json;

namespace cycleon {
namespace config {

class Json final : public ImplementationBase {
 public:
  Config Open(const std::string& path) override;
};

}  // namespace config
}  // namespace cycleon

#endif  // CONFIG_JSON_H_
