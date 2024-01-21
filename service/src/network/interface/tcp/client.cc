#include "network/interface/tcp/client.hpp"

#include <iostream>

using namespace cycleon::network;

TcpClient::TcpClient(ba::io_context& io_context,
                     const ba::ip::tcp::resolver::results_type& endpoints,
                     const std::vector<unsigned char>& request)
    : socket_(io_context), endpoints_(endpoints), request_(request),
      response_header_(std::vector<unsigned char>(4))
{
  do_connect();
}

TcpClient::~TcpClient() {}

std::vector<unsigned char> TcpClient::GetResponse() { return response_; }

void TcpClient::do_connect() {
  ba::async_connect(
      socket_, endpoints_,
      [this](boost::system::error_code ec, ba::ip::tcp::endpoint) {
        if (!ec) {
          auto temp_header = ConvertIntToBytes(request_.size());
          do_write_header();
        } else {
          std::cerr << "TcpClient: connect fail" << std::endl;
        }
      });
}

void TcpClient::do_write_header() {
  ba::async_write(socket_, boost::asio::buffer(ConvertIntToBytes(request_.size())),
                  [this](boost::system::error_code ec, std::size_t /*length*/) {
                    if (!ec) {
                      do_write_body();
                    } else {
                      std::cerr << "TcpClient: write header fail" << std::endl;
                    }
                  });
}

void TcpClient::do_write_body() {
  ba::async_write(socket_, boost::asio::buffer(request_),
                  [this](boost::system::error_code ec, std::size_t /*length*/) {
                    if (!ec) {
                      do_read_header();
                    } else {
                      std::cerr << "TcpClient: write body fail" << std::endl;
                    }
                  });
}

void TcpClient::do_read_header() {
  ba::async_read(socket_, boost::asio::buffer(response_header_),
                 [this](boost::system::error_code ec, std::size_t /*length*/) {
                   if (!ec) {
                     do_read_body();
                   } else {
                     std::cerr << "TcpClient: read header fail" << std::endl;
                   }
                 });
}

void TcpClient::do_read_body() {
  response_ = std::vector<unsigned char>(ConvertBytesToInt(response_header_));
  ba::async_read(socket_, boost::asio::buffer(response_),
                 [this](boost::system::error_code ec, std::size_t /*length*/) {
                   if (!ec) {
                        //  do nothing
                   } else {
                     std::cerr << "TcpClient: read body fail" << std::endl;
                   }
                 });
}
