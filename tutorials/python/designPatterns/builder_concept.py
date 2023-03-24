from abc import ABCMeta, abstractmethod


class Product():
    "The Product"

    def __init__(self):
        self.parts = []


class IBuilder(metaclass=ABCMeta):
    "The builder interface"

    @staticmethod
    @abstractmethod
    def build_part_a():
        "build part a"

    @staticmethod
    @abstractmethod
    def build_part_b():
        "build part b"

    @staticmethod
    @abstractmethod
    def build_part_c():
        "build part c"

    @staticmethod
    @abstractmethod
    def get_result():
        "Return the final product"


class Builder(IBuilder):
    "The concrete builder"

    def __init__(self):
        self.product = Product()

    def build_part_a(self):
        self.product.parts.append('a')
        return self

    def build_part_b(self):
        self.product.parts.append('b')
        return self

    def build_part_c(self):
        self.product.parts.append('c')
        return self

    def get_result(self):
        return self.product


class Director:
    "The director, building a complex representation."
    @staticmethod
    def construct():
        "Constructs and returns the final product"
        return Builder()\
            .build_part_a()\
            .build_part_b()\
            .build_part_c().get_result()


if __name__ == "__main__":
    theProduct = Director.construct()
    print(theProduct.parts)
