#include "processor/echo.hpp"

#include <algorithm>

using namespace cycleon::processor;

std::vector<unsigned char> Echo::Process(
    const std::vector<unsigned char>& request) {
  const std::vector<unsigned char> echo_prefix = {'E', 'c', 'h', 'o', ':', ' '};
  std::vector<unsigned char> response(echo_prefix.size() + request.size());

  std::copy(echo_prefix.begin(), echo_prefix.end(), response.begin());
  std::copy(request.begin(), request.end(), response.begin() + echo_prefix.size());

  return response;
}
