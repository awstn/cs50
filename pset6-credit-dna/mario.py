

def main():
    while (True):
        try:
            height = int(input("Height: "))
            if (height > 0 and height < 9):
                break
        except ValueError:
            pass

    createPyramid(height)


def createPyramid(height: int):
    for i in range(height):
        print(" " * (height - (i + 1)) + "#" * (i + 1), end="")
        print("  " + "#" * (i + 1))


if __name__ == "__main__":
    main()
