"the template method pattern concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class AbstractClass(metaclass=ABCMeta):
    "a template class containing a template method and primitive methods"

    @staticmethod
    def step_one():
        """
        hooks are normally empty in the abstract class - the implementing class
        can optionally override providing a custom implementation
        """

    @staticmethod
    @abstractmethod
    def step_two():
        """
        an abstract method that must be overridden in the implementing class
        it has been given '@abstractmethod' decorator so that pyling shows the error
        """

    @staticmethod
    def step_three():
        """
        hooks can also contain default behavior and can be optionally
        overridden
        """

        print("Step three is a hook that prints this line by default.")

    @classmethod
    def template_method(cls):
        """
        this is the template method that the subclass will call
        the subclass (implementing class) does not need to override this method
        since it has would have already optionally overridden the following methods
        with its own implementations
        """

        cls.step_one()
        cls.step_two()
        cls.step_three()


class ConcreteClassA(AbstractClass):
    "a concrete class that only overrides step two"
    @staticmethod
    def step_two():
        print("class A: Step two (overridden)")


class ConcreteClassB(AbstractClass):
    "a concrete class that only overrides steps one, two and three"
    @staticmethod
    def step_one():
        print("class B: Step one (overridden)")

    @staticmethod
    def step_two():
        print("class B : Step two (overridden)")

    @staticmethod
    def step_three():
        print("class B : step three (overridden)")


if __name__ == "__main__":
    classA = ConcreteClassA()
    classA.template_method()

    classB = ConcreteClassB()
    classB.template_method()
