from abc import ABCMeta, abstractmethod


class IComponent(metaclass=ABCMeta):
    "the component interface"

    reference_to_parent = None

    @staticmethod
    @abstractmethod
    def dir(indent):
        "a method each leaf and composite container should implement"

    @staticmethod
    @abstractmethod
    def detach():
        """
        called before a leaf is attached to a composite so that it can clean any parent references
        """


class File(IComponent):
    "the file class. the files are leaves"

    def __init__(self, name):
        self.name = name

    def dir(self, indent):
        parent_id = (id(self.reference_to_parent)
                     if self.reference_to_parent else None)
        print(
            f"{indent}<FILE> {self.name}\t\t"
            f"id:{id(self)}\tParent:\t{parent_id}"
        )

    def detach(self):
        "detaching this file (leaf) from its parent composite"
        if self.reference_to_parent:
            self.reference_to_parent.delete(self)


class Folder(IComponent):
    "the folder class can contain other folders and files"

    def __init__(self, name):
        self.name = name
        self.components = []

    def dir(self, indent=""):
        print(
            f"{indent}<DIR> {self.name}\t\tid:{id(self)}\t"
            f"Components: {len(self.components)}"
        )

        for component in self.components:
            component.dir(indent + "..")

    def attach(self, component):
        """
        detach file/folder from any current parent reference
        and then set the parent reference to this folder
        """

        component.detach()
        component.reference_to_parent = self
        self.components.append(component)

    def delete(self, component):
        """
        removes file/folder from this folder so that self.components is cleaned
        """

        self.components.remove(component)

    def detach(self):
        "detaching this folder from its parent folder"

        if self.reference_to_parent:
            self.reference_to_parent.delete(self)
            self.reference_to_parent = None


if __name__ == "__main__":
    FILESYSTEM = Folder("root")
    FILE_1 = File("abc.txt")
    FILE_2 = File("123.txt")
    FILESYSTEM.attach(FILE_1)
    FILESYSTEM.attach(FILE_2)
    FOLDER_A = Folder("folder_a")
    FILESYSTEM.attach(FOLDER_A)
    FILE_3 = File("xyz.txt")
    FOLDER_A.attach(FILE_3)
    FOLDER_B = Folder("folder_b")
    FILE_4 = File("456.txt")
    FOLDER_B.attach(FILE_4)
    FILESYSTEM.attach(FOLDER_B)
    FILESYSTEM.dir()

    # now move FOLDER_A and its contents to FOLDER_B
    print()
    FOLDER_B.attach(FOLDER_A)
    FILESYSTEM.dir()
