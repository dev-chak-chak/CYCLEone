#ifndef NETWORK_TCP_SERVER_H_
#define NETWORK_TCP_SERVER_H_

#include <atomic>
#include <boost/asio.hpp>
#include <functional>

#include "network/interface/tcp/common.hpp"

namespace cycleon {
namespace network {

class TcpSession : public std::enable_shared_from_this<TcpSession>, TcpBase {
 public:
  TcpSession(TcpSocket socket);
  void SetProcessRequest(
    std::function<std::vector<unsigned char>(const std::vector<unsigned char>&)> func);
  void start();
 private:
  void do_read_header();
  void do_read_body();
  void do_write_header();
  void do_write_body();

  TcpSocket socket_;
  std::vector<unsigned char> request_header_;
  std::vector<unsigned char> request_;
  std::vector<unsigned char> response_header_;
  std::vector<unsigned char> response_;
  std::function<std::vector<unsigned char>(const std::vector<unsigned char>&)> ProcessRequest;
};

class TcpServer final : public TcpBase {
 public:
  TcpServer(ba::io_context& io_context, unsigned short port);
  virtual ~TcpServer();
  void SetProcessRequest(
    std::function<std::vector<unsigned char>(const std::vector<unsigned char>&)> func);
  
 private:
  void do_accept();
  ba::ip::tcp::acceptor acceptor_;
  std::function<std::vector<unsigned char>(const std::vector<unsigned char>&)> ProcessRequest;
};

}  // namespace network
}  // namespace cycleon

#endif  // NETWORK_TCP_SERVER_H_