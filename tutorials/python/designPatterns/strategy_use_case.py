"the strategy pattern use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class GameCharacter():
    "this is the context whose strategy will change"

    position = [0, 0]

    @classmethod
    def move(cls, movement_style):
        "the movement algorithm has been decided by the client"

        movement_style(cls.position)


class IMove(metaclass=ABCMeta):
    "a concrete strategy interface"

    @staticmethod
    @abstractmethod
    def __call__():
        "implementors must select the default method"


class Walking(IMove):
    "a comcrete strategy subclass"

    @staticmethod
    def walk(position):
        "a walk algorithm"
        position[0] += 1
        print(f"I am walking - new position = {position}")

    __call__ = walk


class Running(IMove):
    "a concrete strategy subclass"

    @staticmethod
    def run(position):
        "a run algorithm"
        position[0] += 2
        print(f"I am running - new position = {position}")

    __call__ = run


class Crawling(IMove):
    "a concrete strategy subclass"

    @staticmethod
    def crawl(position):
        "a crawl algorithm"
        position[0] += 0.5
        print(f"I am crawling - new position = {position}")

    __call__ = crawl


if __name__ == "__main__":
    gameCharacter = GameCharacter()
    gameCharacter.move(Walking())
    gameCharacter.move(Running())
    gameCharacter.move(Crawling())
