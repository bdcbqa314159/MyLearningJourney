from abc import ABCMeta, abstractmethod


class IChair(metaclass=ABCMeta):
    "chair abstract interface"
    @staticmethod
    @abstractmethod
    def get_dimensions():
        "A static interface method"


class ITable(metaclass=ABCMeta):
    "table abstract interface"
    @staticmethod
    @abstractmethod
    def get_dimensions():
        "A static interface method"


class smallChair(IChair):
    "small Table concrete class"

    def __init__(self):
        self._height = 30
        self._width = 30
        self._depth = 30

    def get_dimensions(self):
        return {
            "width": self._width,
            "height": self._width,
            "depth": self._depth
        }


class mediumChair(IChair):
    "Medium Chair concrete class"

    def __init__(self):
        self._height = 50
        self._width = 50
        self._depth = 50

    def get_dimensions(self):
        return {
            "width": self._width,
            "height": self._width,
            "depth": self._depth
        }


class bigChair(IChair):
    "Big Chair concrete class"

    def __init__(self):
        self._height = 80
        self._width = 80
        self._depth = 80

    def get_dimensions(self):
        return {
            "width": self._width,
            "height": self._width,
            "depth": self._depth
        }


class smallTable(ITable):
    "Small Table concrete class"

    def __init__(self):
        self._height = 30
        self._width = 50
        self._depth = 60

    def get_dimensions(self):
        return {
            "width": self._width,
            "height": self._width,
            "depth": self._depth
        }


class mediumTable(ITable):
    "Medium Table concrete class"

    def __init__(self):
        self._height = 50
        self._width = 70
        self._depth = 80

    def get_dimensions(self):
        return {
            "width": self._width,
            "height": self._width,
            "depth": self._depth
        }


class bigTable(ITable):
    "Big Table concrete class"

    def __init__(self):
        self._height = 80
        self._width = 90
        self._depth = 100

    def get_dimensions(self):
        return {
            "width": self._width,
            "height": self._width,
            "depth": self._depth
        }


class ChairFactory:
    "The chair factory class"
    @staticmethod
    def create_object(chair):
        try:
            if chair == 'small chair':
                return smallChair()
            if chair == 'medium chair':
                return mediumChair()
            if chair == 'big chair':
                return bigChair()
            raise Exception('chair not found')
        except Exception as _e:
            print(_e)
        return None


class TableFactory:
    "The table factory class"
    @staticmethod
    def create_object(table):
        try:
            if table == 'small table':
                return smallTable()
            if table == 'medium table':
                return mediumTable()
            if table == 'big table':
                return bigTable()
            raise Exception('table not found')
        except Exception as _e:
            print(_e)
        return None


class IFurnitureFactory(metaclass=ABCMeta):
    "Abstrat Furniture Factory Interface"
    @staticmethod
    @abstractmethod
    def get_furniture(furniture):
        "The static Abstract factory interface"


class FurnitureFactory(IFurnitureFactory):
    "Abstract Factory concrete class"
    @staticmethod
    def get_furniture(furniture):
        "Static get_furntiture methode"

        try:
            if furniture in ['small chair', 'medium chair', 'big chair']:
                return ChairFactory.create_object(furniture)

            if furniture in ['small table', 'medium table', 'big table']:
                return TableFactory.create_object(furniture)
            raise Exception('furniture not found')

        except Exception as _e:
            print(_e)

        return None


if __name__ == "__main__":
    furniture = FurnitureFactory.get_furniture('small table')
    print(f"{furniture.__class__}: {furniture.get_dimensions()}")
    furniture = FurnitureFactory.get_furniture('big chair')
    print(f"{furniture.__class__}: {furniture.get_dimensions()}")
