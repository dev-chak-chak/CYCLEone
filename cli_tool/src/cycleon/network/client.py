from .interface.interface import InterfaceBase
from .adapter.adapter import AdapterBase


class Client:
    def __init__(self) -> None:
        self._interface = None
        self._adapter = None

    @property
    def interface(self) -> InterfaceBase:
        return self._interface

    @interface.setter
    def interface(self, interface: InterfaceBase) -> None:
        self._interface = interface

    @property
    def adapter(self) -> AdapterBase:
        return self._adapter

    @adapter.setter
    def adapter(self, adapter: AdapterBase) -> None:
        self._adapter = adapter

    def Add(self, action) -> int:
        request = self._adapter.SerializeAction(action)
        response = self._send_and_get_response(request)
        return response.action_id

    def Remove(self, action_id: int):
        request = self._adapter.SerializeRemove(action_id)
        self._send_and_get_response(request)

    def GetStatus(self, action_id: int):
        request = self._adapter.SerializeStatus(action_id)
        response = self._send_and_get_response(request)
        return response.status

    def GetResult(self, action_id: int):
        request = self._adapter.SerializeResult(action_id)
        response = self._send_and_get_response(request)
        return response.result

    def _send_and_get_response(self, request_msg):
        response_msg = self._interface.SendAndRecieve(request_msg)
        response = self._adapter.Parse(response_msg)
        return response
