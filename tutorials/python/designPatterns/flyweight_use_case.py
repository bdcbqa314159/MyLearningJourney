"""Flyweigth use case"""


class Flyweight():
    "the flyweight that contains an intrinsic value called code"

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


class Column():
    """
    the columns are the contexts.
    they will share the Flyweights via the FlyweightFactory.
    `data`, `width`, `justify` are the extrinsic values. They are outside of the flyweights.
    """

    def __init__(self, data="", width=11, justify=0) -> None:
        self.data = data
        self.width = width
        self.justify = justify

    def get_data(self):
        "get the flyweight value from the factory, and apply the extrinsic values"

        ret = ""
        for data in self.data:
            ret += FlyweightFactory.get_flyweight(data).code

        ret = f"{ret.center(self.width)}" if self.justify == 0 else ret
        ret = f"{ret.ljust(self.width)}" if self.justify == 1 else ret
        ret = f"{ret.rjust(self.width)}" if self.justify == 2 else ret

        return ret


class Row():
    "a row in the table"

    def __init__(self, column_count: int) -> None:
        self.columns = []
        for _ in range(column_count):
            self.columns.append(Column())

    def get_data(self):
        "format the row before returning it to the table"
        ret = ""
        for column in self.columns:
            ret = f"{ret}{column.get_data()}|"
        return ret


class Table():
    "a formatted table"

    def __init__(self, row_count: int, column_count: int) -> None:
        self.rows = []
        for _ in range(row_count):
            self.rows.append(Row(column_count))

    def draw(self):
        "draws the table formatted in the console"

        max_row_length = 0
        rows = []

        for row in self.rows:
            row_data = row.get_data()
            rows.append(f"|{row_data}")
            row_length = len(row_data)+1

            max_row_length = max(row_length, max_row_length)

        print("-" * max_row_length)

        for row in rows:
            print(row)

        print("-" * max_row_length)


if __name__ == "__main__":

    TABLE = Table(3, 3)

    TABLE.rows[0].columns[0].data = "abra"
    TABLE.rows[0].columns[1].data = "112233"
    TABLE.rows[0].columns[2].data = "cadabra"
    TABLE.rows[1].columns[0].data = "racadab"
    TABLE.rows[1].columns[1].data = "12345"
    TABLE.rows[1].columns[2].data = "332211"
    TABLE.rows[2].columns[0].data = "cadabra"
    TABLE.rows[2].columns[1].data = "445566"
    TABLE.rows[2].columns[2].data = "aa 22 bbzz"

    TABLE.rows[0].columns[0].justify = 1
    TABLE.rows[1].columns[0].justify = 1
    TABLE.rows[2].columns[0].justify = 1
    TABLE.rows[0].columns[2].justify = 2
    TABLE.rows[1].columns[2].justify = 2
    TABLE.rows[2].columns[2].justify = 2
    TABLE.rows[0].columns[1].width = 15
    TABLE.rows[1].columns[1].width = 15
    TABLE.rows[2].columns[1].width = 15

    TABLE.draw()

    print(f"FlyweightFactory has {FlyweightFactory.get_count()} flyweights")
