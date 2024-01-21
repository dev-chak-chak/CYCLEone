#include <iostream>

#include "server/server.hpp"

int main() {
  cycleon::Server server;
  std::cout << "Starting service at 8181 port" << std::endl;
  server.Run();
  return 0;
}
