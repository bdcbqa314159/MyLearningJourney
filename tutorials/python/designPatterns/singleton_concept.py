import copy


class Singleton():
    "The singleton class"

    value = []

    def __new(cls):
        return cls

    # def __init__(self):
    #     print("in init")

    @staticmethod
    def static_method():
        "use @staticmethod if no inner variables"

    @classmethod
    def class_method(cls):
        "use @classmethod to access class level variables"
        print(cls.value)


if __name__ == "__main__":
    print(f"id(Singleton)\t= {id(Singleton)}")
    OBJECT1 = Singleton()
    print(f"id(OBJECT1)\t= {id(OBJECT1)}")

    OBJECT2 = copy.deepcopy(OBJECT1)
    print(f"id(OBJECT2)\t= {id(OBJECT2)}")

    OBJECT3 = Singleton()
    print(f"id(OBJECT3)\t= {id(OBJECT3)}")
