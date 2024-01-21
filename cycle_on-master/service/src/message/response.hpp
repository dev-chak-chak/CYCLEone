#ifndef MESSAGE_RESPONSE_H_
#define MESSAGE_RESPONSE_H_

#include <string>

namespace cycleon {
namespace message {

enum ResponseType {
    RESPONSE_INVALID = 0,
    RESPONSE_ADD_ACTION = 1,
    RESPONSE_REMOVE_ACTION = 2,
    RESPONSE_GET_ACTION_STATUS = 3,
    RESPONSE_GET_ACTION_RESULT = 4,
};

enum Status {
    STATUS_INVALID = 0,
    WAITING = 1,
    RUNNING = 2,
    COMPLETED = 3,
};

enum ResultType {
    RESULT_INVALID = 0,
    PASS = 1,
    FAIL = 2,
    ERROR = 3,
};

class Result {
  public:
    Result(): type(RESULT_INVALID), message("") {}
    ResultType type;
    std::string message;
};

class Response {
  public:
    Response(): action_id(-1), type(RESPONSE_INVALID), status(STATUS_INVALID) {}
    int action_id;
    ResponseType type;
    Status status;
    Result result;
};

}  // namespace config
}  // namespace cycleon

#endif  // MESSAGE_RESPONSE_H_
