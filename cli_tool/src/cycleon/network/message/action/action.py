from .module import Module
from .simulator import Simulator


class Action:
    def __init__(self) -> None:
        self._modules = []
        self._simulators = []

    @property
    def modules(self) -> int:
        return self._modules

    @property
    def simulators(self) -> int:
        return self._simulators

    def AddModule(self, module: Module):
        self._modules.append(module)

    def AddSimulator(self, simulator: Simulator):
        self._simulators.append(simulator)
