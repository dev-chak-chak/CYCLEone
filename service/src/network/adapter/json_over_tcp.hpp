#ifndef ADAPTER_JSON_OVER_TCP_H_
#define ADAPTER_JSON_OVER_TCP_H_

#include "network/adapter/adapter.hpp"

#include <nlohmann/json.hpp>

namespace cycleon {
namespace adapter {

class JsonOverTcp : public AdapterBase {
  public:
    message::Request GetRequest(const std::vector<unsigned char>& raw_request) override;
    std::vector<unsigned char> CreateResponse(const message::Response& response) override;
  private:
    message::Action GetAction(const nlohmann::json& request_json);
};

}  // namespace adapter
}  // namespace cycleon

#endif  // ADAPTER_JSON_OVER_TCP_H_
