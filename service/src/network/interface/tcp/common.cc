#include "network/interface/tcp/common.hpp"

using namespace cycleon::network;

TcpBase::TcpBase() {}
TcpBase::TcpBase(const std::string& address, unsigned short port)
    : address_(address), port_(port) {}
TcpBase::~TcpBase() {}

void TcpBase::SetAddress(const std::string& address) { address_ = address; }
void TcpBase::SetPort(unsigned short port) { port_ = port; }

std::vector<unsigned char> TcpBase::Read(TcpSocket& socket) {
  auto count = ReadUInt32(socket);
  auto buffer = ReadBytes(socket, count);
  return buffer;
}

unsigned int TcpBase::ReadUInt32(TcpSocket& socket) {
  auto buffer = ReadBytes(socket, 4);
  auto count = ConvertBytesToInt(buffer);
  return count;
}

std::vector<unsigned char> TcpBase::ReadBytes(TcpSocket& socket,
                                              unsigned int count) {
  std::vector<unsigned char> buffer(count);
  ba::read(socket, ba::buffer(buffer, count));
  return buffer;
}

void TcpBase::Write(TcpSocket& socket,
                    const std::vector<unsigned char>& buffer) {
  WriteUInt32(socket, buffer.size());
  WriteBytes(socket, buffer);
}

void TcpBase::WriteUInt32(TcpSocket& socket, unsigned int count) {
  auto buffer = ConvertIntToBytes(count);
  WriteBytes(socket, buffer);
}

void TcpBase::WriteBytes(TcpSocket& socket,
                         const std::vector<unsigned char>& buffer) {
  ba::write(socket, ba::buffer(buffer, buffer.size()));
}

std::vector<unsigned char> TcpBase::ConvertIntToBytes(
    const unsigned int& number) {
  // little-endian implementation
  std::vector<unsigned char> bytes(4);
  bytes[0] = number & 0xFF;
  bytes[1] = (number >> 8) & 0xFF;
  bytes[2] = (number >> 16) & 0xFF;
  bytes[3] = (number >> 24) & 0xFF;
  return bytes;
}

unsigned int TcpBase::ConvertBytesToInt(
    const std::vector<unsigned char>& bytes) {
  // little-endian implementation
  unsigned int n;
  n = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24);
  return n;
}
