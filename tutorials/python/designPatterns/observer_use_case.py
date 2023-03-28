"observer use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103


from abc import ABCMeta, abstractmethod


class IDataModel(metaclass=ABCMeta):
    "a subject interface"

    @staticmethod
    @abstractmethod
    def subscribe(observer):
        "the subscribe method"

    @staticmethod
    @abstractmethod
    def unsubscribe(observer_id):
        "the unsubscribe method"

    @staticmethod
    @abstractmethod
    def notify(data):
        "the notify method"


class IDataView(metaclass=ABCMeta):
    "a method for the observer to implement"

    @staticmethod
    @abstractmethod
    def notify(data):
        "receive notifications"

    @staticmethod
    @abstractmethod
    def draw(data):
        "draw the view"

    @staticmethod
    @abstractmethod
    def delete():
        "a delete method to remove observer specific resources"


class IDataController(metaclass=ABCMeta):
    "a subject interface"
    @staticmethod
    @abstractmethod
    def subscribe(observer):
        "the subscribe method"

    @staticmethod
    @abstractmethod
    def unsubscribe(observer):
        "the notify method"

    @staticmethod
    @abstractmethod
    def notify(observer):
        "the notify method"


class DataController(IDataController):
    "a subject (a.k.a observable)"

    _observers = set()

    def __new__(cls):
        return cls

    @classmethod
    def subscribe(cls, observer):
        cls._observers.add(observer)

    @classmethod
    def unsubscribe(cls, observer):
        cls._observers.remove(observer)

    @classmethod
    def notify(cls, *args):
        for observer in cls._observers:
            observer.notify(*args)


class DataModel(IDataModel):
    "a subject (a.k.a observable)"

    def __init__(self):
        self._observers = {}
        self._counter = 0

        self._data_controller = DataController()
        self._data_controller.subscribe(self)

    def subscribe(self, observer):
        self._counter += 1
        self._observers[self._counter] = observer
        return self._counter

    def unsubscribe(self, observer_id):
        self._observers.pop(observer_id)

    def notify(self, data):
        for observer, _ in self._observers.items():
            self._observers[observer].notify(data)


class PieGraphView(IDataView):
    "the concrete observer"

    def __init__(self, observable):
        self._observable = observable
        self._id = self._observable.subscribe(self)

    def notify(self, data):
        print(f"PieGraph, id{self._id}")
        self.draw(data)

    def draw(self, data):
        print(f"Drawing a pie graph using data: {data}")

    def delete(self):
        self._observable.unsubscribe(self._id)


class BarGraphView(IDataView):
    "the concrete observer"

    def __init__(self, observable):
        self._observable = observable
        self._id = self._observable.subscribe(self)

    def notify(self, data):
        print(f"bargraph: id{self._id}")
        self.draw(data)

    def draw(self, data):
        print(f"drawing a bar graph view using data: {data}")

    def delete(self):
        self._observable.unsubscribe(self._id)


class TableView(IDataView):
    "the concrete observer"

    def __init__(self, observable):
        self._observable = observable
        self._id = self._observable.subscribe(self)

    def notify(self, data):
        print(f"tableview: id{self._id}")
        self.draw(data)

    def draw(self, data):
        print(f"drawing a table view using data: {data}")

    def delete(self):
        self._observable.unsubscribe(self._id)


if __name__ == "__main__":
    data_model = DataModel()
    pie_graph = PieGraphView(data_model)
    bar_graph = BarGraphView(data_model)
    table_graph = TableView(data_model)

    data_controller = DataController()

    data_controller.notify([1, 2, 3])

    bar_graph.delete()
    data_controller.notify([4, 5, 6])
