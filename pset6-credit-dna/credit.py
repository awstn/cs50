import re
import sys
from cs50 import get_string, get_int



def main():
    ccNumber: string = get_string("Number:")
    print(checkDigits(ccNumber))


# Implement Luhns Algorithm
def checkDigits(ccNumber: str):

    length: int = len(ccNumber)
    if (length != 13 and length != 15 and length != 16):
        return "INVALID"

    oddSum, evenSum, count = 0, 0, 0

    for i in range(length):
        if (length - i) % 2 == 0:
            evenIndex: int = int(ccNumber[i]) * 2

            if (evenIndex > 9):
                endSplit = evenIndex % 10
                frontSplit = evenIndex // 10
                evenSum += endSplit + frontSplit

            else:
                evenSum += evenIndex

        else:
            oddSum += int(ccNumber[i])

    addedSum: int = oddSum + evenSum

    if (addedSum % 10 == 0):
        return checkStartingNumbers(ccNumber)

    return "INVALID"


def checkStartingNumbers(cardNumber: str):
    # Checks if its AMEX
    if re.search("^3[47][0-9]{13}$", cardNumber):
        return "AMEX"

    # Checks it its MASTERCARD
    elif re.search("^5[1-5][0-9]{14}$", cardNumber):
        return "MASTERCARD"

    # Checks if its VISA
    elif re.search("^4(?:[0-9]{12}|[0-9]{15})$", cardNumber):
        return "VISA"

    else:
        return "INVALID"


if __name__ == "__main__":
    main()
