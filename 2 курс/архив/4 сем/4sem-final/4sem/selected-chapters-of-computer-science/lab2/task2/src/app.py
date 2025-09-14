from cli import CLI
from storage_controller import StorageController


class App:
    _possible_commands = '''
            - add <key> [key, …] – add one or more elements to the container 
            - remove <key> – delete key from container; 
            - find  key> [key, …] – check if the element is presented in the container; 
            - list – print all elements of container; 
            - grep <regex> – check the value in the container by regular expression 
            - save – save container to file
            - load - load container from file
            - switch – switches to another user.
            - help - display commands
    '''

    def print_possible_commands(self, _):
        print('Possible commands: ', self._possible_commands)

    def start_application(self):
        print(f'''
        Welcome to an interactive CLI program which is going to play the role 
        of a storage for unique elements and support a list of the following commands: {self._possible_commands}''')

        controller = StorageController()
        cli = CLI()

        possible_commands = ['add', 'list', 'remove', 'find', 'grep', 'exit', 'switch', 'save', 'load']
        for command in possible_commands:
            cli.add_command(command, getattr(controller, command))

        cli.add_command('help', self.print_possible_commands)

        while True:
            cli.parse_command()
