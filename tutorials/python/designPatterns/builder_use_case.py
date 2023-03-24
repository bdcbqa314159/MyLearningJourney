from abc import ABCMeta, abstractmethod


class House():
    "The product"

    def __init__(self, building_type="Apartment", doors=0, windows=0, wall_material="brick"):
        self.wall_material = wall_material
        self.building_type = building_type
        self.doors = doors
        self.windows = windows

    def construction(self):
        "return a string describing the construction"
        return f"This is a {self.wall_material} "\
            f"{self.building_type} with {self.doors} "\
            f"door(s) and {self.windows} window(s)."


class IHouseBuilder(metaclass=ABCMeta):
    "the house builder interface"
    @staticmethod
    @abstractmethod
    def set_building_type(building_type):
        "build type"

    @staticmethod
    @abstractmethod
    def set_wall_material(wall_material):
        "build material"

    @staticmethod
    @abstractmethod
    def set_number_doors(number):
        "number of doors"

    @staticmethod
    @abstractmethod
    def set_number_windows(number):
        "number of windows"

    @staticmethod
    @abstractmethod
    def get_result():
        "return the final product"


class HouseBuilder(IHouseBuilder):
    "The house builder"

    def __init__(self):
        self.house = House()

    def set_building_type(self, building_type):
        self.house.building_type = building_type
        return self

    def set_wall_material(self, wall_material):
        self.house.wall_material = wall_material
        return self

    def set_number_doors(self, number):
        self.house.doors = number
        return self

    def set_number_windows(self, number):
        self.house.windows = number
        return self

    def get_result(self):
        return self.house


class CastleDirector:
    "One of the directors, that can build a complex representation"
    @staticmethod
    def construct():
        "Constructs and returns the final product"
        return HouseBuilder().set_building_type("Castle")\
            .set_wall_material("Sandstone")\
            .set_number_doors(200)\
            .set_number_windows(200)\
            .get_result()


class IglooDirector:
    "One of the directors, that can build a complex representation"
    def construct():
        "Constructs and returns the final product"
        return HouseBuilder().set_building_type("Igloo")\
            .set_wall_material("Ice")\
            .set_number_doors(1)\
            .set_number_windows(0)\
            .get_result()


class HouseBoatDirector:
    "One of the directors, that can build a complex representation"
    def construct():
        "Constructs and returns the final product"
        return HouseBuilder().set_building_type("HouseBoat")\
            .set_wall_material("Wood")\
            .set_number_doors(6)\
            .set_number_windows(8)\
            .get_result()


if __name__ == "__main__":
    igloo = IglooDirector.construct()
    houseboat = HouseBoatDirector.construct()
    castle = CastleDirector.construct()

    print(igloo.construction())
    print(houseboat.construction())
    print(castle.construction())
