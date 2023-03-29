"the state pattern concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

import random
from abc import ABCMeta, abstractmethod


class Context():
    "this is the object whose behavior will change"

    def __init__(self):
        self.state_handles = [
            ConcreteStateA(), ConcreteStateB(), ConcreteStateC()]
        self.handle = None

    def request(self):
        """
        a method of the state that dynamically changes which class
        it uses depending on the value of self.handle
        """

        self.handle = self.state_handles[random.randint(0, 2)]
        return self.handle


class IState(metaclass=ABCMeta):
    "a state interface"

    @staticmethod
    @abstractmethod
    def __str__():
        "set the default method"


class ConcreteStateA(IState):
    "a concrete state subclass"

    def __str__(self):
        return "I am ConcreteStateA"


class ConcreteStateB(IState):
    "a concrete state subclass"

    def __str__(self):
        return "I am ConcreteStateB"


class ConcreteStateC(IState):
    "a concrete state subclass"

    def __str__(self):
        return "I am ConcreteStateC"


if __name__ == "__main__":
    context = Context()
    print(context.request())
    print(context.request())
    print(context.request())
    print(context.request())
    print(context.request())
    print(context.request())
