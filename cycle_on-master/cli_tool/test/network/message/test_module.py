import os
import sys

sys.path.append(os.path.join(os.getcwd(), 'src', 'cycleon'))  # nopep8
from network.message.action.module import Module  # nopep8


def test_module_ctor():
    cmd = 'command'
    params = ['par1', 'par2']
    module = Module(cmd, params)

    assert module.command == cmd
    assert module.parameters == params
