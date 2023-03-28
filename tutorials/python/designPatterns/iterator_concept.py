"iterator concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class IIterator(metaclass=ABCMeta):
    "an iterator interface"
    @staticmethod
    @abstractmethod
    def has_next():
        "returns boolean wheter at end of collection or not"

    @staticmethod
    @abstractmethod
    def next():
        "return the object in collection"


class Iterable(IIterator):
    "the concrete iterator (iterable)"

    def __init__(self, aggregates):
        self.index = 0
        self.aggregates = aggregates

    def next(self):
        if self.index < len(self.aggregates):
            aggregate = self.aggregates[self.index]
            self.index += 1
            return aggregate

        raise StopIteration

    def has_next(self):
        return self.index < len(self.aggregates)


class IAggregate(metaclass=ABCMeta):
    "an interface that the aggregates should implement"
    @staticmethod
    @abstractmethod
    def method():
        "a method to implement"


class Aggregate(IAggregate):
    "a concrete object"
    @staticmethod
    def method():
        print("this method has been invoked")


if __name__ == "__main__":
    aggregates_ = [Aggregate(), Aggregate(), Aggregate(), Aggregate()]
    iterable_ = Iterable(aggregates_)

    while iterable_.has_next():
        iterable_.next().method()
    print()

    for a in aggregates_:
        a.method()
