#ifndef PROCESSOR_HANDLER_H_
#define PROCESSOR_HANDLER_H_

#include "processor/processor.hpp"

#include <vector>
#include <map>
#include <memory>

#include "runner/child.hpp"
#include "network/adapter/json_over_tcp.hpp"
#include "message/response.hpp"
#include "message/request.hpp"


namespace cycleon {
namespace processor {

typedef std::shared_ptr<runner::ModuleBase> ModuleBasePtr;
typedef std::vector<ModuleBasePtr> ModulesVector;
typedef std::map<int, ModulesVector> ActionMap;
typedef std::map<int, message::Status> StatusMap;
typedef std::map<int, message::Result> ResultMap;

class Handler : public ProcessorBase {
 public:
  Handler();
  std::vector<unsigned char> Process(
      const std::vector<unsigned char>& raw_request) override;
  private:
    message::Response ProcessRequest(const message::Request& request);
    void AddAction(const message::Request& request, message::Response* response);
    void RemoveAction(const message::Request& request, message::Response* response);
    void GetActionStatus(const message::Request& request, message::Response* response);
    void GetActionResult(const message::Request& request, message::Response* response);
    void Invalid(const message::Request& request, message::Response* response);

    int next_action_id();
    std::vector<std::string> ConvertProcessToArguments(const message::Process* process);
    void PrintRawRequest(const std::vector<unsigned char>& raw_request);
    void PrintRawResponse(const std::vector<unsigned char>& raw_response);
    void PrintRawMessage(const std::vector<unsigned char>& raw_message);
    
    adapter::JsonOverTcp json_over_tcp_adapter_;
    int next_action_id_;
    ActionMap actions_;
    StatusMap statuses_;
    ResultMap results_;
};

}  // namespace processor
}  // namespace cycleon

#endif  // PROCESSOR_HANDLER_H_
