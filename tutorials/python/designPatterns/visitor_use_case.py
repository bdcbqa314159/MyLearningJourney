"the visitor pattern use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class IVisitor(metaclass=ABCMeta):
    "an interface that custom visitors should implement"

    @staticmethod
    @abstractmethod
    def visit(element):
        "visitors visit element/objects within the application"


class IVisitable(metaclass=ABCMeta):
    """
    an interface that concrete objects should implement that allows the visitor to
    traverese a hierarchical structure of objects
    """

    @staticmethod
    @abstractmethod
    def accept(visitor):
        "the visitor traverses and accesses each oject through this method"


class AbstractCarPart():
    "the abstract car part"
    @property
    def name(self):
        "a name for the part"
        return self._name

    @name.setter
    def name(self, value):
        self._name = value

    @property
    def sku(self):
        "the stock keeping unit (sku)"
        return self._sku

    @sku.setter
    def sku(self, value):
        self._sku = value

    @property
    def price(self):
        "the price per unit"
        return self._price

    @price.setter
    def price(self, value):
        self._price = value


class Body(AbstractCarPart, IVisitable):
    "a part of the car"

    def __init__(self, name, sku, price):
        self._name = name
        self.sku = sku
        self.price = price

    def accept(self, visitor):
        visitor.visit(self)


class Engine(AbstractCarPart, IVisitable):
    "a part of the car"

    def __init__(self, name, sku, price):
        self.name = name
        self.sku = sku
        self.price = price

    def accept(self, visitor):
        visitor.visit(self)


class Wheel(AbstractCarPart, IVisitable):
    "a part of the car"

    def __init__(self, name, sku, price):
        self.name = name
        self.sku = sku
        self.price = price

    def accept(self, visitor):
        visitor.visit(self)


class Car(AbstractCarPart, IVisitable):
    "a car with parts"

    def __init__(self, name):
        self.name = name
        self._parts = [
            Body("Utility", "ABC-123-21", 1001),
            Engine("V8 engine", "DEF-456-21", 2555),
            Wheel("FrontLeft", "GHI-789FL-21", 136),
            Wheel("FrontRight", "GHI-789FR-21", 136),
            Wheel("BackLeft", "GHI-789BL-21", 152),
            Wheel("BackRight", "GHI-789BR-21", 152),
        ]

    def accept(self, visitor):
        for parts in self._parts:
            parts.accept(visitor)
        visitor.visit(self)


class PrintPartsVisitor(IVisitor):
    "print out the part name and sku"

    @staticmethod
    def visit(element):
        if hasattr(element, 'sku'):
            print(f"{element.name}\t:{element.sku}".expandtabs(6))


class TotalPriceVisitor(IVisitor):
    "print out the total cost of the parts in the car"
    total_price = 0

    @classmethod
    def visit(cls, element):
        if hasattr(element, 'price'):
            cls.total_price += element.price
        return cls.total_price


if __name__ == "__main__":
    car = Car("DeLorean")
    car.accept(PrintPartsVisitor())
    total_price_visitor = TotalPriceVisitor()
    car.accept(total_price_visitor)
    print(f"total price = {total_price_visitor.total_price}")
