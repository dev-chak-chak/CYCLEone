#ifndef PROCESSOR_PROCESSOR_H_
#define PROCESSOR_PROCESSOR_H_

#include <vector>

namespace cycleon {
namespace processor {

class ProcessorBase {
 public:
  virtual ~ProcessorBase() {}
  virtual std::vector<unsigned char> Process(
      const std::vector<unsigned char>& request) = 0;
};

}  // namespace processor
}  // namespace cycleon

#endif  // PROCESSOR_PROCESSOR_H_
