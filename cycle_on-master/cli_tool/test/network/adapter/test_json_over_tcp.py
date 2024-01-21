import os
import sys

sys.path.append(os.path.join(os.getcwd(), 'src', 'cycleon'))  # nopep8
from network.adapter.json_over_tcp import JsonOverTcp  # nopep8
from network.message.request import Request  # nopep8
from network.message.action.action import Action  # nopep8
from network.message.action.module import Module  # nopep8
from network.message.action.simulator import Simulator  # nopep8
from network.message.response import Type as ResponseType, \
                                     Status as ResponseStatus, \
                                     ResultType  # nopep8


def test_serialize_request():
    action = Action()
    action.AddModule(Module('launch', ['core', 'par1', 'par2']))
    action.AddSimulator(Simulator('sim', ['par3', 'par4']))
    request = Request()
    request.SetAction(action)

    adapter = JsonOverTcp()
    request_msg = adapter.Serialize(request)

    assert request_msg == b'{"type":1,"action_id":-1,"action":{"modules":[{"command":"launch","parameters":["core","par1","par2"]}],"simulators":[{"command":"sim","parameters":["par3","par4"]}]}}'


def test_parse_response():
    response_msg = b'{"type":4,"action_id":12,"status":0,"result":{"type":1,"message":"test passed"}}'

    adapter = JsonOverTcp()
    response = adapter.Parse(response_msg)

    assert response.type == ResponseType.GET_ACTION_RESULT
    assert response.action_id == 12
    assert response.status == ResponseStatus.INVALID
    assert response.result.type == ResultType.PASS
    assert response.result.message == 'test passed'


def test_wrap_action():
    action = Action()
    action.AddModule(Module('launch', ['core', 'par1', 'par2']))
    action.AddSimulator(Simulator('sim', ['par3', 'par4']))

    adapter = JsonOverTcp()
    request_msg = adapter.SerializeAction(action)

    assert request_msg == b'{"type":1,"action_id":-1,"action":{"modules":[{"command":"launch","parameters":["core","par1","par2"]}],"simulators":[{"command":"sim","parameters":["par3","par4"]}]}}'


def test_wrap_remove():
    adapter = JsonOverTcp()
    request_msg = adapter.SerializeRemove(12)
    assert request_msg == b'{"type":2,"action_id":12,"action":{"modules":[],"simulators":[]}}'


def test_wrap_status():
    adapter = JsonOverTcp()
    request_msg = adapter.SerializeStatus(12)
    assert request_msg == b'{"type":3,"action_id":12,"action":{"modules":[],"simulators":[]}}'


def test_wrap_result():
    adapter = JsonOverTcp()
    request_msg = adapter.SerializeResult(12)
    assert request_msg == b'{"type":4,"action_id":12,"action":{"modules":[],"simulators":[]}}'
