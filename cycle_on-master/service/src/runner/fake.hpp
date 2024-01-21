#ifndef RUNNER_FAKE_H_
#define RUNNER_FAKE_H_

#include "runner/module.hpp"

namespace cycleon {
namespace runner {

class Fake : public ModuleBase {
 public:
  virtual ~Fake();
  void Open() override;
  void Close() override;

  virtual bool was_Open_called();
  virtual bool was_Close_called();

 protected:
  bool is_open_called_ = false;
  bool is_close_called_ = false;
};

}  // namespace runner
}  // namespace cycleon

#endif  // RUNNER_FAKE_H_
