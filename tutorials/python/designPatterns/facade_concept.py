class SubSystemClassA:
    "a hypothetically complicated class"
    @staticmethod
    def method():
        "a hypothetically complicated class"


class SubSystemClassB:
    "a hypothetically complicated class"
    @staticmethod
    def method(value):
        "a hypothetically complicated class"
        return value


class SubSystemClassC:
    "a hypothetically complicated class"
    @staticmethod
    def method(value):
        "a hypothetically complicated class"
        return value


class Facade():
    "A simplified facade offering the services of subsystems"
    @staticmethod
    def sub_system_class_a():
        "Use the subsystems method"
        return SubSystemClassA.method()

    @staticmethod
    def sub_system_class_b(value):
        "Use the subsystems method"
        return SubSystemClassB.method(value)

    @staticmethod
    def sub_system_class_c(value):
        "Use the subsystems method"
        return SubSystemClassC.method(value)


if __name__ == "__main__":
    print(SubSystemClassA.method())
    print(SubSystemClassB.method("B"))
    print(SubSystemClassC.method({"C": [1, 2, 3]}))

    print(Facade().sub_system_class_a())
    print(Facade().sub_system_class_b("B"))
    print(Facade().sub_system_class_c({"C": [1, 2, 3]}))
