"interpreter concept"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103


class AbstractExpression():
    "all terminal and non-terminal expression will implement an `interpret` method"
    @staticmethod
    def interpret():
        "the 'interpret' method gets called recursiverly for each abstract expression"


class Number(AbstractExpression):
    "terminal expression"

    def __init__(self, value):
        self.value = int(value)

    def interpret(self):
        return self.value

    def __repr__(self):
        return str(self.value)


class Add(AbstractExpression):
    "non-terminal expression"

    def __init__(self, left, right):
        self.left = left
        self.right = right

    def interpret(self):
        return self.left.interpret()+self.right.interpret()

    def __repr__(self):
        return f"({self.left} Add {self.right})"


class Substract(AbstractExpression):
    "non-terminal expression"

    def __init__(self, left, right):
        self.left = left
        self.right = right

    def interpret(self):
        return self.left.interpret()-self.right.interpret()

    def __repr__(self):
        return f"({self.left} Substract {self.right})"


if __name__ == "__main__":

    sentence = "5 + 4 - 3 + 7 - 2"
    print(sentence)

    tokens = sentence.split(" ")
    print(tokens)

    ast: list[AbstractExpression] = []

    ast.append(Add(Number(tokens[0]), Number(tokens[2])))
    ast.append(Substract(ast[0], Number(tokens[4])))
    ast.append(Add(ast[1], Number(tokens[6])))
    ast.append(Substract(ast[2], Number(tokens[8])))

    ast_root = ast.pop()

    print(ast_root.interpret())
    print(ast_root)
