from models.GeoLocationMixin import GeoLocationMixin

class City(GeoLocationMixin):
    """
    Represents a city with its name and country.

    Attributes:
    - name (str): The name of the city.
    - country (str): The country where the city is located.
    """

    def __init__(self, name, country):
        """
        Initializes a new City object with the given name and country.

        Parameters:
        - name (str): The name of the city.
        - country (str): The country where the city is located.
        """
        self.name = name
        self.country = country
        
    def __str__(self):
        """
        Returns a string representation of the city.

        Returns:
        - str: A string representation of the city, including its name and country.
        """
        return f'City: {self.name}, Country: {self.country}'


class CityExtended(City, GeoLocationMixin):
    """
    Represents an extended version of a city with additional attributes.

    Attributes:
    - name (str): The name of the city.
    - country (str): The country where the city is located.
    """

    def __init__(self, name, country):
        """
        Initializes a new CityExtended object with the given name and country.

        Parameters:
        - name (str): The name of the city.
        - country (str): The country where the city is located.
        """
        super().__init__(name, country)

    @property
    def city_name(self):
        """
        Getter method for the city_name property.

        Returns:
        - str: The name of the city.
        """
        return self.name

    @city_name.setter
    def city_name(self, new_name):
        """
        Setter method for the city_name property.

        Parameters:
        - new_name (str): The new name of the city.
        """
        self.name = new_name

    @property #Getter
    def city_country(self):
        """
        Getter method for the city_country property.

        Returns:
        - str: The country where the city is located.
        """
        return self.country

    @city_country.setter #Setter
    def city_country(self, new_country):
        """
        Setter method for the city_country property.

        Parameters:
        - new_country (str): The new country where the city is located.
        """
        self.country = new_country
       

    def __str__(self):
        """
        Returns a string representation of the extended city.

        Returns:
        - str: A string representation of the extended city, including its name and country.
        """
        return f'City Extended: {self.name}, Country: {self.country}'

