"chain of responsability concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

import random
from abc import ABCMeta, abstractmethod


class IHandler(metaclass=ABCMeta):
    "the handler interface that the successors should implement"
    @staticmethod
    @abstractmethod
    def handle(payload):
        "a method to implement"


class Successor1(IHandler):
    "a concrete handler"
    @staticmethod
    def handle(payload):
        print(f"Successor1 payload = {payload}")
        test = random.randint(1, 2)
        if test == 1:
            payload += 1
            payload = Successor1().handle(payload)
        if test == 2:
            payload -= 1
            payload = Successor2().handle(payload)

        return payload


class Successor2(IHandler):
    "a concrete handler"
    @staticmethod
    def handle(payload):
        print(f"Successor2 payload = {payload}")
        test = random.randint(1, 3)
        if test == 1:
            payload *= 2
            payload = Successor1().handle(payload)
        if test == 2:
            payload /= 2
            payload = Successor2().handle(payload)

        return payload


class Chain():
    "a chain with a default first successor"
    @staticmethod
    @abstractmethod
    def start(payload):
        "setting the first successor that will modify the payload"
        return Successor1().handle(payload)


if __name__ == "__main__":
    chain = Chain()
    payload_ = 1
    out = chain.start(payload_)

    print(f"finished result = {out}")
