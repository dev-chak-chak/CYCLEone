#ifndef MESSAGE_REQUEST_H_
#define MESSAGE_REQUEST_H_

#include <memory>
#include <vector>

#include "message/action.hpp"

namespace cycleon {
namespace message {

enum RequestType {
    REQUEST_INVALID = 0,
    REQUEST_ADD_ACTION = 1,
    REQUEST_REMOVE_ACTION = 2,
    REQUEST_GET_ACTION_STATUS = 3,
    REQUEST_GET_ACTION_RESULT = 4,
};

class Request {
  public:
    Action action;
    int action_id;
    RequestType type;
};

}  // namespace config
}  // namespace cycleon

#endif  // MESSAGE_REQUEST_H_
