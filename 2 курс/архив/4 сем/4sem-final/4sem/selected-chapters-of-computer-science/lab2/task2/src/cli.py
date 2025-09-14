class CLI:
    _commands: dict[str, callable]

    def __init__(self):
        self._commands = {}

    def add_command(self, command: str, function: callable):
        self._commands[command] = function

    def parse_command(self):
        command_and_args = input('Enter command: ').split(maxsplit=1)

        if not command_and_args:
            print('Empty command')
            return

        command = command_and_args[0]
        args = command_and_args[1] if len(command_and_args) > 1 else ''

        function_to_call = self._commands.get(command)

        if function_to_call is None:
            print('Unknown command')
            return

        function_to_call(args)
