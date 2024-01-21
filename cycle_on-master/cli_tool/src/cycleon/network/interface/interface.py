from abc import ABC, abstractmethod


class InterfaceBase(ABC):
    @abstractmethod
    def SendAndRecieve(self, request_msg):
        ...
