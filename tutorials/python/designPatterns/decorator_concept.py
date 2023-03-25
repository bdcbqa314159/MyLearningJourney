from abc import ABCMeta, abstractmethod


class IComponent(metaclass=ABCMeta):
    "methods the component must implement"
    @staticmethod
    @abstractmethod
    def method():
        "A method to implement"


class Component(IComponent):
    "a component that can be decorated or not"

    def method(self):
        "an exmaple method"
        return "Component Method"


class Decorator(IComponent):
    "the decorator also implements the IComponent"

    def __init__(self, obj):
        "set reference to the decorated object"
        self.object = obj

    def method(self):
        "A method to implement"
        return f"Decorator Method({self.object.method()})"


if __name__ == "__main__":
    component = Component()
    print(component.method())
    print(Decorator(component).method())
    print(Decorator(Decorator(component)).method())
