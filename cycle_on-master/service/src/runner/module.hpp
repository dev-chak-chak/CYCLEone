#ifndef RUNNER_MODULE_H_
#define RUNNER_MODULE_H_

namespace cycleon {
namespace runner {

class ModuleBase {
 public:
  virtual ~ModuleBase() {}
  void Launch() {
    Open();
    is_running_ = true;
  }
  void Shutdown() {
    Close();
    is_running_ = false;
  }
  bool isRunning() { return is_running_; }

 protected:
  virtual void Open() = 0;
  virtual void Close() = 0;

  bool is_running_ = false;
};

}  // namespace runner
}  // namespace cycleon

#endif  // RUNNER_MODULE_H_
