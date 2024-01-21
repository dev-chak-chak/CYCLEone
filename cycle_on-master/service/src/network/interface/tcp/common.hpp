#ifndef NETWORK_TCP_COMMON_H_
#define NETWORK_TCP_COMMON_H_

#include <boost/asio.hpp>
#include <vector>

namespace ba = boost::asio;
typedef ba::ip::tcp::socket TcpSocket;

namespace cycleon {
namespace network {

class TcpBase {
 public:
  TcpBase();
  TcpBase(const std::string& address, unsigned short port);
  virtual ~TcpBase();
  void SetAddress(const std::string& address);
  void SetPort(unsigned short port);

 protected:
  std::vector<unsigned char> Read(TcpSocket& socket);
  unsigned int ReadUInt32(TcpSocket& socket);
  std::vector<unsigned char> ReadBytes(TcpSocket& socket, unsigned int count);
  void Write(TcpSocket& socket, const std::vector<unsigned char>& buffer);
  void WriteUInt32(TcpSocket& socket, unsigned int count);
  void WriteBytes(TcpSocket& socket, const std::vector<unsigned char>& buffer);

  std::vector<unsigned char> ConvertIntToBytes(const unsigned int& number);
  unsigned int ConvertBytesToInt(const std::vector<unsigned char>& bytes);

  std::string address_;
  unsigned short port_;
};

}  // namespace network
}  // namespace cycleon

#endif  // NETWORK_TCP_COMMON_H_