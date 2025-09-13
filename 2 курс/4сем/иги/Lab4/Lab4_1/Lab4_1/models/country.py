from models.GeoLocationMixin import GeoLocationMixin

class Country:
    """
    Represents a country with its name and cities.

    Attributes:
    - name (str): The name of the country.
    - cities (list): A list of city objects belonging to the country.
    """
    #не предназначен для использования вне метода класса, однако доступен по этому имени
    _total_countries = 0

    @staticmethod #работает как обычные функции, но принадлежат области имён класса. Они не имеют доступа ни к самому классу, ни к его экземплярам.
    def get_total_countries():
        """
        Returns the total number of country objects created.

        Returns:
        - int: The total number of country objects created.
        """
        return Country._total_countries
    
    def __init__(self, name):
        """
        Initializes a new Country object with the given name.

        Parameters:
        - name (str): The name of the country.
        """
        self.name = name
        self.cities = []

    def add_city(self, city):
        """
        Adds a city to the list of cities belonging to the country.

        Parameters:
        - city (City): The city object to add to the country.
        """
        self.cities.append(city)

    def __str__(self):
        """
        Returns a string representation of the country.

        Returns:
        - str: A string representation of the country, including its name and the names of its cities.
        """
        return f'{self.name}: {", ".join(city.name for city in self.cities)}'


class CountryExtended(Country, GeoLocationMixin):
    """
    Represents an extended version of a country with additional attributes.

    Attributes:
    - name (str): The name of the country.
    - region (str): The region where the country is located.
    - population (int): The population of the country.
    """

    def __init__(self, name, region, population):
        """
        Initializes a new CountryExtended object with the given name, region, and population.

        Parameters:
        - name (str): The name of the country.
        - region (str): The region where the country is located.
        - population (int): The population of the country.
        """
        super().__init__(name) # для вызова конструктора базового класса Country(вызов оригинального метода родительского класса)
        self._region = region  # Приватное поле для хранения региона
        self._population = population  # Приватное поле для хранения населения
        
#декоратор @property используется для создания свойств, которые обеспечивают доступ к атрибутам объекта как к атрибутам класса.
    @property
    def region(self):
        """
        Getter method for the region property.

        Returns:
        - str: The region where the country is located.
        """
        return self._region
    
#для обеспечения доступа к приватным полям, сеттер-позволяет превращать атрибуты класса в свойства или управляемые объекты
    @region.setter
    def region(self, new_region):
        """
        Setter method for the region property.

        Parameters:
        - new_region (str): The new region where the country is located.
        """
        self._region = new_region

    @property
    def population(self):
        """
        Getter method for the population property.

        Returns:
        - int: The population of the country.
        """
        return self._population

    @population.setter
    def population(self, new_population):
        """
        Setter method for the population property.

        Parameters:
        - new_population (int): The new population of the country.
        """
        self._population = new_population

    @property
    def total_countries(self):
        """
        Getter method for the total_countries property.

        Returns:
        - int: The total number of country objects created.
        """
        return self.get_total_countries()
    
    @property #динамический атрибут
    def total_cities(self):
        """
        Computes the total number of cities in the country.

        Returns:
        - int: The total number of cities in the country.
        """
        return len(self.cities)
    
    def __str__(self):
        """
        Returns a string representation of the extended country.

        Returns:
        - str: A string representation of the extended country, including its name, region, and population.
        """
        return f'Country Extended: {self.name}, Region: {self.region}, Population: {self.population}, Total Cities: {self.total_cities}'
