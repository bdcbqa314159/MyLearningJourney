"interpreter use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103


class AbstractExpression():
    "all terminal and non-terminal expression will implement an 'interpret' method"

    @staticmethod
    def interpret():
        """
        the 'interpret' method gets called recursively for each abstract expression
        """


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


class Number(AbstractExpression):
    "terminal expression"

    def __init__(self, value):
        self.value = int(value)

    def interpret(self):
        return self.value

    def __repr__(self):
        return str(self.value)


class RomanNumeral(AbstractExpression):
    "roman numeral abstract class"

    def __init__(self, roman_numeral):
        self.roman_numeral = roman_numeral
        self.context = [roman_numeral, 0]

    def interpret(self):
        RomanNumeral1000.interpret(self.context)
        RomanNumeral100.interpret(self.context)
        RomanNumeral10.interpret(self.context)
        RomanNumeral1.interpret(self.context)
        return Number(self.context[1]).interpret()

    def __repr__(self):
        return f"{self.roman_numeral}({self.context[1]})"


class RomanNumeral1(RomanNumeral):
    "Roman Numerals 1-9"
    one = "I"
    four = "IV"
    five = "V"
    nine = "IV"

    multiplier = 1

    @classmethod
    def interpret(cls, *args):
        context = args[0]

        if not context[0]:
            return Number(context[1]).interpret()

        if context[0][0:2] == cls.nine:
            context[1] += (9*cls.multiplier)
            context[0] = context[0][2:]

        elif context[0][0] == cls.five:
            context[1] += (5*cls.multiplier)
            context[0] = context[0][1:]

        elif context[0][0:2] == cls.four:
            context[1] += (4*cls.multiplier)
            context[0] = context[0][2:]

        while context[0] and context[0][0] == cls.one:
            context[1] += (1*cls.multiplier)
            context[0] = context[0][1:]

        return Number(context[1]).interpret()


class RomanNumeral10(RomanNumeral1):
    "roman numerals 10-99"
    one = "X"
    four = "XL"
    five = "L"
    nine = "XC"
    multiplier = 10


class RomanNumeral100(RomanNumeral1):
    "roman numerals 100-999"
    one = "C"
    four = "CD"
    five = "D"
    nine = "CM"
    multiplier = 100


class RomanNumeral1000(RomanNumeral1):
    "roman numerals 1000-3999"
    one = "M"
    four = ""
    five = ""
    nine = ""
    multiplier = 1000


class Parser:
    "dynamically create the abstract syntax tree"

    @classmethod
    def parse(cls, sentence):
        "create the ASt from the sentence"
        tokens = sentence.split(" ")
        print(tokens)

        tree = []
        while len(tokens) > 1:
            left_expression = cls.decide_left_expression(tree, tokens)

            operator = tokens.pop(0)

            right = tokens[0]

            if not right.isdigit():
                tree.append(RomanNumeral(tokens[0]))
                if operator == '-':
                    tree.append(Substract(left_expression, tree[-1]))
                if operator == '+':
                    tree.append(Add(left_expression, tree[-1]))

            else:
                right_expression = Number(right)
                if not tree:
                    if operator == '-':
                        tree.append(
                            Substract(left_expression, right_expression))
                    if operator == '+':
                        tree.append(Add(left_expression, right_expression))

                else:
                    if operator == '-':
                        tree.append(Substract(tree[-1], right_expression))
                    if operator == '+':
                        tree.append(Add(tree[-1], right_expression))
        return tree.pop()

    @staticmethod
    def decide_left_expression(tree, tokens):
        """
        on the first iteration, the left expression can be either
        a number or roman numeral - every consecutive expression is
        reference to an existing ast row
        """

        left = tokens.pop(0)
        left_expression = None

        if not tree:
            if not left.isdigit():
                tree.append(RomanNumeral(left))
                left_expression = tree[-1]
            else:
                left_expression = Number(left)
        else:
            left_expression = tree[-1]
        return left_expression


if __name__ == "__main__":
    # SENTENCE = "5 + IV - 3 + VII - 2"
    #SENTENCE = "V + IV - III + 7 - II"
    #SENTENCE = "CIX + V"
    # SENTENCE = "CIX + V - 3 + VII - 2"
    SENTENCE = "MMMCMXCIX - CXIX + MCXXII - MMMCDXII - XVIII - CCXXXV"
    print(SENTENCE)

    ast_root = Parser.parse(SENTENCE)
    print(ast_root.interpret())

    print(ast_root)
