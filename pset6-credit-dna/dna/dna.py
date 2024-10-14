import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("dna.py DATABASE SEQUENCE")
        sys.exit(1)

    # Read database file into a variable
    database = createDict(sys.argv[1])

    # Read DNA sequence file into a variable
    sequence = getDNASequence(sys.argv[2])

    # Find longest match of each STR in DNA sequence
    # Make a dictionary with each key being a STR and the value is the longest match
    strMatches = createSTRDict(database, sequence)

    # Check database for matching profiles
    findMatches(database, strMatches)


def findMatches(database: list, strMatches: dict):
    for person in database:
        for str in person:
            match = True
            if str == "name":
                continue

            if int(person[str]) != strMatches[str]:
                match = False
                break

        if match:
            print(person["name"])
            sys.exit(0)

    print("No match")
    sys.exit(0)


def createDict(database: str):
    rows = []
    with open(database) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)

    return rows


def getDNASequence(dnafile: str):
    with open(dnafile) as file:
        return file.read()


def createSTRDict(database: list, sequence: str):
    strMatches = {}
    for dictionary in database:
        for str, count in dictionary.items():
            if str == "name":
                continue

            strMatches[str] = longest_match(sequence, str)

    return strMatches


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


if __name__ == "__main__":
    main()
