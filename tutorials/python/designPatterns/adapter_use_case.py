import time
import random
from abc import ABCMeta, abstractmethod


class ICubeA(metaclass=ABCMeta):
    "an interface for an object"
    @staticmethod
    @abstractmethod
    def manufacture(width, height, depth):
        "manufactures a cube"


class ICubeB(metaclass=ABCMeta):
    "an interface for an object"
    @staticmethod
    @abstractmethod
    def create(top_left_front, bottom_right_back):
        "manufactures a cube with coords offset [0,0,0]"


class CubeA(ICubeA):
    "a hypothetical cube tool from company A"
    last_time = int(time.time())

    def __init__(self):
        self.width = self.height = self.depth = 0

    def manufacture(self, width, height, depth):
        self.width = width
        self.height = height
        self.depth = depth

        now = int(time.time())

        if now > int(CubeA.last_time + 1):
            CubeA.last_time = now
            return True
        return False


class CubeB(ICubeB):
    "a hypothetical cube tool from company B"
    last_time = int(time.time())

    def create(self, top_left_front, bottom_right_back):
        now = int(time.time())
        if now > int(CubeB.last_time + 2):
            CubeB.last_time = now
            return True
        return False


class CubeBAdapter(ICubeA):
    "Adapter for CubeB that implements ICubeA"

    def __init__(self):
        self.cube = CubeB()
        self.width = self.height = self.depth = 0

    def manufacture(self, width, height, depth):
        self.width = width
        self.height = height
        self.depth = depth

        success = self.cube.create(
            [0-width/2, 0-height/2, 0-depth/2],
            [0+width/2, 0+height/2, 0+depth/2]
        )
        return success


if __name__ == "__main__":
    total_cubes = 5
    counter = 0

    while counter < total_cubes:
        width = random.randint(1, 10)
        height = random.randint(1, 10)
        depth = random.randint(1, 10)

        cube = CubeA()
        success = cube.manufacture(width, height, depth)
        if success:
            print(
                f"Company A building Cube id:{id(cube)}, "
                f"{cube.width}x{cube.height}x{cube.depth}")
            counter += 1

        else:
            print("Company A is busy, trying company B")
            cube = CubeBAdapter()
            success = cube.manufacture(width, height, depth)
            if success:
                print(
                    f"Company B building Cube id:{id(cube)}, "
                    f"{cube.width}x{cube.height}x{cube.depth}")
                counter += 1
            else:
                print("Company B is busy, trying company A")

        time.sleep(1)
    print(f"{total_cubes} cubes have been manufactured.")
