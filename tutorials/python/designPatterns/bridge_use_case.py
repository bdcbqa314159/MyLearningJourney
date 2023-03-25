from abc import ABCMeta, abstractmethod


class IShape(metaclass=ABCMeta):
    "the shape abstraction interface"
    @staticmethod
    @abstractmethod
    def draw():
        "the method that will be handled at the shapes implementer"


class IShapeImplementer(metaclass=ABCMeta):
    "shape implementer"
    @staticmethod
    @abstractmethod
    def draw_implementation():
        "the method that the refined abstraction will implement"


class SquareImplementer(IShapeImplementer):
    "a square implementer"

    def draw_implementation(self):
        print("**************")
        print("*            *")
        print("*            *")
        print("*            *")
        print("*            *")
        print("*            *")
        print("*            *")
        print("**************")


class CircleImplementer(IShapeImplementer):
    "a circle implementer"

    def draw_implementation(self):
        print("    ******")
        print("  **      **")
        print(" *          *")
        print("*            *")
        print("*            *")
        print(" *          *")
        print("  **      **")
        print("    ******")


class Square(IShape):
    "the square is a refined abstraction"

    def __init__(self, implementer):
        self.implementer = implementer()

    def draw(self):
        self.implementer.draw_implementation()


class Circle(IShape):
    "the cercle is a refined abstraction"

    def __init__(self, implementer):
        self.implementer = implementer()

    def draw(self):
        self.implementer.draw_implementation()


if __name__ == "__main__":
    circle = Circle(CircleImplementer)
    circle.draw()

    square = Square(SquareImplementer)
    square.draw()
