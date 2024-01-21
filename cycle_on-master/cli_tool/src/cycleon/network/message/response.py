from enum import Enum
import json


class Type(Enum):
    INVALID = 0
    ADD_ACTION = 1
    REMOVE_ACTION = 2
    GET_ACTION_STATUS = 3
    GET_ACTION_RESULT = 4


class Status(Enum):
    INVALID = 0
    WAITING = 1
    RUNNING = 2
    COMPLETED = 3


class ResultType(Enum):
    INVALID = 0
    PASS = 1
    FAIL = 2
    ERROR = 3


class Result:
    def __init__(self) -> None:
        self._type = ResultType.INVALID
        self._message = ''
    
    def __str__(self) -> str:
        return f'({self._type},{self._message})'

    @property
    def type(self) -> ResultType:
        return self._type

    def SetType(self, result_type: ResultType) -> None:
        self._type = result_type

    @property
    def message(self) -> str:
        return self._message

    def SetMessage(self, message: str) -> None:
        self._message = message


class Response:
    def __init__(self) -> None:
        self._type = Type.INVALID
        self._action_id = -1
        self._status = Status.INVALID

    @property
    def type(self) -> Type:
        return self._type

    def SetType(self, type: Type) -> None:
        self._type = type

    @property
    def action_id(self) -> Type:
        return self._action_id

    def SetActionId(self, action_id: int) -> None:
        self._action_id = action_id

    @property
    def status(self) -> Type:
        return self._status

    def SetStatus(self, status):
        self._status = status

    @property
    def result(self) -> Result:
        return self._result

    def SetResult(self, result):
        self._result = result


class ResponseDecoder(json.JSONDecoder):
    def __init__(self, *args, **kwargs):
        json.JSONDecoder.__init__(
            self, object_hook=self.object_hook, *args, **kwargs)

    def object_hook(self, dct):
        if any(s not in dct for s in ('type', 'action_id', 'status', 'result')):
            return dct
        decoded_response = Response()
        decoded_response.SetType(Type(int(dct['type'])))
        decoded_response.SetActionId(int(dct['action_id']))
        decoded_response.SetStatus(Status(int(dct['status'])))
        decoded_result = Result()
        decoded_result.SetType(ResultType(int(dct['result']['type'])))
        decoded_result.SetMessage(dct['result']['message'])
        decoded_response.SetResult(decoded_result)

        return decoded_response
