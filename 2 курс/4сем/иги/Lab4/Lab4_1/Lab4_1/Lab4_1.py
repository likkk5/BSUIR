from models.country import CountryExtended
from models.city import CityExtended
from utils.file_handling import save_countries_to_pickle, load_countries_from_pickle, save_countries_to_csv, load_countries_from_csv
from utils.find_city_by_name import find_city_by_name

def main():
    countries = {}
    while True:  
        # Создание объектов стран и городов
        france = CountryExtended("France", "Europe", 67000000)
        france.add_city(CityExtended("Paris", "France"))
        france.add_city(CityExtended("Marseille", "France"))

        spain = CountryExtended("Spain", "Europe", 47000000)
        spain.add_city(CityExtended("Madrid", "Spain"))
        spain.add_city(CityExtended("Barcelona", "Spain"))

        #countries = [france, spain]
        countries[france.name] = france
        countries[spain.name] = spain
    
        # Сохранение данных в файлы
        save_countries_to_pickle("countries.pickle", countries)
        save_countries_to_csv("countries.csv", countries)

        # Загрузка данных из файлов
        countries_from_pickle = load_countries_from_pickle("countries.pickle")
        countries_from_csv = load_countries_from_csv("countries.csv")

        # Поиск города по названию
        city_name = input("Enter the name of the city: ")
        while not city_name.strip() or not city_name.isalpha():
            print("Please enter a valid city name containing only letters.")
            city_name = input("Enter the name of the city: ")
            
        found_city = find_city_by_name(countries_from_pickle, city_name)
        if found_city:
            # print(f"The city {found_city.name} is in {found_city.country}")
            print(found_city.get_location_info())  # Получаем информацию о местоположении города
            # Найдем соответствующую страну
            for country in countries_from_pickle.values():
               if country.name == found_city.country:
                  print(country)
                  #print(f"Country: {country.name}, Region: {country.region}, Population: {country.population}")
                  break
            else:
                print("Country not found?")
        else:
            print("City not found.")
        
        repeat = input("Do you want to run the program again? (y/n): ")
        if repeat.lower() != 'y':
            break

if __name__ == "__main__":
    main()
