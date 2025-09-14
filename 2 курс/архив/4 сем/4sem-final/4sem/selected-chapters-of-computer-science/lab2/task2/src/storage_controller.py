import re

from storage_service import StorageService


class StorageController:
    _storage_service: StorageService = None

    def __init__(self):
        self.switch()

    @staticmethod
    def _split_keys_and_apply_function(keys: str, function: callable):
        for key in keys.split():
            function(key)

    def add(self, args: str):
        if not args:
            print('Keys to add not provided')
            return

        self._split_keys_and_apply_function(args, self._storage_service.add)
        print('Successfully added keys to storage')

    def _remove_key(self, key: str):
        if self._storage_service.find(key):
            self._storage_service.remove(key)
        else:
            print(f'Cant remove key {key}. It does not exists')

    def remove(self, args: str):
        if not args:
            print('Keys to remove not provided')
            return

        self._split_keys_and_apply_function(args, self._remove_key)

    def list(self, args):
        data = self._storage_service.list()

        if not data:
            print('Empty')
            return

        print(' '.join(data))

    def find(self, args: str):
        if not args:
            print('Keys to find not provided')
            return

        self._split_keys_and_apply_function(
            args,
            lambda key: print(f'Key {key} {"" if self._storage_service.find(key) else "not "}exists')
        )

    def grep(self, args: str):
        if not args:
            print('Empty regexp')
            return

        try:
            regexp = re.compile(args)
        except re.error:
            print('Incorrect regexp')
            return

        keys_found = self._storage_service.grep(regexp)

        if not keys_found:
            print('No such elements')
            return

        print(' '.join(keys_found))

    def save(self, args):
        self._storage_service.save()
        print('Saved successfully')

    def load(self, args):
        self._storage_service.load()
        print('Loaded successfully')

    def exit(self, args):
        self._ask_for_save()
        exit(0)

    def switch(self, args=None):
        if self._storage_service:
            self._ask_for_save()

        username = input('Enter new username: ')
        self._storage_service = StorageService(username)

        self._ask_for_load()

    def _ask_for_load(self):
        if self._storage_service.is_exists():
            answer = input('Container was found. Would you like to load it? (y/n): ')

            if answer.lower() in ['y', 'yes']:
                self._storage_service.load()

    def _ask_for_save(self):
        answer = input('Do you want to save container? (y/n): ')

        if answer.lower() in ['y', 'yes']:
            self._storage_service.save()
