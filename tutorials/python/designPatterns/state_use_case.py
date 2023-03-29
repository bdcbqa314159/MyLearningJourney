"the state pattern use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103
# pylint: disable=C2801

from abc import ABCMeta, abstractmethod


class Context():
    "this is the object whose behavior will change"

    def __init__(self):
        self.state_handles = [Started(), Running(), Finished()]

        self._handle = iter(self.state_handles)

    def request(self):
        "each time the request is called, a new class will handle it"

        try:
            self._handle.__next__()()
        except StopIteration:
            self._handle = iter(self.state_handles)


class IState(metaclass=ABCMeta):
    "a state interface"

    @staticmethod
    @abstractmethod
    def __call__():
        "set the default method"


class Started(IState):
    "a concrete state subclass"

    @staticmethod
    def method():
        "a task of this class"
        print("task started")

    __call__ = method


class Running(IState):
    "a concrete state subclass"

    @staticmethod
    def method():
        "a task of this class"
        print("task running")

    __call__ = method


class Finished(IState):
    "a concrete state subclass"

    @staticmethod
    def method():
        "a task of this class"
        print("task finished")

    __call__ = method


if __name__ == "__main__":
    context = Context()
    context.request()
    context.request()
    context.request()
    context.request()
    context.request()
    context.request()
