from abc import ABCMeta, abstractmethod


class IValue(metaclass=ABCMeta):
    "methods the component must implement"
    @staticmethod
    @abstractmethod
    def __str__():
        "override the object to return the value attribute by default"


class Value(IValue):
    "A component that can be decoreated or not"

    def __init__(self, value):
        self.value = value

    def __str__(self):
        return str(self.value)


class Add(IValue):
    "A decorator that adds a number to a number"

    def __init__(self, val1, val2):
        val1 = getattr(val1, 'value', val1)
        val2 = getattr(val2, 'value', val2)
        self.value = val1+val2

    def __str__(self):
        return str(self.value)


class Substract(IValue):
    "A decorator that adds a number to a number"

    def __init__(self, val1, val2):
        val1 = getattr(val1, 'value', val1)
        val2 = getattr(val2, 'value', val2)
        self.value = val1-val2

    def __str__(self):
        return str(self.value)


if __name__ == "__main__":
    A = Value(1)
    B = Value(2)
    C = Value(5)

    print(Add(A, B))
    print(Add(A, 100))
    print(Substract(C, A))
    print(Substract(Add(C, B), A))
    print(Substract(100, 101))
    print(Add(Substract(Add(C, B), A), 100))
    print(Substract(123, Add(C, C)))
    print(Add(Substract(Add(C, 10), A), 100))
    print(A)
    print(B)
    print(C)
