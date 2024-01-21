import json

from .adapter import AdapterBase
from network.message.request import Request, RequestEncoder
from network.message.response import Response, ResponseDecoder


class JsonOverTcp(AdapterBase):
    def SerializeAction(self, action) -> bytearray:
        request = Request()
        request.SetAction(action)
        request_msg = self.Serialize(request)
        return request_msg

    def SerializeRemove(self, action_id: int) -> bytearray:
        request = Request()
        request.SetRemove(action_id)
        request_msg = self.Serialize(request)
        return request_msg

    def SerializeStatus(self, action_id: int) -> bytearray:
        request = Request()
        request.SetStatus(action_id)
        request_msg = self.Serialize(request)
        return request_msg

    def SerializeResult(self, action_id: int) -> bytearray:
        request = Request()
        request.SetResult(action_id)
        request_msg = self.Serialize(request)
        return request_msg

    def Serialize(self, request: Request) -> bytearray:
        json_as_string = json.dumps(
            request, cls=RequestEncoder, separators=(',', ':'))
        json_as_bytes = json_as_string.encode('utf-8')
        return json_as_bytes

    def Parse(self, json_as_bytes: bytearray) -> Response:
        json_as_string = json_as_bytes.decode("utf-8")
        response = json.loads(json_as_string, cls=ResponseDecoder)
        return response
