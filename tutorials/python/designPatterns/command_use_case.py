"command use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
from abc import ABCMeta, abstractmethod
from datetime import datetime
import time


class ISwitch(metaclass=ABCMeta):
    "the switch interface, that all commands will implement"

    @staticmethod
    @abstractmethod
    def execute():
        "the required execute method that all command objects will use"


class Light:
    "the receiver"
    @staticmethod
    def turn_on():
        "a set of instructions to run"
        print("light turned ON")

    @staticmethod
    def turn_off():
        "a set of instructions to run"
        print("light turned OFF")


class SwitchOnCommand(ISwitch):
    "switch on command"

    def __init__(self, light_):
        self._light = light_

    def execute(self):
        self._light.turn_on()


class SwitchOffCommand(ISwitch):
    "switch off command"

    def __init__(self, light_):
        self._light = light_

    def execute(self):
        self._light.turn_off()


class Switch:
    "the invoker class"

    def __init__(self):
        self._commands = {}
        self._history = []

    def show_history(self):
        "print the history of each time a command was invoked"
        for row in self._history:
            print(f"{datetime.fromtimestamp(row[0]).strftime('%H:%M:%S')}"
                  f" : {row[1]}")

    def register(self, command_name, command):
        "register commands in the invoker"
        self._commands[command_name] = command

    def execute(self, command_name):
        "execute any registered command"
        if command_name in self._commands:
            self._history.append((time.time(), command_name))
        else:
            print(f"command [{command_name}] not recognised")

    def replay_last(self, number_of_commands):
        "replay the last n commands"
        commands = self._history[-number_of_commands:]
        for command in commands:
            self._commands[command[1]].execute()


if __name__ == "__main__":
    light = Light()
    switchOn = SwitchOnCommand(light)
    switchOff = SwitchOffCommand(light)

    switch = Switch()

    switch.register("ON", switchOn)
    switch.register("OFF", switchOff)

    switch.execute("ON")
    switch.execute("OFF")
    switch.execute("ON")
    switch.execute("OFF")

    switch.show_history()

    switch.replay_last(2)
