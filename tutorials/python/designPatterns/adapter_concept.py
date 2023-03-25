from abc import ABCMeta, abstractmethod


class IA(metaclass=ABCMeta):
    "an interface for an object"
    @staticmethod
    @abstractmethod
    def method_a():
        "an abstract method a"


class ClassA(IA):
    "a simple class that implements IA"

    def method_a(self):
        print("method A")


class IB(metaclass=ABCMeta):
    "an interface for an object"
    @staticmethod
    @abstractmethod
    def method_b():
        "an abstract method b"


class ClassB(IB):
    "a simple class that implements IB"

    def method_b(self):
        print("method B")


class ClassBAdapter(IA):
    "ClassB does not have a method_a we need to fit it"

    def __init__(self):
        self.class_b = ClassB()

    def method_a(self):
        "calls the class b method_b instead"
        self.class_b.method_b()


if __name__ == "__main__":
    items = [ClassA(), ClassB()]

# Very bad design below
    for item in items:
        if isinstance(item, ClassB):
            item.method_b()
        else:
            item.method_a()

# Usage of the adapter design pattern
    items_bis = [ClassA(), ClassBAdapter()]
    for item in items_bis:
        item.method_a()
