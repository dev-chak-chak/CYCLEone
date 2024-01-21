import argparse

from settings.reader import Reader as ConfigReader
from settings.json import Json as JsonConfig
from network.client import Client
from network.interface.tcp.client import Client as TcpClient
from network.adapter.json_over_tcp import JsonOverTcp as JsonTcpAdapter


def process(args):
    GLOBAL_CONFIG_PATH = 'data/global_config.json'
    config_reader = ConfigReader()
    config_reader.implementation = JsonConfig()
    config = config_reader.Open(GLOBAL_CONFIG_PATH)

    client = Client()
    client.interface = TcpClient(
        address=config.network.address,
        port=config.network.port)
    client.adapter = JsonTcpAdapter()

    if args.command == 'add':
        action_id = client.Add(config.action)
        print(f'added with action_id: {action_id}')
    elif args.command == 'remove':
        client.Remove(int(args.id))
        print(f'removed action_id: {args.id}')
    elif args.command == 'status':
        status = client.GetStatus(int(args.id))
        print(f'status of action_id {args.id}: {status}')
    elif args.command == 'result':
        result = client.GetResult(int(args.id))
        print(f'result of action_id {args.id}: {result}')
    else:
        raise RuntimeError(f'unsupported command "{args.command}"')

    # ToDo: add high-level scenario group execution


def main():
    parser = argparse.ArgumentParser()
    # parser.add_argument('--config', help='path to global config file', required=True)
    
    subparsers = parser.add_subparsers(help='sub-command', required=True, dest='command')
    
    add_cmd_subparser = subparsers.add_parser('add', help='request new action to perform')
    add_config_group = add_cmd_subparser.add_mutually_exclusive_group(required=True)
    add_config_group.add_argument('--reuse_global_config', action='store_true',
                                   help='get action from global config')
    add_config_group.add_argument('--config', type=str,
                                   help='path to config file with action to perform')
    
    remove_cmd_subparser = subparsers.add_parser('remove', help='cancel selected action')
    remove_cmd_subparser.add_argument('id', help='unique index of the action')
    
    status_cmd_subparser = subparsers.add_parser('status', help='get status of selected action')
    status_cmd_subparser.add_argument('id', help='unique index of the action')
    
    result_cmd_subparser = subparsers.add_parser('result', help='get result of selected action')
    result_cmd_subparser.add_argument('id', help='unique index of the action')
    
    args = parser.parse_args()

    process(args)


if __name__ == '__main__':
    main()
