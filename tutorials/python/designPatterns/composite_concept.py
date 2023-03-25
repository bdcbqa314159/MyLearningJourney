from abc import ABCMeta, abstractmethod


class IComponent(metaclass=ABCMeta):
    "a component interface describing the common fields and methods or leaves and composites"
    reference_to_parent = None

    @staticmethod
    @abstractmethod
    def detach():
        "calle before a leaf is attached to a composite"


class Leaf(IComponent):
    "a leaf can be added to a composite, but not a leaf"

    def method(self):
        parent_id = (id(self.reference_to_parent)
                     if self.reference_to_parent is not None else None)

        print(f"<Leaf>\t\tid:{id(self)}\tParent:\t{parent_id}")

    def detach(self):
        "detaching this leaf from its parent composite"
        if self.reference_to_parent is not None:
            self.reference_to_parent.delete(self)


class Composite(IComponent):
    "a composite can contain leaves and composites"

    def __init__(self):
        self.components = []

    def method(self):
        parent_id = (id(self.reference_to_parent)
                     if self.reference_to_parent is not None else None)
        print(f"<Composite>\tid:{id(self)}\tParent:\t{parent_id}\t"
              f"Components:{len(self.components)}")

        for component in self.components:
            component.method()

    def attach(self, component):
        """
        detach leaf/composite from any current parent reference
        and then set the parent reference to this composite (self)
        """
        component.detach()
        component.reference_to_parent = self
        self.components.append(component)

    def delete(self, component):
        "removes leaf/composite from this composite self.components"

    def detach(self):
        "detaching this composite from its parent composite"
        if self.reference_to_parent is not None:
            self.reference_to_parent.delete(self)
            self.reference_to_parent = None


if __name__ == "__main__":
    leaf_a = Leaf()
    leaf_b = Leaf()

    composite_1 = Composite()
    composite_2 = Composite()

    print(f"leaf_a\t\tid:{id(leaf_a)}")
    print(f"leaf_b\t\tid:{id(leaf_b)}")
    print(f"composite_1\tid:{id(composite_1)}")
    print(f"composite_1\tid:{id(composite_1)}")

    composite_1.attach(leaf_a)
    composite_2.attach(leaf_a)
    composite_2.attach(composite_1)

    print()
    leaf_b.method()
    composite_2.method()
