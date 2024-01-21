#ifndef RUNNER_CHILD_H_
#define RUNNER_CHILD_H_

#include <boost/process/child.hpp>
#include <boost/process/group.hpp>
#include <memory>

#include "runner/module.hpp"

namespace bp = boost::process;
typedef std::shared_ptr<bp::child> childPtr;

namespace cycleon {
namespace runner {

class Child final : public ModuleBase {
 public:
  Child(const std::vector<std::string>& arguments);
  void Open() override;
  void Close() override;

 private:
  childPtr child_;
  bp::group group_;
  std::vector<std::string> arguments_;
};

}  // namespace runner
}  // namespace cycleon

#endif  // RUNNER_CHILD_H_
