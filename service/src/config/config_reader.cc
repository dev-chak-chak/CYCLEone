#include "config/config_reader.hpp"

using namespace cycleon::config;

void ConfigReader::setImplementation(ImplPtr implementation) {
  implementation_ = implementation;
}

Config ConfigReader::Open(const std::string& path) {
  return implementation_->Open(path);
}
