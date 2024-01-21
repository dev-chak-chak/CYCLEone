import os
import sys
import json

sys.path.append(os.path.join(os.getcwd(), 'src', 'cycleon'))  # nopep8
from network.message.request import Request, \
                                    Type as ReqType, \
                                    RequestEncoder  # nopep8
from network.message.action.action import Action  # nopep8
from network.message.action.module import Module  # nopep8
from network.message.action.simulator import Simulator  # nopep8


def test_invalid_default():
    request = Request()
    assert request.type == ReqType.INVALID


def test_action_set():
    action = Action()
    action.AddModule(Module('launch', ['core', 'par1', 'par2']))
    request = Request()
    request.SetAction(action)
    assert request.type == ReqType.ADD_ACTION


def test_action_id_set():
    request = Request()
    action_id = 1
    request.SetRemove(action_id)
    assert request.action_id == action_id


def test_remove_set():
    request = Request()
    request.SetRemove(1)
    assert request.type == ReqType.REMOVE_ACTION


def test_status_set():
    request = Request()
    request.SetStatus(1)
    assert request.type == ReqType.GET_ACTION_STATUS


def test_status_set():
    request = Request()
    request.SetResult(1)
    assert request.type == ReqType.GET_ACTION_RESULT


def test_encode_to_json():
    action = Action()
    action.AddModule(Module('launch', ['core', 'par1', 'par2']))
    action.AddSimulator(Simulator('sim', ['par3', 'par4']))
    request = Request()
    request.SetAction(action)
    assert json.dumps(
        request, cls=RequestEncoder) == '{"type": 1, "action_id": -1, "action": {"modules": [{"command": "launch", "parameters": ["core", "par1", "par2"]}], "simulators": [{"command": "sim", "parameters": ["par3", "par4"]}]}}'
