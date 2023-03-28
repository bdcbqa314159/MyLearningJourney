"command concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
from abc import ABCMeta, abstractmethod


class ICommand(metaclass=ABCMeta):
    "the command interface, that all commands will implement"
    @staticmethod
    @abstractmethod
    def execute():
        "the required execute method that all comman objects will use"


class Invoker:
    "the invoker class"

    def __init__(self):
        self._commands = {}

    def register(self, command_name, command):
        "register commands in the Invoker"
        self._commands[command_name] = command

    def execute(self, command_name):
        "execute any registered commands"
        if command_name in self._commands:
            self._commands[command_name].execute()

        else:
            print(f"Command [{command_name}] not recognised")


class Receiver:
    "the receiver"

    @staticmethod
    def run_command_1():
        "a set of instructions to run"
        print("executing command 1")

    @staticmethod
    def run_command_2():
        "a set of instructions to run"
        print("executing command 2")


class Command1(ICommand):
    """
    a command object, that implements the ICommand interface and
    runs the command on the designated receiver
    """

    def __init__(self, receiver_):
        self._receiver = receiver_

    def execute(self):
        self._receiver.run_command_1()


class Command2(ICommand):
    """
    a command object, that implements the ICommand interface and
    runs the command on the designated receiver
    """

    def __init__(self, receiver_):
        self._receiver = receiver_

    def execute(self):
        self._receiver.run_command_2()


if __name__ == "__main__":
    receiver = Receiver()

    command1 = Command1(receiver)
    command2 = Command2(receiver)

    invoker = Invoker()
    invoker.register("1", command1)
    invoker.register("2", command2)

    invoker.execute("1")
    invoker.execute("2")
    invoker.execute("1")
    invoker.execute("2")
