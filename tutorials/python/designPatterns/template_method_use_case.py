"the template method pattern use case"
# pylint: disable=too-few-public-methods
# pylint: disable=arguments-differ
# pylint: disable=C0103

from abc import ABCMeta, abstractmethod


class AbstractDocument(metaclass=ABCMeta):
    "a template class containing a template method and primitive methods"

    @staticmethod
    @abstractmethod
    def title(document):
        "must implement"

    @staticmethod
    def description(document):
        "optional"

    @staticmethod
    def author(document):
        "optional"

    @staticmethod
    def background_colour(document):
        "optional with a default behavior"
        document["background_colour"] = "white"

    @staticmethod
    @abstractmethod
    def text(document, text):
        "must implement"

    @staticmethod
    def footer(document):
        "optional"

    @staticmethod
    def print(document):
        "optional with a default behavior"
        print("----------------------")
        for attribute in document:
            print(f"{attribute}\t: {document[attribute]}")
        print()

    @classmethod
    def create_document(cls, text):
        "the template method"
        _document = {}
        cls.title(_document)
        cls.description(_document)
        cls.author(_document)
        cls.background_colour(_document)
        cls.text(_document, text)
        cls.footer(_document)
        cls.print(_document)


class TextDocument(AbstractDocument):
    "Prints out a text document"
    @staticmethod
    def title(document):
        document["title"] = "New Text Document"

    @staticmethod
    def text(document, text):
        document["text"] = text

    @staticmethod
    def footer(document):
        document["footer"] = "-- Page 1 --"


class HTMLDocument(AbstractDocument):
    "Prints out a HTML formatted document"
    @staticmethod
    def title(document):
        document["title"] = "New HTML Document"

    @staticmethod
    def text(document, text):
        "Putting multiple lines into there own p tags"
        lines = text.splitlines()
        markup = ""
        for line in lines:
            markup = markup + "    <p>" + f"{line}</p>\n"
        document["text"] = markup[:-1]

    @staticmethod
    def print(document):
        "overriding print to output with html tags"
        print("<html>")
        print("  <head>")
        for attribute in document:
            if attribute in ["title", "description", "author"]:
                print(
                    f"    <{attribute}>{document[attribute]}"
                    f"</{attribute}>"
                )
            if attribute == "background_colour":
                print("    <style>")
                print("      body {")
                print(
                    f"        background-color: "
                    f"{document[attribute]};")
                print("      }")
                print("    </style>")
        print("  </head>")
        print("  <body>")
        print(f"{document['text']}")
        print("  </body>")
        print("</html>")


if __name__ == "__main__":
    txt_doc = TextDocument()
    txt_doc.create_document("some text")

    html_doc = HTMLDocument()
    html_doc.create_document("Line 1\nLine2")
