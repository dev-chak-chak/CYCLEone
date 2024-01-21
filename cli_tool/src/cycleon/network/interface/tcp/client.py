from .common import Common
from ..interface import InterfaceBase

from socket import SHUT_RDWR


class Client(InterfaceBase, Common):
    def __init__(self,
                 address='localhost',
                 port=8181,
                 timeout=1.0) -> None:
        super().__init__()
        self._address = address
        self._port = port
        self._my_socket.settimeout(timeout)

    def SendAndRecieve(self, request_msg: bytearray) -> bytearray:
        self._connect()
        self._write(self._my_socket, request_msg)
        response_msg = self._read(self._my_socket)
        self._disconnect()
        return response_msg

    def _connect(self):
        self._my_socket.connect((self._address, self._port))

    def _disconnect(self):
        self._my_socket.shutdown(SHUT_RDWR)
        self._my_socket.close()
