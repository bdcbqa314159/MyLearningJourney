"observer concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class IObservable(metaclass=ABCMeta):
    "the subject interface"
    @staticmethod
    @abstractmethod
    def subscribe(observer):
        "the subscribe method"

    @staticmethod
    @abstractmethod
    def unsubscribe(observer):
        "the unsubscribe method"

    @staticmethod
    @abstractmethod
    def notify(observer):
        "the notify method"


class Subject(IObservable):
    "the subject a.k.a the observable"

    def __init__(self):
        self._observers = set()

    def subscribe(self, observer):
        self._observers.add(observer)

    def unsubscribe(self, observer):
        self._observers.remove(observer)

    def notify(self, *args):
        for observer in self._observers:
            observer.notify(*args)


class IObserver(metaclass=ABCMeta):
    "a method for the observer to implement"

    @staticmethod
    @abstractmethod
    def notify(observable, *args):
        "receive notifications"


class Observer(IObserver):
    "the concrete observer"

    def __init__(self, observable):
        observable.subscribe(self)

    def notify(self, *args):
        print(f"observer id: {id(self)} received {args}")


if __name__ == "__main__":
    subject = Subject()
    observer_a = Observer(subject)
    observer_b = Observer(subject)

    subject.notify("first notification", [1, 2, 3])
    subject.unsubscribe(observer_b)
    subject.notify("second notification", {"a": 1, "b": 2, "c": 3})
