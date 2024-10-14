import sys
from cs50 import get_string


def main():
    text = get_string("Text: ")

    letterCount: int = getLetterCount(text)
    wordCount: int = getWordCount(text)
    sentenceCount: int = getSentenceCount(text)

    getGrade = clIndex(letterCount, wordCount, sentenceCount)
    printResult(getGrade)


def getLetterCount(text: str):
    return len([i for i in text if i.isalpha()])


def getWordCount(text: str):
    return len([i for i in text if i.isspace()]) + 1


def getSentenceCount(text: str):
    return len([i for i in text if (i == ".") or (i == "!") or (i == "?")])


def clIndex(letterCount: int, wordCount: int, sentenceCount: int):
    averageWords: float = 100 * (letterCount / wordCount);
    averageSentences: float = 100 * (sentenceCount / wordCount);
    colemanIndex: float = (0.0588 * averageWords - 0.296 * averageSentences - 15.8);

    # Round up if needed
    if (colemanIndex < 1):
        return colemanIndex
    roundUp: float = round(colemanIndex)

    return roundUp

def printResult(grade: int):
    if (grade < 1):
        print("Before Grade 1")

    elif (grade >= 16):
        print("Grade 16+")

    else:
        print(f"Grade {grade}")


if __name__ == "__main__":
    main()
