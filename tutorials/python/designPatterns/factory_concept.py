from abc import ABCMeta, abstractmethod


class IProduct(metaclass=ABCMeta):
    "Class Interface (Product)"

    @staticmethod
    @abstractmethod
    def create_object():
        "An abstract interface method"


class ConcreteProductA(IProduct):
    "Concrete class that implements the IProduct"

    def __init__(self):
        self.name = "ConcreteProductA"

    def create_object(self):
        return self


class ConcreteProductB(IProduct):
    "Concrete class that implements the IProduct"

    def __init__(self):
        self.name = "ConcreteProductB"

    def create_object(self):
        return self


class ConcreteProductC(IProduct):
    "Concrete class that implements the IProduct"

    def __init__(self):
        self.name = "ConcreteProductC"

    def create_object(self):
        return self


class Creator:
    "Factory class"
    @staticmethod
    def create_object(some_property):
        "A static method to get a concrete product"
        if some_property == 'a':
            return ConcreteProductA()
        if some_property == 'b':
            return ConcreteProductB()
        if some_property == 'c':
            return ConcreteProductC()
        return None


if __name__ == "__main__":
    the_product = Creator.create_object('a')
    print(the_product.name)
