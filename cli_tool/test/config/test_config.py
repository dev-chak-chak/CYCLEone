import os
import sys
import json

sys.path.append(os.path.join(os.getcwd(), 'src', 'cycleon'))  # nopep8
from settings.reader import Reader  # nopep8
from settings.json import Json, ConfigDecoder  # nopep8


def test_decoder():
    print()
    encoded_json = '{"network": {"address": "localhost", "port": 8181}, "action": {"modules": [{"command": "launch", "parameters": ["core", "par1", "par2"]}], "simulators": [{"command": "sim", "parameters": ["par3", "par4"]}]}}'
    config = json.loads(encoded_json, cls=ConfigDecoder)
    print(f'config: {config}')

    assert config.network.address == "localhost"
    assert config.network.port == 8181

    assert config.action.modules[0].command == "launch"
    assert config.action.modules[0].parameters == ["core", "par1", "par2"]

    assert config.action.simulators[0].command == "sim"
    assert config.action.simulators[0].parameters == ["par3", "par4"]


def test_read_json():
    config_path = 'test/data/config_test.json'
    config_reader = Reader()
    config_reader.implementation = Json()
    config = config_reader.Open(config_path)

    assert config.network.address == "localhost"
    assert config.network.port == 8181

    assert config.action.modules[0].command == "launch"
    assert config.action.modules[0].parameters == ["core", "par1", "par2"]

    assert config.action.simulators[0].command == "sim"
    assert config.action.simulators[0].parameters == ["par3", "par4"]
