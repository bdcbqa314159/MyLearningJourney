"chain of responsability use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod
import sys


class IDispenser(metaclass=ABCMeta):
    "methods to implement"
    @staticmethod
    @abstractmethod
    def next_successor(successor):
        "set the next handler in the chain"

    @staticmethod
    @abstractmethod
    def handle(amount):
        "handle the event"


class Dispenser10(IDispenser):
    "Dispenses £10s if applicable, otherwise continues to next successor"

    def __init__(self):
        self._successor = None

    def next_successor(self, successor):
        "set the next successor"
        self._successor = successor

    def handle(self, amount):
        "handle the dispensing of notes"
        if amount >= 10:
            num = amount // 10
            remainder = amount % 10

            print(f"Dispensing {num} £10 notes")

            if remainder != 0:
                self._successor.handle(remainder)
        else:
            self._successor.handle(amount)


class Dispenser20(IDispenser):
    "Dispenses £20s if applicable, otherwise continues to next successor"

    def __init__(self):
        self._successor = None

    def next_successor(self, successor):
        "set the next successor"
        self._successor = successor

    def handle(self, amount):
        "handle the dispensing of notes"
        if amount >= 20:
            num = amount // 20
            remainder = amount % 20

            print(f"Dispensing {num} £20 notes")

            if remainder != 0:
                self._successor.handle(remainder)
        else:
            self._successor.handle(amount)


class Dispenser50(IDispenser):
    "Dispenses £10s if applicable, otherwise continues to next successor"

    def __init__(self):
        self._successor = None

    def next_successor(self, successor):
        "set the next successor"
        self._successor = successor

    def handle(self, amount):
        "handle the dispensing of notes"
        if amount >= 50:
            num = amount // 50
            remainder = amount % 50

            print(f"Dispensing {num} £50 notes")

            if remainder != 0:
                self._successor.handle(remainder)
        else:
            self._successor.handle(amount)


class ATMDispenserChain:
    "the chain client"

    def __init__(self):
        self.chain1 = Dispenser50()
        self.chain2 = Dispenser20()
        self.chain3 = Dispenser10()

        self.chain1.next_successor(self.chain2)
        self.chain2.next_successor(self.chain3)


if __name__ == "__main__":
    atm = ATMDispenserChain()
    amount_ = int(input("Enter amount to withdrawal: "))
    if amount_ < 10 or amount_ % 10 != 0:
        print("amount should be positive and in multiple of 10")
        sys.exit(0)
    atm.chain1.handle(amount_)
    print("Now go spoil yourself")
