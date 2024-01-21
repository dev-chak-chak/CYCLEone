from abc import ABC, abstractmethod


class AdapterBase(ABC):
    '''
    serializing/parsing to/from interface data format
    '''
    @abstractmethod
    def SerializeAction(self, action):
        ...

    @abstractmethod
    def SerializeRemove(self, action_id: int):
        ...

    @abstractmethod
    def SerializeStatus(self, action_id: int):
        ...

    @abstractmethod
    def SerializeResult(self, action_id: int):
        ...

    @abstractmethod
    def Serialize(self, request):
        ...

    @abstractmethod
    def Parse(self, response_msg):
        ...
