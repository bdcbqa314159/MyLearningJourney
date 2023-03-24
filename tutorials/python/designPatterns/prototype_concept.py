from abc import ABCMeta, abstractmethod


class IPrototype(metaclass=ABCMeta):
    "interface with clone method"
    @staticmethod
    @abstractmethod
    def clone():
        "the clone, deep or shallow, it is up to the situation"


class MyClass_shallow1(IPrototype):
    "A concrete class"

    def __init__(self, field):
        self.field = field

    def clone(self):
        "this clone method uses shallow copy directly"
        return type(self)(self.field)

    def __str__(self):
        return f"{id(self)} \tfield={self.field}\ttype={type(self.field)}"


class MyClass_shallow2(IPrototype):
    "A concrete class"

    def __init__(self, field):
        self.field = field

    def clone(self):
        "this clone method uses python version of shallow copy directly"
        return type(self)(self.field.copy())

    def __str__(self):
        return f"{id(self)} \tfield={self.field}\ttype={type(self.field)}"


if __name__ == "__main__":
    obj1 = MyClass_shallow1([1, 2, 3, 4])
    print(f"obj1 {obj1}")

    obj2 = obj1.clone()
    obj2.field[1] = 101

    print(f"obj2 {obj2}")
    print(f"obj1 {obj1}")

    obj3 = MyClass_shallow2([1, [3, 4, 102], 3, 4])
    print(f"obj3 {obj3}")

    obj4 = obj3.clone()
    obj4.field[1][0] = 999

    print(f"obj4 {obj4}")
    print(f"obj3 {obj3}")
