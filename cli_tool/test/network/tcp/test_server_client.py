import os
import sys
from threading import Thread


sys.path.append(os.path.join(os.getcwd(), 'src', 'cycleon'))  # nopep8
from network.interface.tcp.server import Server as TcpServer  # nopep8
from network.interface.tcp.client import Client as TcpClient  # nopep8


def test_tcp_echo():
    tcp_server = TcpServer(timeout=0.01)
    tcp_client = TcpClient()

    server_thread = Thread(target=tcp_server.BlockingRun)
    server_thread.start()

    request = 'Hello you!'
    request_msg = request.encode('utf-8')
    response_msg = tcp_client.SendAndRecieve(request_msg)
    response = response_msg.decode("utf-8")

    tcp_server.Stop()
    server_thread.join()

    assert response == f'Echo: {request}'
