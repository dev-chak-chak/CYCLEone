#ifndef NETWORK_TCP_CLIENT_H_
#define NETWORK_TCP_CLIENT_H_

#include <boost/asio.hpp>
#include <vector>

#include "network/interface/tcp/common.hpp"

namespace ba = boost::asio;

namespace cycleon {
namespace network {

class TcpClient final : public TcpBase {
 public:
  TcpClient(ba::io_context& io_context,
            const ba::ip::tcp::resolver::results_type& endpoints,
            const std::vector<unsigned char>& request);
  virtual ~TcpClient();
  std::vector<unsigned char> GetResponse();
 private:
  void do_connect();
  void do_write_header();
  void do_write_body();
  void do_read_header();
  void do_read_body();

  TcpSocket socket_;
  const ba::ip::tcp::resolver::results_type& endpoints_;
  const std::vector<unsigned char>& request_;
  std::vector<unsigned char> response_header_;
  std::vector<unsigned char> response_;
};

}  // namespace network
}  // namespace cycleon

#endif  // NETWORK_TCP_CLIENT_H_