#ifndef PROCESSOR_ECHO_H_
#define PROCESSOR_ECHO_H_

#include "processor/processor.hpp"

namespace cycleon {
namespace processor {

class Echo : public ProcessorBase {
 public:
  std::vector<unsigned char> Process(
      const std::vector<unsigned char>& request) override;
};

}  // namespace processor
}  // namespace cycleon

#endif  // PROCESSOR_ECHO_H_
