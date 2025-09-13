class GeoLocationMixin: #Примесь представляет собой класс, содержащий методы и/или атрибуты, которые могут быть добавлены к другим классам для добавления им новой функциональности, без строгого наследования
    """
    A mixin class providing methods for obtaining location information.

    Methods:
    - get_location_info(): Returns information about the location of the object.
    """

    def get_location_info(self):
        """
        Returns information about the location of the object.

        Returns:
        - str: Information about the location of the object.
        """
        return f"City {self.name} is in {self.country}"