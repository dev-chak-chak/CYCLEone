#include "config/config.hpp"

#include <gtest/gtest.h>

#include <boost/filesystem.hpp>

#include "config/json.hpp"
#include "config/config_reader.hpp"

using namespace cycleon::config;
namespace bf = boost::filesystem;
typedef std::shared_ptr<Json> JsonPtr;

class ConfigTest : public ::testing::Test {
 protected:
  Config config;
  ConfigReader config_reader;
};

TEST_F(ConfigTest, IsConstructed) {}

// TEST_F(ConfigTest, ConstructedWithNoPath) {
//   JsonPtr json_impl = std::make_shared<config::Json>();
//   config.setImplementation(json_impl);
// }

TEST_F(ConfigTest, ThrowIfJsonNotExists) {
  std::string config_path = "non_existed.json";
  ASSERT_FALSE(bf::exists(config_path));
  JsonPtr json_impl = std::make_shared<Json>();
  config_reader.setImplementation(json_impl);
  EXPECT_ANY_THROW({ config_reader.Open(config_path); });
}

TEST_F(ConfigTest, OpenJson) {
  std::string config_path = "config_test.json";
  ASSERT_TRUE(bf::exists(config_path));

  JsonPtr json_impl = std::make_shared<Json>();
  config_reader.setImplementation(json_impl);
  config = config_reader.Open(config_path);

  EXPECT_STREQ(config.network.address.c_str(), "localhost");
  EXPECT_EQ(config.network.port, 8181);
}
