#include <gtest/gtest.h>

#include <chrono>
#include <functional>
#include <iostream>
#include <thread>
#include <atomic>

#include "network/interface/tcp/client.hpp"
#include "network/interface/tcp/server.hpp"
#include "processor/echo.hpp"

using namespace cycleon;


TEST(Tcp, Echo) {
  ba::io_context server_io_context;
  const unsigned short port = 8181;
  const char port_str[] = "8181";
  ::network::TcpServer tcp_server(server_io_context, port);

  ::processor::Echo echo_processor;
  using std::placeholders::_1;
  std::function<std::vector<unsigned char>(const std::vector<unsigned char>&)>
      process_request =
          std::bind(&::processor::Echo::Process, &echo_processor, _1);
  tcp_server.SetProcessRequest(process_request);
  
  std::thread server_thread([&]{
    try {
      server_io_context.run();
    } catch (std::exception& e) {
      std::cerr << "Server exception: " << e.what() << "\n";
    }
  });

  std::vector<unsigned char> request= {'H','e','l','l','o',',',' ','y','o','u',};
  std::vector<unsigned char> expected_response = {
    'E','c','h','o',':',' ','H','e','l','l','o',',',' ','y','o','u',};
  std::vector<unsigned char> response;
  try
  {
    ba::io_context client_io_context;
    ba::ip::tcp::resolver resolver(client_io_context);
    auto endpoints = resolver.resolve("localhost", port_str);
    ::network::TcpClient tcp_client(client_io_context, endpoints, request);

    client_io_context.run();
    response = tcp_client.GetResponse();
  }
  catch (std::exception& e)
  {
    std::cerr << "Client exception: " << e.what() << "\n";
  }

  server_io_context.stop();
  server_thread.join(); 

  EXPECT_EQ(expected_response, response);
}
