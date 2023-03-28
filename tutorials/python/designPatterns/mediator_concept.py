"mediator concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103


class Colleague1():
    "this colleague provides data for colleague2"

    @staticmethod
    def method_1():
        "a simple method"
        return "here is the colleague1 specific data you asked for"


class Colleague2():
    "this colleague provides data for colleague1"

    @staticmethod
    def method_2():
        "a simple method"
        return "here is the colleague2 specific data you asked for"


class Mediator():
    "the mediator concrete class"

    def __init__(self):
        self.colleague1 = Colleague1()
        self.colleague2 = Colleague2()

    def colleague1_method(self):
        "calls the method provided by colleague1"
        return self.colleague1.method_1()

    def colleague2_method(self):
        "calls the method provided by colleague2"
        return self.colleague2.method_2()


if __name__ == "__main__":
    mediator = Mediator()
    data = mediator.colleague2_method()
    print(f"colleague1 <--> {data}")

    data = mediator.colleague1_method()
    print(f"colleague2 <--> {data}")
