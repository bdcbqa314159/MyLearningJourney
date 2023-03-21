import sys
import random

the_answers = ["it is certain", "you may rely on it", "as I see it, yes",
               "outlook looks good", "most likely", "it is decidely so",
               "without a doubt", "yes, definitely"]

if __name__ == "__main__":
    print("First project")

    while True:
        question = input("Ask a question. (Press ENTER to quit) >> ")

        if question == "":
            print("ok... bye now.")
            sys.exit(0)
        else:
            random_number = random.randint(0, 7)
            answer = the_answers[random_number]
            print(f"\nto this question: {question} I say: {answer}")
