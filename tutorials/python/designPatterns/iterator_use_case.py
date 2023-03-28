"iterator use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103


class NumberWheel():
    "the concrete iterator (iterable)"

    def __init__(self):
        self.index = 0

    def next(self):
        "return a new number next in the wheel"
        self.index = self.index+1
        return self.index*2 % 11


if __name__ == "__main__":
    number_wheel_a = NumberWheel()
    number_wheel_b = NumberWheel()

    for i in range(5):
        print(number_wheel_a.next(), end=", ")

    print()
    for i in range(5):
        print(number_wheel_b.next(), end=", ")

    print()
