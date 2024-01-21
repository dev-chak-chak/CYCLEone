#include "config/json.hpp"

#include <iostream>
// #include <boost/filesystem.hpp>
#include <fstream>

using namespace cycleon::config;
// namespace bf = boost::filesystem;

Config Json::Open(const std::string& path) {
  std::ifstream f(path);
  auto parsed_data = json::parse(f);
  Config config;
  std::cout << "parsed data: " << parsed_data << std::endl;
  parsed_data.at("network").at("address").get_to(config.network.address);
  parsed_data.at("network").at("port").get_to(config.network.port);
  return config;
};
