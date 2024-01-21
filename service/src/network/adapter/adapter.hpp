#ifndef ADAPTER_ADAPTER_H_
#define ADAPTER_ADAPTER_H_

#include <vector>

#include "message/request.hpp"
#include "message/response.hpp"

namespace cycleon {
namespace adapter {

class AdapterBase {
  public:
    virtual message::Request GetRequest(const std::vector<unsigned char>& raw_request) = 0;
    virtual std::vector<unsigned char> CreateResponse(const message::Response& response) = 0;
};

}  // namespace adapter
}  // namespace cycleon

#endif  // ADAPTER_ADAPTER_H_
