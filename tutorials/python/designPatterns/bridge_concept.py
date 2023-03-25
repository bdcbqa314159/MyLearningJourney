from abc import ABCMeta, abstractmethod


class IAbstraction(metaclass=ABCMeta):
    "the abstraction interface"
    @staticmethod
    @abstractmethod
    def method(*args):
        "the method handle"


class RefinedAbstractionA(IAbstraction):
    "A refined abstraction"

    def __init__(self, implementer):
        self.implementer = implementer()

    def method(self, *args):
        self.implementer.method(*args)


class IImplementer(metaclass=ABCMeta):
    "the implementer interface"
    @staticmethod
    @abstractmethod
    def method(*args: tuple) -> None:
        "the method implmentation"


class ConcreterImplementerA(IImplementer):
    "a concrete implementer"
    @staticmethod
    def method(*args: tuple) -> None:
        print(args)


class ConcreteImplementerB(IImplementer):
    "a concrete Implementer"
    @staticmethod
    def method(*args: tuple) -> None:
        for arg in args:
            print(arg)


if __name__ == "__main__":
    refined_abstraction_A = RefinedAbstractionA(ConcreterImplementerA)
    refined_abstraction_B = RefinedAbstractionA(ConcreteImplementerB)

    refined_abstraction_A.method('a', 'b', 'c')
    refined_abstraction_B.method('a', 'b', 'c')
