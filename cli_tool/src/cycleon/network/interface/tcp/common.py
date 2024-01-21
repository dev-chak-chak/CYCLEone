from socket import socket, AF_INET, SOCK_STREAM


class Common:
    def __init__(self) -> None:
        self._my_socket = socket(AF_INET, SOCK_STREAM)
        self._byte_order = 'little'
        self._buffer_size = 65535

    def _read(self, client: socket) -> bytearray:
        bytes_count = self.__read_uint32(client)
        data_bytes = self.__read_bytes(client, bytes_count)
        return data_bytes

    def __read_uint32(self, client: socket) -> int:
        int_bytes = self.__read_bytes(client, 4)
        return int.from_bytes(int_bytes, self._byte_order, signed=False)

    def __read_bytes(self, client: socket, count: int) -> bytearray:
        buffer = b''
        while len(buffer) < count:
            buffer += client.recv(count)
        return buffer

    def _write(self, client: socket, data_bytes: bytearray) -> None:
        bytes_count = len(data_bytes)
        self.__write_uint32(client, bytes_count)
        client.send(data_bytes)

    def __write_uint32(self, client: socket, count) -> None:
        int_bytes = count.to_bytes(4, self._byte_order, signed=False)
        client.send(int_bytes)
