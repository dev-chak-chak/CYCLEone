from .implementation import Implementation
from .config import Config


class Reader:
    def __init__(self) -> None:
        self._implementation = None

    @property
    def implementation(self) -> Implementation:
        return self._implementation

    @implementation.setter
    def implementation(self, implementation: Implementation) -> None:
        self._implementation = implementation

    def Open(self, path) -> Config:
        return self._implementation.Open(path)
