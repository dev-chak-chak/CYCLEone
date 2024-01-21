from abc import ABC, abstractmethod
from .config import Config


class Implementation(ABC):
    @abstractmethod
    def Open(self, path) -> Config:
        ...
