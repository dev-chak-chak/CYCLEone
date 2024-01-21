from socket import socket, SHUT_RDWR, SOL_SOCKET, SO_REUSEADDR, timeout
from typing import Callable, Tuple

from .common import Common


class Server(Common):
    def __init__(self,
                 address='localhost',  # address=socket.gethostname(),
                 port=8181,
                 max_clients=5,
                 timeout=1.0) -> None:
        super().__init__()
        self._address = address
        self._port = port
        self._max_clients = max_clients
        self._my_socket.settimeout(timeout)
        self._my_socket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        self._process_function = Server._echo
        self._open()

    def _open(self):
        self._my_socket.bind((self._address, self._port))
        self._my_socket.listen(self._max_clients)

    def BlockingRun(self):
        self._is_running = True
        while self._is_running:
            client_socket = None
            try:
                client_socket, address = self._my_socket.accept()
            except timeout:
                pass
            if client_socket:
                self._process_client(client_socket, address)
                client_socket.shutdown(SHUT_RDWR)
                client_socket.close()
        self._close()

    def _close(self):
        self._my_socket.shutdown(SHUT_RDWR)
        self._my_socket.close()

    def Stop(self):
        self._is_running = False

    def _process_client(self, client_socket: socket, address: str):
        request_msg = self._read(client_socket)
        response_msg = self._process(request_msg, address)
        self._write(client_socket, response_msg)

    def _process(self, request_msg: bytearray, address: str):
        response_msg = self._process_function(request_msg, address)
        return response_msg

    @property
    def process_function(self) -> callable:
        return self._process_function

    @process_function.setter
    def process_function(self, process_function: Callable) -> None:
        self._process_function = process_function

    @staticmethod
    def _echo(request_msg: bytearray, address: Tuple[str, int]) -> bytearray:
        request = request_msg.decode("utf-8")
        response = f'Echo: {request}'
        return response.encode('utf-8')
