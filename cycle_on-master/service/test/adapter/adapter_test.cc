#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <nlohmann/json.hpp>

#include "network/adapter/json_over_tcp.hpp"

using namespace cycleon;
using json = nlohmann::json;

std::vector<unsigned char> PrepareRawFrom(const std::string& input) {
  std::vector<unsigned char> raw_data;
  raw_data.reserve(input.size());
  for (const auto& c : input) {
    raw_data.push_back(c);
  }
  return raw_data;
}

TEST(JsonOverTcpTest, AddActionRequest) {
  ::adapter::JsonOverTcp json_over_tcp_adapter;
  auto raw_request = PrepareRawFrom(
      R"({"action":{)"
        R"("modules":[{"command":"cmd_1","parameters":["par_1","par_2"]}],)"
        R"("simulators":[{"command":"sim_1","parameters":["par_3","par_4"]}])"
      R"(},)"
      R"("action_id":-1,"type":1})");

  auto request = json_over_tcp_adapter.GetRequest(raw_request);

  EXPECT_EQ(request.action_id, -1);
  EXPECT_EQ(request.type, ::message::REQUEST_ADD_ACTION);

  ASSERT_EQ(request.action.modules.size(), 1);
  EXPECT_STREQ(request.action.modules[0].command.c_str(), "cmd_1");
  EXPECT_EQ(request.action.modules[0].parameters.size(), 2);
  EXPECT_STREQ(request.action.modules[0].parameters[0].c_str(), "par_1");
  EXPECT_STREQ(request.action.modules[0].parameters[1].c_str(), "par_2");

  ASSERT_EQ(request.action.simulators.size(), 1);
  EXPECT_STREQ(request.action.simulators[0].command.c_str(), "sim_1");
  EXPECT_EQ(request.action.simulators[0].parameters.size(), 2);
  EXPECT_STREQ(request.action.simulators[0].parameters[0].c_str(), "par_3");
  EXPECT_STREQ(request.action.simulators[0].parameters[1].c_str(), "par_4");
}

TEST(JsonOverTcpTest, RemoveActionRequest) {
  ::adapter::JsonOverTcp json_over_tcp_adapter;
  auto raw_request = PrepareRawFrom(
      R"({"action_id":12,"type":2})");
  
  auto request = json_over_tcp_adapter.GetRequest(raw_request);

  EXPECT_EQ(request.action_id, 12);
  EXPECT_EQ(request.type, ::message::REQUEST_REMOVE_ACTION);
  EXPECT_EQ(request.action.modules.size(), 0);
  EXPECT_EQ(request.action.simulators.size(), 0);
}

TEST(JsonOverTcpTest, GetActionStatusRequest) {
  ::adapter::JsonOverTcp json_over_tcp_adapter;
  auto raw_request = PrepareRawFrom(
      R"({"action":{},)"
      R"("action_id":13,"type":3})");
  
  auto request = json_over_tcp_adapter.GetRequest(raw_request);

  EXPECT_EQ(request.action_id, 13);
  EXPECT_EQ(request.type, ::message::REQUEST_GET_ACTION_STATUS);
  EXPECT_EQ(request.action.modules.size(), 0);
  EXPECT_EQ(request.action.simulators.size(), 0);
}

TEST(JsonOverTcpTest, GetActionResultRequest) {
  ::adapter::JsonOverTcp json_over_tcp_adapter;
  auto raw_request = PrepareRawFrom(
      R"({"action":{)"
        R"("modules":[])"
      R"(},)"
      R"("action_id":14,"type":4})");

  auto request = json_over_tcp_adapter.GetRequest(raw_request);

  EXPECT_EQ(request.action_id, 14);
  EXPECT_EQ(request.type, ::message::REQUEST_GET_ACTION_RESULT);
  EXPECT_EQ(request.action.modules.size(), 0);
  EXPECT_EQ(request.action.simulators.size(), 0);
}

 nlohmann::json ConvertRawToJson(const std::vector<unsigned char>& raw_input) {
  std::string data(raw_input.begin(), raw_input.end());
  auto data_json = json::parse(data);
  return data_json;
}

TEST(JsonOverTcpTest, AddActionResponse) {
  ::adapter::JsonOverTcp json_over_tcp_adapter;
  ::message::Response response;
  response.action_id = 11;
  response.type = ::message::RESPONSE_ADD_ACTION;
  response.status = ::message::STATUS_INVALID;
  response.result.message = "";
  response.result.type = ::message::RESULT_INVALID;

  auto raw_request = json_over_tcp_adapter.CreateResponse(response);

  auto request_json = ConvertRawToJson(raw_request);
  EXPECT_EQ(request_json.at("action_id").get<int>(), 11);
  EXPECT_EQ(request_json.at("type").get<int>(), ::message::RESPONSE_ADD_ACTION);
  EXPECT_EQ(request_json.at("status").get<int>(), ::message::STATUS_INVALID);
  EXPECT_EQ(request_json.at("result").at("message").get<std::string>(), "");
  EXPECT_EQ(request_json.at("result").at("type").get<int>(), ::message::RESULT_INVALID);
}

TEST(JsonOverTcpTest, GetActionStatusResponse) {
  ::adapter::JsonOverTcp json_over_tcp_adapter;
  ::message::Response response;
  response.action_id = 12;
  response.type = ::message::RESPONSE_GET_ACTION_STATUS;
  response.status = ::message::COMPLETED;
  response.result.message = "";
  response.result.type = ::message::RESULT_INVALID;

  auto raw_request = json_over_tcp_adapter.CreateResponse(response);

  auto request_json = ConvertRawToJson(raw_request);
  EXPECT_EQ(request_json.at("action_id").get<int>(), 12);
  EXPECT_EQ(request_json.at("type").get<int>(), ::message::RESPONSE_GET_ACTION_STATUS);
  EXPECT_EQ(request_json.at("status").get<int>(), ::message::COMPLETED);
  EXPECT_EQ(request_json.at("result").at("message").get<std::string>(), "");
  EXPECT_EQ(request_json.at("result").at("type").get<int>(), ::message::RESULT_INVALID);
}

TEST(JsonOverTcpTest, GetActionResultResponse) {
  ::adapter::JsonOverTcp json_over_tcp_adapter;
  ::message::Response response;
  response.action_id = 13;
  response.type = ::message::RESPONSE_GET_ACTION_RESULT;
  response.status = ::message::STATUS_INVALID;
  response.result.message = "everything looks good!";
  response.result.type = ::message::PASS;

  auto raw_request = json_over_tcp_adapter.CreateResponse(response);

  auto request_json = ConvertRawToJson(raw_request);
  EXPECT_EQ(request_json.at("action_id").get<int>(), 13);
  EXPECT_EQ(request_json.at("type").get<int>(), ::message::RESPONSE_GET_ACTION_RESULT);
  EXPECT_EQ(request_json.at("status").get<int>(), ::message::STATUS_INVALID);
  EXPECT_EQ(request_json.at("result").at("message").get<std::string>(), "everything looks good!");
  EXPECT_EQ(request_json.at("result").at("type").get<int>(), ::message::PASS);
}
