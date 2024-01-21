#include "network/interface/tcp/server.hpp"

#include <iostream>

using namespace cycleon::network;

TcpSession::TcpSession(TcpSocket socket)
    : socket_(std::move(socket)), request_header_(std::vector<unsigned char>(4)),
      response_header_(std::vector<unsigned char>(4))
{}

void TcpSession::SetProcessRequest(
    std::function<std::vector<unsigned char>(
      const std::vector<unsigned char>&)> func) {
  ProcessRequest = func;
}

void TcpSession::start() { do_read_header(); }

void TcpSession::do_read_header() {
    auto self(shared_from_this());
    ba::async_read(socket_, boost::asio::buffer(request_header_),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            do_read_body();
          } else {
            std::cerr << "TcpSession: read header failed" << std::endl;
          }
        });
  }

void TcpSession::do_read_body() {
    auto self(shared_from_this());
    request_ = std::vector<unsigned char>(ConvertBytesToInt(request_header_));
    ba::async_read(socket_, boost::asio::buffer(request_),
        [this, self](boost::system::error_code ec, std::size_t length)
        {
          if (!ec)
          {
            response_ = ProcessRequest(request_);
            response_header_ = ConvertIntToBytes(response_.size());
            do_write_header();
          } else {
            std::cerr << "TcpSession: read body failed" << std::endl;
          }
        });
  }

void TcpSession::do_write_header() {
  auto self(shared_from_this());
  ba::async_write(
      socket_, boost::asio::buffer(response_header_),
      [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
            do_write_body();
        } else {
            std::cerr << "TcpSession: write header failed" << std::endl;
        }
      });
}

void TcpSession::do_write_body() {
  auto self(shared_from_this());
  ba::async_write(
      socket_, boost::asio::buffer(response_),
      [this, self](boost::system::error_code ec, std::size_t /*length*/) {
        if (!ec) {
                    // do nothing
        } else {
            std::cerr << "TcpSession: write body failed" << std::endl;
        }
      });
}

TcpServer::TcpServer(ba::io_context& io_context, unsigned short port)
    : acceptor_(io_context, ba::ip::tcp::endpoint(ba::ip::tcp::v4(), port)) {
  do_accept();
}

TcpServer::~TcpServer() { }

void TcpServer::SetProcessRequest(
    std::function<std::vector<unsigned char>(
      const std::vector<unsigned char>&)> func) {
  ProcessRequest = func;
}

void TcpServer::do_accept() {
  acceptor_.async_accept(
      [this](boost::system::error_code ec, TcpSocket socket) {
        if (!ec) {
          auto sesstion_ptr = std::make_shared<TcpSession>(std::move(socket));
          sesstion_ptr->SetProcessRequest(ProcessRequest);
          sesstion_ptr->start();
        } else {
          std::cerr << "TcpServer: accept failed" << std::endl;
        }
        do_accept();
      });
}
