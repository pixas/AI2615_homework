
with open("data.txt", 'w') as f:
    f.write("2 10 1 2 10\n")
    f.writelines(["1 2 1\n" for i in range(5)] + ["2 1 1\n" for i in range(5)])
    # f.write("1 2 2\n")
    