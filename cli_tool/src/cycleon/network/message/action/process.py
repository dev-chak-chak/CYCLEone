from abc import ABC
from typing import List


class Process(ABC):
    def __init__(self,
                 command: str,
                 parameters: List[str]) -> None:
        self._command = command
        self._parameters = parameters
        pass

    @property
    def command(self) -> str:
        return self._command

    @property
    def parameters(self) -> List[str]:
        return self._parameters
