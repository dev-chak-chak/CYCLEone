#include "processor/handler.hpp"

#include <algorithm>
#include <iostream>

using namespace cycleon::processor;
using namespace cycleon::message;

Handler::Handler() : next_action_id_(0) {}

std::vector<unsigned char> Handler::Process(
    const std::vector<unsigned char>& raw_request) {
  PrintRawRequest(raw_request);
  auto request = json_over_tcp_adapter_.GetRequest(raw_request);
  auto response = ProcessRequest(request);
  auto raw_response = json_over_tcp_adapter_.CreateResponse(response);
  PrintRawResponse(raw_response);
  return raw_response;
}

Response Handler::ProcessRequest(const Request& request) {
  Response response;

  switch (request.type) {
    case REQUEST_ADD_ACTION:
      AddAction(request, &response);
      break;
    case REQUEST_REMOVE_ACTION:
      RemoveAction(request, &response);
      break;
    case REQUEST_GET_ACTION_STATUS:
      GetActionStatus(request, &response);
      break;
    case REQUEST_GET_ACTION_RESULT:
      GetActionResult(request, &response);
      break;

    case REQUEST_INVALID:
    default:
      Invalid(request, &response);
      break;
  }

  return response;
}

int Handler::next_action_id() {
  int new_action_id = next_action_id_;
  next_action_id_++;
  return new_action_id;
}

void Handler::AddAction(const Request& request, Response* response) {
  auto action_id = next_action_id();
  actions_[action_id] = ModulesVector();
  statuses_[action_id] = message::RUNNING;
  results_[action_id] = message::Result();

  for (const auto& module : request.action.modules) {
    auto arguments = ConvertProcessToArguments(&module);
    actions_[action_id].push_back(std::make_shared<runner::Child>(arguments));
  }
  for (const auto& simulator : request.action.simulators) {
    auto arguments = ConvertProcessToArguments(&simulator);
    actions_[action_id].push_back(std::make_shared<runner::Child>(arguments));
  }

  for (const auto& runner : actions_[action_id]) {
    runner->Launch();
  }

  response->action_id = action_id;
  response->type = RESPONSE_ADD_ACTION;
}

std::vector<std::string> Handler::ConvertProcessToArguments(
    const message::Process* process) {
  std::vector<std::string> arguments;
  arguments.push_back(process->command);
  for (const auto& parameter : process->parameters) {
    arguments.push_back(parameter);
  }
  return arguments;
}

void Handler::PrintRawRequest(const std::vector<unsigned char>& raw_request) {
  std::cout << "get request: ";
  PrintRawMessage(raw_request);
}
void Handler::PrintRawResponse(const std::vector<unsigned char>& raw_response) {
  std::cout << "post response: ";
  PrintRawMessage(raw_response);
}

void Handler::PrintRawMessage(const std::vector<unsigned char>& raw_message) {
  for (const auto& c : raw_message) {
    std::cout << c;
  }
  std::cout << std::endl;
}

void Handler::RemoveAction(const Request& request, Response* response) {
  const auto& action_id = request.action_id;
  statuses_[action_id] = message::COMPLETED;

  for (const auto& runner : actions_[action_id]) {
    runner->Shutdown();
  }

  response->action_id = action_id;
  response->type = RESPONSE_REMOVE_ACTION;
}

void Handler::GetActionStatus(const Request& request, Response* response) {
  const auto& action_id = request.action_id;
  
  response->action_id = action_id;
  response->type = RESPONSE_GET_ACTION_STATUS;
  response->status = statuses_[action_id];
}

void Handler::GetActionResult(const Request& request, Response* response) {
  const auto& action_id = request.action_id;
  
  response->action_id = action_id;
  response->type = RESPONSE_GET_ACTION_STATUS;
  response->result = results_[action_id];
}

void Handler::Invalid(const Request& request, Response* response) {
  // ignore an unsupported request
}
