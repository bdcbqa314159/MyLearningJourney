
if __name__ == "__main__":
    # f = open("sales_data", "r")
    # # print(f.read())
    # # print(f.readline())
    # # print(f.readline())
    # # print(f.readline())

    # for x in f:
    #     print(x.strip())

    f = open("sales_data", "a")  # w: overwrite, a:add more info.
    f.write("\nJan 2023 $122200")
    f.close()

    f = open("sales_data", "r")
    for x in f:
        print(x.strip())
    f.close()

    f = open("sales", "w")  # x: creates if the file does not exist.
    for i in range(10):
        f.write(str(i)+"\n")
    f.close()

    f = open("sales", "r")
    for x in f:
        print(x.strip())
    f.close()
