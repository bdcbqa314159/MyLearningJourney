import random
import sys
import csv


class magicBall:

    def __init__(self, name):
        self.__name = name
        # self.__questions = []
        self.__start_game()

    def __start_game(self):
        print(f"Hey {self.__name}!")
        the_answers = ["it is certain", "you may rely on it", "as I see it, yes",
                       "outlook looks good", "most likely", "it is decidely so",
                       "without a doubt", "yes, definitely"]
        file = open("questions.csv", "w")

        while True:

            wrt = csv.writer(file)

            question = input("Ask a question. (Press ENTER to quit) >> ")

            if question == "":
                print("ok... bye now.")
                file.close()
                sys.exit(0)
            else:
                wrt.writerow([question])
                random_number = random.randint(0, 7)
                answer = the_answers[random_number]
                print(f"\nto this question: {question} I say: {answer}")


if __name__ == "__main__":
    game = magicBall("Bernardo")
