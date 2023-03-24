from abc import ABCMeta, abstractmethod
import copy


class IPrototype(metaclass=ABCMeta):
    "interface with clone method"
    @staticmethod
    @abstractmethod
    def clone(mode):
        "the clone, deep or shallow it is up to the situation."


class Document(IPrototype):
    "concrete class"

    def __init__(self, name, l):
        self.name = name
        self.list = l

    def clone(self, mode):
        "this clone method uses different copy"
        if mode == 1:
            doc_list = self.list
        if mode == 2:
            doc_list = self.list.copy()
        if mode == 3:
            doc_list = copy.deepcopy(self.list)

        return type(self)(self.name, doc_list)

    def __str__(self):
        "overriding the default __str__ method"
        return f"{id(self)}\tname={self.name}\tlist={self.list}"


if __name__ == "__main__":
    # Creating a document containing a list of two lists
    ORIGINAL_DOCUMENT = Document("Original", [[1, 2, 3, 4], [5, 6, 7, 8]])
    print(ORIGINAL_DOCUMENT)
    print()

    DOCUMENT_COPY_1 = ORIGINAL_DOCUMENT.clone(1)  # shallow copy
    DOCUMENT_COPY_1.name = "Copy 1"
    # This also modified ORIGINAL_DOCUMENT because of the shallow copy
    # when using mode 1
    DOCUMENT_COPY_1.list[1][2] = 200
    print(DOCUMENT_COPY_1)
    print(ORIGINAL_DOCUMENT)
    print()

    DOCUMENT_COPY_2 = ORIGINAL_DOCUMENT.clone(2)  # 2 level shallow copy
    DOCUMENT_COPY_2.name = "Copy 2"
    # This does NOT modify ORIGINAL_DOCUMENT because it changes the
    # list[1] reference that was deep copied when using mode 2
    DOCUMENT_COPY_2.list[1] = [9, 10, 11, 12]
    print(DOCUMENT_COPY_2)
    print(ORIGINAL_DOCUMENT)
    print()

    DOCUMENT_COPY_3 = ORIGINAL_DOCUMENT.clone(2)  # 2 level shallow copy
    DOCUMENT_COPY_3.name = "Copy 3"
    # This does modify ORIGINAL_DOCUMENT because it changes the element of
    # list[1][0] that was NOT deep copied recursively when using mode 2
    DOCUMENT_COPY_3.list[1][0] = "1234"
    print(DOCUMENT_COPY_3)
    print(ORIGINAL_DOCUMENT)
    print()

    DOCUMENT_COPY_4 = ORIGINAL_DOCUMENT.clone(3)  # deep copy (recursive)
    DOCUMENT_COPY_4.name = "Copy 4"
    # This does NOT modify ORIGINAL_DOCUMENT because it
    # deep copies all levels recursively when using mode 3
    DOCUMENT_COPY_4.list[1][0] = "5678"
    print(DOCUMENT_COPY_4)
    print(ORIGINAL_DOCUMENT)
    print()
