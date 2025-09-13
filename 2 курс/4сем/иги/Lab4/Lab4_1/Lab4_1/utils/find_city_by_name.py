def find_city_by_name(countries, city_name):
    """
    Finds a city by its name in the list of countries.

    Parameters:
    - countries (list): List of country objects.
    - city_name (str): The name of the city to find.

    Returns:
    - City or None: The city object if found, or None if the city is not found.
    """
    # for country in countries:
    #     for city in country.cities:
    #         if city.name.lower() == city_name.lower():
    #             return city
    # return None
    for country in countries.values():
        for city in country.cities:
            if city.name.lower() == city_name.lower():
                return city
    return None
