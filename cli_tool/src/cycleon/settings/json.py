from .implementation import Implementation
from .config import Config
from network.message.action.action import Action
from network.message.action.module import Module
from network.message.action.simulator import Simulator
import json


class Json(Implementation):
    def Open(self, path) -> Config:
        with open(path) as f:
            data_as_string = f.read()
        return json.loads(data_as_string, cls=ConfigDecoder)


class ConfigDecoder(json.JSONDecoder):
    def __init__(self, *args, **kwargs):
        json.JSONDecoder.__init__(
            self, object_hook=self.object_hook, *args, **kwargs)

    def object_hook(self, dct):
        if any(s not in dct for s in ('network', 'action')):
            return dct
        config = Config()
        config.network.address = dct['network']['address']
        config.network.port = int(dct['network']['port'])

        action = Action()
        for json_module in dct['action']['modules']:
            module = Module(json_module['command'], json_module['parameters'])
            action.AddModule(module)
        for json_simulator in dct['action']['simulators']:
            simulator = Simulator(
                json_simulator['command'], json_simulator['parameters'])
            action.AddSimulator(simulator)
        config.action = action

        return config
