from network.message.action.action import Action


class Network:
    def __init__(self) -> None:
        self._address = ''
        self._port = -1

    @property
    def address(self) -> str:
        return self._address

    @address.setter
    def address(self, address: str) -> None:
        self._address = address

    @property
    def port(self) -> int:
        return self._port

    @port.setter
    def port(self, port: int) -> None:
        self._port = port


class Config:
    def __init__(self) -> None:
        self._network = Network()
        self._action = Action()

    @property
    def network(self) -> Network:
        return self._network

    @network.setter
    def network(self, network: Network) -> None:
        self._network = network

    @property
    def action(self) -> Action:
        return self._action

    @action.setter
    def action(self, action: Action) -> None:
        self._action = action
