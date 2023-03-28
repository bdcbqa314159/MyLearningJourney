"mediator use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class IComponent(metaclass=ABCMeta):
    "an interface that each component will implement"

    @staticmethod
    @abstractmethod
    def notify(message):
        "the required notify method"

    @staticmethod
    @abstractmethod
    def receive(message):
        "the required receive method"


class Component(IComponent):
    "each component stays synchronized trough a mediator"

    def __init__(self, mediator, name):
        self._mediator = mediator
        self._name = name

    def notify(self, message):
        print(self._name + ": >>> out >>> : "+message)
        self._mediator.notify(message, self)

    def receive(self, message):
        print(self._name + ": <<< in <<< : "+message)


class Mediator():
    "a subject whose notify method is mediated"

    def __init__(self):
        self._components = set()

    def add(self, component):
        "add components"
        self._components.add(component)

    def notify(self, message, originator):
        "add components except for the originator component"
        for component in self._components:
            if component != originator:
                component.receive(message)


if __name__ == "__main__":
    mediator_ = Mediator()
    component1 = Component(mediator_, "component1")
    component2 = Component(mediator_, "component2")
    component3 = Component(mediator_, "component3")

    mediator_.add(component1)
    mediator_.add(component2)
    mediator_.add(component3)

    component1.notify("data A")
    component2.notify("data B")
    component3.notify("data C")
