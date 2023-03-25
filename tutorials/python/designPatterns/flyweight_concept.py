
class IFlyweight():
    "nothing to implement"


class Flyweight(IFlyweight):
    "the concrete flyweight"

    def __init__(self, code: str) -> None:
        self.code = code


class FlyweightFactory():
    "creating the flyweight as a singleton"

    _flyweights: dict[str, Flyweight] = {}

    def __new__(cls):
        return cls

    @classmethod
    def get_flyweight(cls, code: str) -> Flyweight:
        "a static method to get a flyweight based on a code"

        if not code in cls._flyweights:
            cls._flyweights[code] = Flyweight(code)

        return cls._flyweights[code]

    @classmethod
    def get_count(cls) -> int:
        "return the number of flyweights in the cache"
        return len(cls._flyweights)


class Context():
    """
    an example context that holds references to the flyweights in a particular order
    and converts the code to an ascii letter
    """

    def __init__(self, codes: str) -> None:
        self.codes = list(codes)

    def output(self):
        "the context specific output that uses flyweights"

        ret = ""
        for code in self.codes:
            ret += FlyweightFactory.get_flyweight(code).code
        return ret


if __name__ == "__main__":
    context = Context("abracadabra")
    print(context.output())
    print(f"abracadabra has {len('abracadabra')} letters")
    print(f"FlyweightFactory has {FlyweightFactory.get_count()} flyweights")
