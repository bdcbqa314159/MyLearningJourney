import csv

if __name__ == "__main__":

    with open("example.csv") as csvfile:
        file = csv.reader(csvfile)
        for row in file:
            print(row)

    with open("example.csv", "a") as csvfile:
        file = csv.writer(csvfile)
        file.writerow(['1004', 'Fred', 'Weasley', 'IT'])

    with open("example.csv") as csvfile:
        file = csv.reader(csvfile)
        for row in file:
            print(row[1], row[3])

    with open("example.csv") as csvfile:
        file = csv.reader(csvfile)
        for row in file:
            if row[3] == "IT":
                print(row)
