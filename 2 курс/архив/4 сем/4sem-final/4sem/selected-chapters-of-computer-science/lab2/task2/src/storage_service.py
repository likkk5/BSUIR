import os
import pickle
import re


class StorageService:
    _storage: set[str] = set()
    _username: str
    _container_filename: str

    def __init__(self, username: str):
        self._username = username
        self._container_filename = f'{username}-container.dmp'

    def add(self, key: str):
        self._storage.add(key)

    def remove(self, key: str):
        self._storage.remove(key)

    def list(self):
        return list(self._storage)

    def find(self, key):
        return key in self._storage

    def grep(self, regex):
        return list(filter(lambda key: re.match(regex, key), self._storage))

    def is_exists(self):
        return os.path.exists(self._container_filename)

    def save(self):
        with open(self._container_filename, 'wb') as file:
            pickle.dump(self._storage, file)

    def load(self):
        with open(self._container_filename, 'rb') as file:
            loaded_set = pickle.load(file)
            self._storage = self._storage | loaded_set
