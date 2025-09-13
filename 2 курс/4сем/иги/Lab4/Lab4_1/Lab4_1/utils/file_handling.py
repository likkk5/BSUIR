from models.country import CountryExtended
from models.city import CityExtended
import pickle
import csv

def save_countries_to_pickle(filename, countries):
    """
    Saves the list of countries to a file in pickle format.

    Parameters:
    - filename (str): The name of the file to save the data to.
    - countries (list): The list of country objects to save.
    """
    with open(filename, 'wb') as file:
        pickle.dump(countries, file) #сериализация объекта obj с записью в файл file

def load_countries_from_pickle(filename):
    """
    Loads the list of countries from a file in pickle format.

    Parameters:
    - filename (str): The name of the file from which to load the data.

    Returns:
    - list: The list of loaded country objects.
    """
    with open(filename, 'rb') as file:
        return pickle.load(file) #десериализация содержимого file и возврат объекта

def save_countries_to_csv(filename, countries):
    """
    Saves the list of countries to a file in CSV format.

    Parameters:
    - filename (str): The name of the file to save the data to.
    - countries (list): The list of country objects to save.
    """
    # with open(filename, 'w', newline='') as file:
    #     writer = csv.writer(file)
    #     for country in countries:
    #         for city in country.cities:
    #             writer.writerow([country.name, city.name, country.region, country.population])
    with open(filename, 'w', newline='') as file:
        writer = csv.writer(file)
        for country_name, country in countries.items():
            for city in country.cities:
                writer.writerow([country_name, city.name, country.region, country.population])

def load_countries_from_csv(filename):
    """
    Loads the list of countries from a file in CSV format.

    Parameters:
    - filename (str): The name of the file from which to load the data.

    Returns:
    - list: The list of loaded country objects.
    """
    countries = {}
    with open(filename, 'r', newline='') as file:
        reader = csv.reader(file)
        for row in reader:
            country_name, city_name, region, population = row
            if country_name not in countries:
                countries[country_name] = CountryExtended(country_name, region, int(population))
            countries[country_name].add_city(CityExtended(city_name, country_name))
    return list(countries.values())
