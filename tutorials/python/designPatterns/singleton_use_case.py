from abc import ABCMeta, abstractmethod


class Leaderboard():
    "The leaderboard as a singleton"
    _table = {}

    def __new__(cls):
        return cls

    @classmethod
    def print(cls):
        "A class level method"
        print("-----------Leaderboard-----------")
        for key, value in sorted(cls._table.items()):
            print(f"|\t{key}\t|\t{value}\t|")
        print()

    @ classmethod
    def add_winner(cls, position, name):
        "A class level method"
        cls._table[position] = name


class IGame(metaclass=ABCMeta):
    "A game interface"
    @ staticmethod
    @ abstractmethod
    def add_winner(position, name):
        "Must implement add_winner"


class Game1(IGame):
    "Game1 implements IGame"

    def __init__(self):
        self.leaderboard = Leaderboard()

    def add_winner(self, position, name):
        self.leaderboard.add_winner(position, name)


class Game2(IGame):
    "Game2 implements IGame"

    def __init__(self):
        self.leaderboard = Leaderboard()

    def add_winner(self, position, name):
        self.leaderboard.add_winner(position, name)


class Game3(Game2):
    "Game3 inherits from Game2"


if __name__ == "__main__":
    # The Client
    # All games share and manage the same leaderboard because it is a singleton.
    game1 = Game1()
    game1.add_winner(2, "Cosmo")

    game2 = Game2()
    game2.add_winner(3, "Sean")

    game3 = Game3()
    game3.add_winner(1, "Emmy")

    game1.leaderboard.print()
    game2.leaderboard.print()
    game3.leaderboard.print()
