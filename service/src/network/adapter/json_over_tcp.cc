#include "network/adapter/json_over_tcp.hpp"

using namespace cycleon::adapter;
using namespace cycleon::message;
using json = nlohmann::json;

Request JsonOverTcp::GetRequest(const std::vector<unsigned char>& raw_request) {
  
  auto request_json = json::parse(std::string(raw_request.begin(), raw_request.end()));

  Request request;
  request_json.at("action_id").get_to(request.action_id);
  request_json.at("type").get_to(request.type);

  request.action = GetAction(request_json);
  
  return request;
}

Action JsonOverTcp::GetAction(const nlohmann::json& request_json) {

  Action action;
  if (!request_json.contains("action")) {
    return action;
  }

  const auto& action_json = request_json.at("action");
  if (!action_json.contains("modules") && !action_json.contains("simulators")) {
    return action;
  }

  if (action_json.contains("modules")) {
    if (action_json.at("modules").size() > 0) {
      for (const auto& module : action_json.at("modules")) {
        Module new_module;
        module.at("command").get_to(new_module.command);
        for (const auto& parameter : module.at("parameters")) {
          new_module.parameters.push_back(parameter.get<std::string>());
        }
        action.modules.push_back(new_module);
      }
    }
  }

  if (action_json.contains("simulators")) {
    if (action_json.at("simulators").size() > 0) {
      for (const auto& simulator : action_json.at("simulators")) {
        Simulator new_simulator;
        simulator.at("command").get_to(new_simulator.command);
        for (const auto& parameter : simulator.at("parameters")) {
          new_simulator.parameters.push_back(parameter.get<std::string>());
        }
        action.simulators.push_back(new_simulator);
      }
    }
  }

  return action;
}

std::vector<unsigned char> JsonOverTcp::CreateResponse(const Response& response) {
  json j;
  j["action_id"] = response.action_id;
  j["type"] = response.type;
  j["status"] = response.status;
  j["result"]["message"] = response.result.message;
  j["result"]["type"] = response.result.type;

  std::string s = j.dump();
  std::vector<unsigned char> raw_response;
  raw_response.reserve(s.size());
  for (const auto& c : s) {
    raw_response.push_back(c);
  }

  return raw_response;
}
