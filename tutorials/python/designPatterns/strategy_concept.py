"the strategy pattern concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class Context():
    "this is the object whose behavior will change"

    @staticmethod
    def request(strategy):
        "the request is handled by the class passed in"
        return strategy()


class IStrategy(metaclass=ABCMeta):
    "a strategy interface"

    @staticmethod
    @abstractmethod
    def __str__():
        "implement the __str__ dunder"


class ConcreteStrategyA(IStrategy):
    "a concrete strategy subclass"

    def __str__(self):
        return "I am concrete strategy A"


class ConcreteStrategyB(IStrategy):
    "a concrete strategy subclass"

    def __str__(self):
        return "I am concrete strategy B"


class ConcreteStrategyC(IStrategy):
    "a concrete strategy subclass"

    def __str__(self):
        return "I am concrete strategy C"


if __name__ == "__main__":
    context = Context()
    print(context.request(ConcreteStrategyA))
    print(context.request(ConcreteStrategyB))
    print(context.request(ConcreteStrategyC))
