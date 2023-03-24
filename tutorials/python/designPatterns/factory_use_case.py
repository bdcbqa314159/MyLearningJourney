# The chair interface
from abc import ABCMeta, abstractmethod


class IChair(metaclass=ABCMeta):
    "The Chair interface (product)"

    @staticmethod
    @abstractmethod
    def get_dimensions():
        "A static interface method"


class SmallChair(IChair):
    "The small chair concrete implements IChair"

    def __init__(self):
        self._height = 41
        self._width = 40
        self._depth = 40

    def get_dimensions(self):
        return {
            "width": self._width,
            "depth": self._depth,
            "height": self._height
        }


class MediumChair(IChair):
    "The small chair concrete implements IChair"

    def __init__(self):
        self._height = 60
        self._width = 60
        self._depth = 60

    def get_dimensions(self):
        return {
            "width": self._width,
            "depth": self._depth,
            "height": self._height
        }


class BigChair(IChair):
    "The small chair concrete implements IChair"

    def __init__(self):
        self._height = 80
        self._width = 80
        self._depth = 80

    def get_dimensions(self):
        return {
            "width": self._width,
            "depth": self._depth,
            "height": self._height
        }


class ChairFactory:
    "The factory class"
    @staticmethod
    def get_chair(chair):
        "A static method to get a chair"
        if chair == 'BigChair':
            return BigChair()
        if chair == 'MediumChair':
            return MediumChair()
        if chair == 'SmallChair':
            return SmallChair()
        return None


if __name__ == "__main__":
    print("This is the client part")
    chair = ChairFactory.get_chair("SmallChair")
    print(chair.get_dimensions())
