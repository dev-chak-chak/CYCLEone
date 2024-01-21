#include "server.hpp"

#include <iostream>

#include "network/interface/tcp/server.hpp"
#include "processor/handler.hpp"

using namespace cycleon;
namespace ba = boost::asio;

void Server::Run() {
  ba::io_context io_context;
  const unsigned short port = 8181;
  ::network::TcpServer tcp_server(io_context, port);

  ::processor::Handler handler;
  using std::placeholders::_1;
  std::function<std::vector<unsigned char>(const std::vector<unsigned char>&)>
      process_request =
          std::bind(&::processor::Handler::Process, &handler, _1);
  tcp_server.SetProcessRequest(process_request);

  try {
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Server exception: " << e.what() << "\n";
  }

}
