from enum import Enum
import json

from network.message.action.action import Action


class Type(Enum):
    INVALID = 0
    ADD_ACTION = 1
    REMOVE_ACTION = 2
    GET_ACTION_STATUS = 3
    GET_ACTION_RESULT = 4

    def toJSON(self):
        return self.value


class Request:
    def __init__(self) -> None:
        self._type = Type.INVALID
        self._action_id = -1
        self._action = Action()

    @property
    def type(self) -> Type:
        return self._type

    @property
    def action_id(self) -> Type:
        return self._action_id

    def SetAction(self, action):
        self._action = action
        self._type = Type.ADD_ACTION

    def SetRemove(self, action_id):
        self._action_id = action_id
        self._type = Type.REMOVE_ACTION

    def SetStatus(self, action_id):
        self._action_id = action_id
        self._type = Type.GET_ACTION_STATUS

    def SetResult(self, action_id):
        self._action_id = action_id
        self._type = Type.GET_ACTION_RESULT


class RequestEncoder(json.JSONEncoder):
    def default(self, request):
        if isinstance(request, Request):
            return {
                'type': request.type.value,
                'action_id': request.action_id,
                'action': {
                    'modules': [
                        {
                            'command': m.command,
                            'parameters': m.parameters}
                        for m in request._action.modules
                    ],
                    'simulators': [
                        {
                            'command': m.command,
                            'parameters': m.parameters}
                        for m in request._action.simulators
                    ],
                },
            }
        return json.JSONEncoder.default(self, request)
