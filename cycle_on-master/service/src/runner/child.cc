#include "runner/child.hpp"

#include <boost/process/args.hpp>
#include <cstdlib>
#include <string>
#include <vector>

using namespace cycleon::runner;

Child::Child(const std::vector<std::string>& arguments)
    : arguments_(arguments) {}

void Child::Open() {
    child_.reset(new bp::child(bp::args(arguments_), group_));
    // std::cout << "Child: id " << child_->id() << std::endl;
    }

void Child::Close() {
    group_.terminate();
    child_->wait();
    // std::cout << "Child: exit_code " << child_->exit_code() << std::endl;
    }
