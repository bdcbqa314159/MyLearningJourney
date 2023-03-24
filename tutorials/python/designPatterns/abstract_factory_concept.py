from abc import ABCMeta, abstractmethod


class IProduct(metaclass=ABCMeta):
    "Abstract class interface (product)"
    @staticmethod
    @abstractmethod
    def create_object():
        "An abstract interface method"


class concreteProductA(IProduct):
    "Implementation of IProduct"

    def __init__(self):
        self.name = "concreteProductA"

    def create_object(self):
        return self


class concreteProductB(IProduct):
    "Implementation of IProduct"

    def __init__(self):
        self.name = "concreteProductB"

    def create_object(self):
        return self


class concreteProductC(IProduct):
    "Implementation of IProduct"

    def __init__(self):
        self.name = "concreteProductC"

    def create_object(self):
        return self


class FactoryA:
    "The FactoryA class"
    @staticmethod
    def create_object(some_property):
        "Static method to get a  concrete product"

        try:
            if some_property == 'a':
                return concreteProductA
            if some_property == 'b':
                return concreteProductB()
            if some_property == 'c':
                return concreteProductC()

            raise Exception('class not found')

        except Exception as _e:
            print(_e)

        return None


class IIProduct(metaclass=ABCMeta):
    "Another abstract class"
    @staticmethod
    @abstractmethod
    def create_object():
        "Abstract interface method"


class concreteProductD(IIProduct):
    "Implementation of IIProduct"

    def __init__(self):
        self.name = "concreteProductB"

    def create_object(self):
        return self


class concreteProductE(IIProduct):
    "Implementation of IIProduct"

    def __init__(self):
        self.name = "concreteProductB"

    def create_object(self):
        return self


class concreteProductF(IIProduct):
    "Implementation of IIProduct"

    def __init__(self):
        self.name = "concreteProductB"

    def create_object(self):
        return self


class FactoryB:
    "The FactoryB class"
    @staticmethod
    def create_object(some_property):
        "static method to create objects"
        try:
            if some_property == 'd':
                return concreteProductD()
            if some_property == 'e':
                return concreteProductE()
            if some_property == 'f':
                return concreteProductF()
            raise Exception('class not found')

        except Exception as _e:
            print(_e)
        return None


class IAbstractFactory(metaclass=ABCMeta):
    "Abstract Factory Interface"
    @staticmethod
    @abstractmethod
    def create_object(factory):
        "The static Abstract factory interface method"


class AbstractFactory(IAbstractFactory):
    "The Abstract Factory Concrete Class"
    @staticmethod
    def create_object(factory):
        "Static get_factory method"
        try:
            if factory in ['aa', 'ab', 'ac']:
                return FactoryA.create_object(factory[1])
            if factory in ['bd', 'be', 'bf']:
                return FactoryB.create_object(factory[1])
            raise Exception('No factory found')
        except Exception as _e:
            print(_e)
        return None


if __name__ == "__main__":
    product = AbstractFactory.create_object('ab')
    print(f"{product.__class__}")
    product = AbstractFactory.create_object('be')
    print(f"{product.__class__}")
