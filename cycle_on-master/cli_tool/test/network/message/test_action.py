import os
import sys

sys.path.append(os.path.join(os.getcwd(), 'src', 'cycleon'))  # nopep8
from network.message.action.action import Action  # nopep8
from network.message.action.module import Module  # nopep8
from network.message.action.simulator import Simulator  # nopep8


def test_module_added_to_action():
    action = Action()
    command = 'launch'
    params = ['core', 'par1', 'par2']
    module = Module(command, params)
    action.AddModule(module)

    assert action.modules[0] == module


def test_simulator_added_to_action():
    action = Action()
    command = 'sim'
    params = ['par1', 'par2']
    simulator = Simulator(command, params)
    action.AddSimulator(simulator)

    assert action.simulators[0] == simulator
