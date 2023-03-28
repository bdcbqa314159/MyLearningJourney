"proxy use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
from abc import ABCMeta, abstractmethod
import random


class IProteus(metaclass=ABCMeta):
    "a greek mythological character that can change to many forms"

    @staticmethod
    @abstractmethod
    def tell_me_the_future():
        "Proteus will change form rather than tell you the future"

    @staticmethod
    @abstractmethod
    def tell_me_your_form():
        "the form of Proteus is elusive like the sea"


class Leopard(IProteus):
    "Proteus in the form of a Leopard"
    name = "Leopard"

    def tell_me_the_future(self):
        "Proteus will change to something random"
        self.__class__ = Lion if random.randint(0, 1) else Serpent

    @classmethod
    def tell_me_your_form(cls):
        print("I am the form of a " + cls.name)


class Lion(IProteus):
    "Proteus in the form of a Lion"
    name = "Lion"

    def tell_me_the_future(self):
        "Proteus will change to something random"
        self.__class__ = Leopard if random.randint(0, 1) else Serpent

    @classmethod
    def tell_me_your_form(cls):
        print("I am the form of a " + cls.name)


class Serpent(IProteus):
    "Proteus in the form of a Serpent"

    name = "Serpent"

    def tell_me_the_future(self):
        "Proteus will change to something random"
        self.__class__ = Leopard if random.randint(0, 1) else Lion

    @classmethod
    def tell_me_your_form(cls):
        print("I am the form of a " + cls.name)


if __name__ == "__main__":
    PROTEUS = Lion()
    PROTEUS.tell_me_your_form()
    PROTEUS.tell_me_the_future()
    PROTEUS.tell_me_your_form()
    PROTEUS.tell_me_the_future()
    PROTEUS.tell_me_your_form()
    PROTEUS.tell_me_the_future()
    PROTEUS.tell_me_your_form()
    PROTEUS.tell_me_the_future()
    PROTEUS.tell_me_your_form()
    PROTEUS.tell_me_the_future()
