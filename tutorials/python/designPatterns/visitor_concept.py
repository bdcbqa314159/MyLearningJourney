"the visitor pattern concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class IVisitor(metaclass=ABCMeta):
    "an interface that custom visitors should implement"
    @staticmethod
    @abstractmethod
    def visit(element):
        "visitors visit elements/objects within the application"


class IVisitable(metaclass=ABCMeta):
    """
    an interface the concrete objects should implement that allows
    the visitor to traverse a hierarchical structure of objects
    """

    @staticmethod
    @abstractmethod
    def accept(visitor):
        "the visitor traverses and accesses each object through this method"


class Element(IVisitable):
    "an object that can be part of any hierarchy"

    def __init__(self, name, value, parent=None):
        self.name = name
        self.value = value
        self.elements = set()

        if parent:
            parent.elements.add(self)

    def accept(self, visitor):
        "required by the visitor that will traverse"
        for element in self.elements:
            element.accept(visitor)
        visitor.visit(self)


class PrintELementVisitor(IVisitor):
    "interface for the visitor"
    @staticmethod
    def visit(element):
        print(element.name)


class CalculateElementTotalsVisitor(IVisitor):
    "create a visitor that totals the element values"
    total_value = 0

    @classmethod
    def visit(cls, element):
        cls.total_value += element.value

        return cls.total_value


if __name__ == "__main__":
    element_a = Element("A", 101)
    element_b = Element("B", 305, element_a)
    element_c = Element("C", 185, element_a)
    element_d = Element("D", -30, element_b)

    element_a.accept(PrintELementVisitor)
    total = CalculateElementTotalsVisitor()
    element_a.accept(CalculateElementTotalsVisitor)
    print(total.total_value)
