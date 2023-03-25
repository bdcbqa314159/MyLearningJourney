"""proxy concept"""
from abc import ABCMeta, abstractmethod


class ISubject(metaclass=ABCMeta):
    "an interface implemented by both the proxy and real subject"

    @staticmethod
    @abstractmethod
    def request():
        "method to implement"


class RealSubject(ISubject):
    "the actual real object that the proxy is representing"

    def __init__(self):
        self.enormous_data = [1, 2, 3]

    def request(self):
        return self.enormous_data


class Proxy(ISubject):
    """
    in this case the proxy will act as a cache for `enormous_data` and
    only populate the enormous_data when it is actually necessary
    """

    def __init__(self):
        self.enormous_data = []
        self.real_subject = RealSubject()

    def request(self):
        """
        using the proxy as a cache, and loading data into it only if it is needed
        """

        if not self.enormous_data:
            print("pulling data from RealSubject")
            self.enormous_data = self.real_subject.request()
            return self.enormous_data
        print("pulling data from Proxy cache")
        return self.enormous_data


if __name__ == "__main__":
    subject = Proxy()
    print(id(subject))

    print(subject.request())
    print(subject.request())
