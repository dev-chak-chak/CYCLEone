import os
import sys
import json

sys.path.append(os.path.join(os.getcwd(), 'src', 'cycleon'))  # nopep8
from network.message.response import Response, \
                                     Type as ResponseType, \
                                     Status as ResponseStatus, \
                                     Result, ResultType, \
                                     ResponseDecoder  # nopep8


def test_request_defaults():
    response = Response()
    assert response.action_id == -1
    assert response.type == ResponseType.INVALID
    assert response.status == ResponseStatus.INVALID


def test_set_action_id():
    response = Response()
    action_id = 1
    response.SetActionId(action_id)
    assert response.action_id == action_id


def test_set_type():
    response = Response()
    res_type = ResponseType.ADD_ACTION
    response.SetType(res_type)
    assert response.type == res_type


def test_result():
    result = Result()
    assert result.type == ResultType.INVALID
    assert result.message == ''
    message = 'everything is good!'
    result.SetMessage(message)
    assert result.message == message
    result_type = ResultType.PASS
    result.SetType(result_type)
    assert result.type == result_type


def test_set_result():
    response = Response()

    result = Result()
    message = 'everything is good!'
    result.SetMessage(message)
    result_type = ResultType.PASS
    result.SetType(result_type)
    response.SetResult(result)

    assert response.result.type == result_type
    assert response.result.message == message


def test_decode_from_json():
    encoded_json = '{"type": 4, "action_id": 12, "status": 0, "result": {"type": 1, "message": "test passed"}}'
    response = json.loads(encoded_json, cls=ResponseDecoder)
    assert response.type == ResponseType.GET_ACTION_RESULT
    assert response.action_id == 12
    assert response.status == ResponseStatus.INVALID
    assert response.result.type == ResultType.PASS
    assert response.result.message == 'test passed'
